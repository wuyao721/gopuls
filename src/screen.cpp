#include <windows.h>
#include <winnt.h>
#include <stdio.h>

int SaveBitmapToFile(HBITMAP hBitmap, LPSTR lpFileName)
{
   //我们也可以把屏幕内容以位图格式存到磁盘文件上.
   //lpFileName     为位图文件名
   HDC                hDC;      //设备描述表
   int                iBits;    //当前显示分辨率下每个像素所占字节数
   WORD               wBitCount; //位图中每个像素所占字节数

   //定义调色板大小，位图中像素字节大小，位图文件大小，写入文件字节数
   DWORD              dwPaletteSize = 0;
   DWORD              dwBmBitsSize;
   DWORD              dwDIBSize; 
   DWORD              dwWritten;

   BITMAP             Bitmap;   //位图属性结构
   BITMAPFILEHEADER   bmfHdr;   //位图文件头结构
   BITMAPINFOHEADER   bi;       //位图信息头结构    
   LPBITMAPINFOHEADER lpbi;     //指向位图信息头结构
   HANDLE             fh, hDib, hPal,hOldPal = NULL;

   //定义文件，分配内存句柄，调色板句柄
   //计算位图文件每个像素所占字节数
   hDC = CreateDC("DISPLAY",NULL,NULL,NULL);
   iBits = GetDeviceCaps(hDC, BITSPIXEL)*GetDeviceCaps(hDC, PLANES);
   DeleteDC(hDC);
     
   if (iBits <= 1)
      wBitCount = 1;
   else if (iBits <= 4)
      wBitCount = 4;
   else if (iBits <= 8)
      wBitCount = 8;
   else if (iBits <= 32)
      wBitCount = 24;
     
   //计算调色板大小
   if( wBitCount <= 8)
      dwPaletteSize = (1 << wBitCount) * sizeof(RGBQUAD);
     
   //设置位图信息头结构
   GetObject(hBitmap, sizeof(BITMAP), (LPSTR)&     Bitmap);
   bi.biSize = sizeof(BITMAPINFOHEADER);
   bi.biWidth = Bitmap.bmWidth;
   bi.biHeight = Bitmap.bmHeight;
   bi.biPlanes = 1;
   bi.biBitCount = wBitCount;
   bi.biCompression = BI_RGB;
   bi.biSizeImage = 0;
   bi.biXPelsPerMeter = 0;
   bi.biYPelsPerMeter = 0;
   bi.biClrUsed = 0;
   bi.biClrImportant = 0;
   dwBmBitsSize = ((Bitmap.bmWidth*wBitCount+31)/32)*     4*Bitmap.bmHeight     ;
   hDib = GlobalAlloc(GHND,dwBmBitsSize+dwPaletteSize+sizeof(BITMAPINFOHEADER));// 为位图内容分配内存
   lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDib);
   *lpbi = bi;
   hPal=(HPALETTE)::GetStockObject(DEFAULT_PALETTE);// 处理调色板        
     
   if( hPal ){
      hDC = GetDC(NULL);
      hOldPal = SelectPalette(hDC,(HPALETTE)hPal, FALSE);
      RealizePalette(hDC);
   }
 
   // 获取该调色板下新的像素值
   GetDIBits(hDC, hBitmap, 0, (UINT)Bitmap.bmHeight, 
             (LPSTR)lpbi     +     sizeof(BITMAPINFOHEADER)
             +dwPaletteSize, 
             (BITMAPINFO *)
             lpbi, DIB_RGB_COLORS);
 
   //恢复调色板        
   if( hOldPal ){
      SelectPalette(hDC,(HPALETTE)     hOldPal, TRUE);
      RealizePalette(hDC);
      ReleaseDC(NULL, hDC);
   }
     
   //创建位图文件                
   fh = CreateFile(lpFileName, GENERIC_WRITE,0, NULL, CREATE_ALWAYS, 
                   FILE_ATTRIBUTE_NORMAL|FILE_FLAG_SEQUENTIAL_SCAN, NULL);
   if     (fh     ==     INVALID_HANDLE_VALUE)
      return     FALSE;
   // 设置位图文件头
   bmfHdr.bfType = 0x4D42;         // "BM"
 
   dwDIBSize = sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)
      + dwPaletteSize + dwBmBitsSize;        
   bmfHdr.bfSize = dwDIBSize;
   bmfHdr.bfReserved1 = 0;
   bmfHdr.bfReserved2 = 0;
   bmfHdr.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER)    
      + (DWORD)sizeof(BITMAPINFOHEADER)
      + dwPaletteSize;
     
   // 写入位图文件头
   WriteFile(fh, (LPSTR)&     bmfHdr, sizeof
             (BITMAPFILEHEADER), &     dwWritten, NULL);
     
   // 写入位图文件其余内容
   WriteFile(fh, (LPSTR)lpbi, dwDIBSize, 
             &     dwWritten, NULL);
     
   //清除        
   GlobalUnlock(hDib);
   GlobalFree(hDib);
   CloseHandle(fh);
   return     TRUE;            
} 

LPTSTR CopyScreenToBitmap(LPRECT lpRect)
{
   HDC     hScrDC, hMemDC;     // 屏幕和内存设备描述表
   HBITMAP hBitmap,hOldBitmap; // 位图句柄
   int     nX, nY, nX2, nY2;   // 选定区域坐标
   int     nWidth, nHeight;    // 位图宽度和高度
   int     xScrn, yScrn;       // 屏幕分辨率
     
   // 确保选定区域不为空矩形
   if( IsRectEmpty(lpRect) ) return NULL;
     
   // 为屏幕创建设备描述表
   hScrDC = CreateDC("DISPLAY", NULL, NULL, NULL);
     
   // 为屏幕设备描述表创建兼容的内存设备描述表
   hMemDC = CreateCompatibleDC(hScrDC);

   // 获得选定区域坐标
   nX = lpRect->left;
   nY = lpRect->top;
   nX2 = lpRect->right;
   nY2 = lpRect->bottom;
   
   // 获得屏幕分辨率
   xScrn = GetDeviceCaps(hScrDC, HORZRES);
   yScrn = GetDeviceCaps(hScrDC, VERTRES);
     
   // 确保选定区域是可见的
   if( nX  < 0) nX = 0;
   if( nY  < 0) nY = 0;
   if( nX2  > xScrn) nX2 = xScrn;
   if( nY2  > yScrn) nY2 = yScrn;
   nWidth = nX2     -     nX;
   nHeight = nY2     -     nY;
   
#if 0
   // 创建一个与屏幕设备描述表兼容的位图
   int  *temp = new int(m_szResolution.Find("*"));
   char strWidth[10];
   char strHeight[10];

   strcpy(pWidth,m_szResolution.Mid(0,*temp));
   strcpy(pHeight,m_szResolution.Mid(*temp+1));
   delete     temp;
     
   int nDestResWidth = atoi(strWidth);
   int nDestResHeight = atoi(strHeight);
#endif 
   int nDestResWidth = lpRect->right - lpRect->left;
   int nDestResHeight = lpRect->bottom - lpRect->top;

   hBitmap = CreateCompatibleBitmap(hScrDC, nDestResWidth, nDestResHeight);
     
   // 把新位图选到内存设备描述表中
   hOldBitmap = (HBITMAP)::SelectObject(hMemDC, hBitmap);
     
   // 把屏幕设备描述表拷贝到内存设备描述表中
   StretchBlt(hMemDC, 0, 0, nDestResWidth, nDestResHeight,hScrDC, nX, nY,nWidth,nHeight,SRCCOPY);
     
   //得到屏幕位图的句柄
   hBitmap = (HBITMAP)SelectObject(hMemDC, hOldBitmap);
 
   //清除 
   DeleteDC(hScrDC);
   DeleteDC(hMemDC);
   
#if 0
   char     tmppath[MAX_PATH];
   char     *tmpname=new     char[MAX_PATH];
     
   GetTempPath(MAX_PATH,tmppath);
   GetTempFileName(tmppath,"AnyServer",0,tmpname);//获得一个唯一的临时文件名
   SaveBitmapToFile(hBitmap,tmpname);
   return tmpname;
#else 
   SaveBitmapToFile(hBitmap,"C:\\1.bmp");
   return NULL;
#endif
}

#if 0
BOOL ImageList::merge(CString outfile)
{

   unsigned int width = merge_image_width;
   unsigned int height = merge_image_height;
	
   HDC   imgDC = CreateCompatibleDC( NULL );
	
   VOID   *   pbits32;
   HBITMAP   holdBmp,hbm32;
   BITMAPFILEHEADER   hdr;
   BITMAPINFOHEADER   bmi;
   unsigned   char*   buffer;
   HANDLE   hFile;
   int   LineDataBytes=width*4;
   int   Zero=(4-((width*3)%4))%4;
   int   TotalDataBytes=(width*3+Zero)*height;
	
   BOOL   result=FALSE;
	
   if(width<=0   ||   height<=0)
      return   FALSE;
	
   hdr.bfType = ((WORD)   ('M'   <<   8)   |   'B');   //"BM"
   hdr.bfReserved1 = 0;
   hdr.bfReserved2 = 0;
   hdr.bfOffBits = (DWORD)   (sizeof(hdr)+sizeof(bmi));
   hdr.bfSize = (width*3+Zero)*height   +   hdr.bfOffBits;
	
   bmi.biSize=sizeof(BITMAPINFOHEADER);
   bmi.biWidth=width;
   bmi.biHeight=height;
   bmi.biPlanes=1;
   bmi.biBitCount=24;
   bmi.biCompression=BI_RGB;
   bmi.biSizeImage=0;
   bmi.biXPelsPerMeter=0;
   bmi.biYPelsPerMeter=0;
   bmi.biClrUsed=0;
   bmi.biClrImportant=0;
   hFile=CreateFile(outfile,GENERIC_WRITE,FILE_SHARE_WRITE,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
   if(INVALID_HANDLE_VALUE!=hFile)
   {
      DWORD   bw;
		
      WriteFile(hFile,(LPSTR)&hdr, sizeof(hdr),&bw,NULL);
      WriteFile(hFile,(LPSTR)&bmi, sizeof(bmi),&bw,NULL);
		
      bmi.biBitCount=32;
		
      if (hbm32 = CreateDIBSection(imgDC, (BITMAPINFO*)&bmi, DIB_RGB_COLORS, &pbits32, NULL, 0) )
      {
         BYTE   *p32 = (BYTE *)pbits32;
         LONG   *p;
         unsigned int   i,j,h=0;
			
         buffer=(unsigned   char*)malloc(TotalDataBytes);
         holdBmp = (HBITMAP)SelectObject(imgDC, hbm32);

         for (i = 0; i < m_imageCount; i++)
         {
            HDC hdc = CreateCompatibleDC( NULL );
            HBITMAP hOldBmp = (HBITMAP)SelectObject(hdc, images[i].hbmp);
            BitBlt(imgDC, images[i].x, images[i].y, images[i].bmp.bmWidth, images[i].bmp.bmHeight, hdc, 0, 0, SRCCOPY);	
            //DeleteObject(SelectObject(hdc, hOldBmp));
            DeleteDC(hdc);
         }
			
         for   (i = 0;i<height;   i++)
         {
            for   (j = 0;j<width;   j++)
            {
               p = (LONG   *)p32   +   j;
               buffer[h] = GetRValue(*p);
               buffer[h+1] = GetGValue(*p);
               buffer[h+2] = GetBValue(*p);
               h+=3;
            }
            if(Zero)h+=Zero;
            p32 += LineDataBytes;
         }
         WriteFile(hFile,(LPSTR)buffer, TotalDataBytes,&bw,NULL);
         DeleteObject(SelectObject(imgDC, holdBmp));
         free(buffer);
         result=TRUE;
      }
      CloseHandle(hFile);
   }
	
   DeleteDC(imgDC);
   return   result;
}


void func()
{
   // Create a normal DC and a memory DC for the entire screen. The 
   // normal DC provides a "snapshot" of the screen contents. The 
   // memory DC keeps a copy of this "snapshot" in the associated 
   // bitmap. 
 
   hdcScreen = CreateDC("DISPLAY", NULL, NULL, NULL); 
   hdcCompatible = CreateCompatibleDC(hdcScreen); 
 
   // Create a compatible bitmap for hdcScreen. 
 
   hbmScreen = CreateCompatibleBitmap(hdcScreen, 
                                      GetDeviceCaps(hdcScreen, HORZRES), 
                                      GetDeviceCaps(hdcScreen, VERTRES)); 
 
   if (hbmScreen == 0) 
      errhandler("hbmScreen", hwnd); 
 
   // Select the bitmaps into the compatible DC. 
 
   if (!SelectObject(hdcCompatible, hbmScreen)) 
      errhandler("Compatible Bitmap Selection", hwnd); 
 
   // Hide the application window. 
 
   ShowWindow(hwnd, SW_HIDE); 
 
   //Copy color data for the entire display into a 
   //bitmap that is selected into a compatible DC. 
 
   if (!BitBlt(hdcCompatible, 
               0,0, 
               bmp.bmWidth, bmp.bmHeight, 
               hdcScreen, 
               0,0, 
               SRCCOPY)) 
 
      errhandler("Screen to Compat Blt Failed", hwnd); 
 
   // Redraw the application window. 
 
   ShowWindow(hwnd, SW_SHOW); 
}

#endif

void find(HDC hdc, int width, int height)
{
   int w; int h;
	
   // 以“从左到右，从上到下”的循序扫描
   for( h = 0; h < height; h++){
      for( w = 0; w < width; w++){
			
         if( isEdge(GetPixel(hdc, w, h)) ) {
				
            // 棋盘的右边已经超过图片的宽度
            if( w + QQ_GO_19_EDGE_BIT_LENGTH - 1 > width ){
               continue;
            }
				
            // 棋盘的底已经超过图片的高度
            if( w + QQ_GO_19_EDGE_BIT_LENGTH - 1 > height ){
               continue;
            }
				
            // 判断是否为棋盘的横边
            int i;
            for(i = w + 1; i < w + QQ_GO_19_EDGE_BIT_LENGTH - 1; i++ ){
               if( !isEdge(GetPixel(hdc, i, h)) ) {
                  goto cont;
               }
            }
				
            // 判断是否为棋盘的横边
            int j;
            for(j = h + 1; j < h + QQ_GO_19_EDGE_BIT_LENGTH - 1; j++ ){
               if( !isEdge(GetPixel(hdc, w, j)) ) {
                  goto cont;
               }
            }
				
            // 找到棋盘
            printf("FOUND!/n");
            return;
           cont:
			;
         }
      }
   }
	
   // 没有找到
   printf("NOT FOUND!/n");
}

void test()
{
   HDC     hMemDC;     // 屏幕和内存设备描述表
   // 为屏幕设备描述表创建兼容的内存设备描述表
   hMemDC = CreateCompatibleDC(NULL);

   HBITMAP hBmp;
   hBmp = (HBITMAP)LoadImage( 0,//AfxGetInstanceHandle(), 
                              "c:\\1.bmp",
                              IMAGE_BITMAP,
                              0,
                              0,
                              LR_LOADFROMFILE);
   
   BITMAP bmp;
   GetObject(hBmp, sizeof(BITMAP), &bmp);

   // 把新位图选到内存设备描述表中
   HBITMAP hOldBitmap = (HBITMAP)::SelectObject(hMemDC, hBmp);
   find(hMemDC, bmp.bmWidth, bmp.bmHeight);
   hBmp = (HBITMAP)::SelectObject(hMemDC, hOldBitmap);
}

int main()
{
#if 0
   RECT rect;
   rect.left = 0;
   rect.top = 0;
   rect.right = 1080;
   rect.bottom = 800;
   CopyScreenToBitmap(&rect);
#endif 
   test();
   return 0;
}
