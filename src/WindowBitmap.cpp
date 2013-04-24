#include <windows.h>
#include <Tlhelp32.h>

#include "WindowBitmap.h"

WindowBitmap::WindowBitmap(HWND hWnd, bool directx):
   _hWnd(hWnd),
   m_bits(NULL)
{
   HDC hdcWindow = GetWindowDC(hWnd);
   HDC hdcBuffer = CreateCompatibleDC(hdcWindow);

   RECT windowRect;
   int windowWidth, windowHeight;

   GetWindowRect(hWnd, &windowRect);
   windowWidth = windowRect.right - windowRect.left;
   windowHeight = windowRect.bottom - windowRect.top;

   _hBitmap = CreateCompatibleBitmap(hdcWindow, windowWidth, windowHeight);
   HBITMAP hBitTemp = (HBITMAP) SelectObject(hdcBuffer, _hBitmap);

   if(directx){
      BitBlt(hdcBuffer, 0, 0, windowWidth, windowHeight, hdcWindow, 0, 0, SRCCOPY);
   }else{
      PrintWindow(hWnd, hdcBuffer, 0);  
   }

   _hBitmap = (HBITMAP) SelectObject(hdcBuffer, hBitTemp);
   //WindowBitmap::saveHBitmap2File(_hBitmap, "my.bmp");

   GetObject( _hBitmap, sizeof(BITMAP), &m_bmp);
   
   LONG bytes = m_bmp.bmWidthBytes * m_bmp.bmHeight;
   m_bits = new BYTE[bytes];

   GetBitmapBits( _hBitmap, bytes, m_bits );

   //WindowBitmap::saveHBitmap2File(_hBitmap, "my.bmp");

   DeleteObject(hBitTemp);
   DeleteDC(hdcBuffer);
   ReleaseDC(hWnd, hdcWindow);
}

WindowBitmap::~WindowBitmap()
{
   DeleteObject(_hBitmap);
   delete [] m_bits;
}

void WindowBitmap::click(int x, int y)
{
   SendMessage(_hWnd, WM_LBUTTONDOWN, MK_LBUTTON, MAKELONG(x,y)); 
   SendMessage(_hWnd, WM_LBUTTONUP, MK_LBUTTON, MAKELONG(x,y)); 
}

void WindowBitmap::clickScreenRelateToWindow(int x, int y)
{
   RECT windowRect;
   GetWindowRect(_hWnd, &windowRect);

   POINT lpPoint;
   GetCursorPos(&lpPoint);

   SetCursorPos(x + windowRect.left, y + windowRect.top);
   mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);

   SetCursorPos(lpPoint.x, lpPoint.y);
}

void WindowBitmap::clickScreen(HWND hWnd, int x, int y)
{
   RECT windowRect;
   GetWindowRect(hWnd, &windowRect);

   POINT lpPoint;
   GetCursorPos(&lpPoint);

   SetCursorPos(x + windowRect.left, y + windowRect.top);
   mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);

   SetCursorPos(lpPoint.x, lpPoint.y);
}

void WindowBitmap::clickScreen(int x, int y)
{
   POINT lpPoint;
   GetCursorPos(&lpPoint);

   SetCursorPos(x, y);
   mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);

   SetCursorPos(lpPoint.x, lpPoint.y);
}

void WindowBitmap::drawRectangle(int left, int top, int right, int bottom)
{
   // 获取一个可供画图的DC，我这里就直接用桌面算了
   HDC hdc = GetWindowDC( _hWnd );

   //HDC hdc = CreateDC("DISPLAY", NULL, NULL, NULL);
   // 创建实线画笔
   HPEN hpen1 = CreatePen( PS_SOLID, 1, RGB(255,0,0) );
   // 创建一个实体画刷
   HBRUSH hbrush1 = CreateSolidBrush( RGB(255,0,0) );

   // 将hpen1和hbrush1选进HDC，并保存HDC原来的画笔和画刷
   HPEN hpen_old = (HPEN)SelectObject( hdc, hpen1 );
   HBRUSH hbrush_old = (HBRUSH)SelectObject( hdc, hbrush1 );

   // 画一个矩形
   Rectangle( hdc, left, top, right, bottom );

   // 恢复原来的画笔和画刷
   SelectObject( hdc, hpen_old );
   SelectObject( hdc, hbrush_old );
   ReleaseDC(_hWnd, hdc);
}

//void GoBoard::draw_debug()
//{
//   // 获取一个可供画图的DC，我这里就直接用桌面算了
//   HDC hdc = GetWindowDC( GetDesktopWindow() );
//
//   //HDC hdc = CreateDC("DISPLAY", NULL, NULL, NULL);
//   // 创建实线画笔
//   HPEN hpen1 = CreatePen( PS_SOLID, 1, RGB(255,0,0) );
//   // 创建一个实体画刷
//   HBRUSH hbrush1 = CreateSolidBrush( RGB(255,0,0) );
//
//   // 将hpen1和hbrush1选进HDC，并保存HDC原来的画笔和画刷
//   HPEN hpen_old = (HPEN)SelectObject( hdc, hpen1 );
//   HBRUSH hbrush_old = (HBRUSH)SelectObject( hdc, hbrush1 );
//
//   int x, y;
//   for(y=0; y<_goGameFrame.boardsize();y++)
//   {
//      for(x=0;x<_goGameFrame.boardsize();x++){
//         int i,j;
//         int kind = _goGameFrame.getPieceKind(x,y);
//         if( GoGameRule::isKindEmpty(kind) ) continue;
//         i = _leftTopX + x * _gridLen;
//         j = _leftTopY + y * _gridLen;
//         // 画一个矩形
//         Rectangle( hdc, i-_gridLen/2, j-_gridLen/2, i+_gridLen/2, j+_gridLen/2 );
//
//
////         int kind = _goGameFrame.getPieceKind(j,i);
////         if( GoGameRule::isKindEmpty(kind) ) continue;
////
////         std::string str = GoGameRule::strOfCoordinate(_goGameFrame.boardsize(), j, i);
////         _ostr << "play" << " "
////    << GoGameRule::strOfKind(kind) << " " 
////               << str << std::endl;
////         // TODO: Error Handler
////
////         readDumpResponse();
//      }
//   }
//
//   // 恢复原来的画笔和画刷
//   SelectObject( hdc, hpen_old );
//   SelectObject( hdc, hbrush_old );
//   ReleaseDC(hdc);
//}

int WindowBitmap::width()
{
   return m_bmp.bmWidth;
}

int WindowBitmap::height()
{
   return m_bmp.bmHeight;
}

BYTE WindowBitmap::getR(int x, int y)
{
   return *(m_bits + m_bmp.bmWidthBytes * y + 4 * x + 2);
}

BYTE WindowBitmap::getG(int x, int y)
{
   return *(m_bits + m_bmp.bmWidthBytes * y + 4 * x + 1);
}

BYTE WindowBitmap::getB(int x, int y)
{
   return *(m_bits + m_bmp.bmWidthBytes * y + 4 * x);
}

BOOL CALLBACK matchProcessWindowEnumProc(HWND hWnd, LPARAM lParam) 
{ 
   DWORD ProcessID;
   DWORD ThreadID;
   HWndProcess *hWndProcess = (HWndProcess *)lParam;
   
   // 不可见、不可激活的窗口不作考虑。
   if ( !IsWindowVisible(hWnd) ){
      return true;
   }

   if ( !IsWindowEnabled(hWnd) ){
      return true;
   }

   // 弹出式窗口，但没有标题的不作考虑。
   LONG gwl_style = GetWindowLong( hWnd, GWL_STYLE );
   if ((gwl_style & WS_POPUP) && !(gwl_style & WS_CAPTION)){
      return true;
   }

   // 父窗口是可见或可激活的窗口不作考虑。
   HWND hParent = (HWND)GetWindowLong( hWnd, GWL_HWNDPARENT );
   if ( IsWindowEnabled(hParent) ){
      return true;
   }
   if ( IsWindowVisible(hParent) ){
      return true;
   }

//
//   // Shell_TrayWnd类的窗口（托盘里面的）不作考虑。
//   TCHAR szClassName[MAX_PATH];
//   GetClassName( hWnd, szClassName, MAX_PATH );
//   if ( !wcscmp(szClassName, _T("Shell_TrayWnd")) ){
//      return true;
//   }

   ThreadID = GetWindowThreadProcessId(hWnd,&ProcessID);
   if( ProcessID == hWndProcess->processID ){
	  hWndProcess->hWnd = hWnd;
	  RECT rect;
	  GetWindowRect(hWnd, &rect);
      return false;
   }
   return true;
}

BOOL CALLBACK matchProcessMessageBoxWindowEnumProc(HWND hWnd, LPARAM lParam) 
{ 
   DWORD ProcessID;
   DWORD ThreadID;
   HWndProcess *hWndProcess = (HWndProcess *)lParam;
   
   // 不可见、不可激活的窗口不作考虑。
   if ( !IsWindowVisible(hWnd) ){
      return true;
   }

   if ( !IsWindowEnabled(hWnd) ){
      return true;
   }

   // 弹出式窗口，但没有标题的不作考虑。
   LONG gwl_style = GetWindowLong( hWnd, GWL_STYLE );
   if ((gwl_style & WS_POPUP) && !(gwl_style & WS_CAPTION)){
      return true;
   }
   
   // message box can not MINIMIZE and MAXIMIZE
   if ((gwl_style & WS_MINIMIZEBOX) || (gwl_style & WS_MAXIMIZEBOX)){
      return true;
   }

   // 父窗口是可见或可激活的窗口不作考虑。
   HWND hParent = (HWND)GetWindowLong( hWnd, GWL_HWNDPARENT );
   if ( IsWindowEnabled(hParent) ){
      return true;
   }
   //if ( IsWindowVisible(hParent) ){
   //   return true;
   //}

//
//   // Shell_TrayWnd类的窗口（托盘里面的）不作考虑。
//   TCHAR szClassName[MAX_PATH];
//   GetClassName( hWnd, szClassName, MAX_PATH );
//   if ( !wcscmp(szClassName, _T("Shell_TrayWnd")) ){
//      return true;
//   }

   ThreadID = GetWindowThreadProcessId(hWnd,&ProcessID);
   if( ProcessID == hWndProcess->processID ){
	  hWndProcess->hWnd = hWnd;
	  RECT rect;
	  GetWindowRect(hWnd, &rect);
      return false;
   }
   return true;
}

DWORD getProcessIDFromName(const std::string& processName)   
{         
   HANDLE hProcessSnap = NULL;
   PROCESSENTRY32 pe32 = {0};
   DWORD processID = -1;
   
   hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
   if( hProcessSnap==(HANDLE)-1 ){
      return -1;
   }
   
   pe32.dwSize=sizeof(PROCESSENTRY32);
   if(Process32First(hProcessSnap,&pe32)){
      do{ 
         if( processName == pe32.szExeFile ){ 
            processID = pe32.th32ProcessID;
            goto end;
         }
      }
      while(Process32Next(hProcessSnap,&pe32)); 
   }

  end:
   CloseHandle(hProcessSnap); 
   return processID;
}

std::list<WindowBitmap> WindowBitmap::getWindowBitmapList(const std::string& process, bool directx)
{
   DWORD processID;
   std::list<WindowBitmap> windowBitmapList;
   HWndProcess hWndProcess;

   if( (processID = getProcessIDFromName(process)) == -1 ){
      goto end;
   }

   hWndProcess.processID = processID;
   if( false == EnumWindows(matchProcessWindowEnumProc, (LPARAM)&hWndProcess) ){
      //SendMessage(hWndProcess.hWnd, WM_LBUTTONDOWN, MK_LBUTTON, MAKELONG(100,100)); 
      //SendMessage(hWndProcess.hWnd, WM_LBUTTONUP, MK_LBUTTON, MAKELONG(100,100)); 
      windowBitmapList.push_back(WindowBitmap(hWndProcess.hWnd, directx));
   }
  end:
   return windowBitmapList;
}

WindowBitmap* WindowBitmap::getWindowBitmap(const std::string& process, bool directx)
{
   DWORD processID = -1;
   HWndProcess hWndProcess;
   WindowBitmap* windowBitmap = NULL;

   if( (processID = getProcessIDFromName(process)) == -1 ){
      return NULL;
   }

   hWndProcess.processID = processID;
   if( false == EnumWindows(matchProcessWindowEnumProc, (LPARAM)&hWndProcess) ){
      return new WindowBitmap(hWndProcess.hWnd, directx);
   }

   return NULL;
}

bool WindowBitmap::rgbEqual(int x1, int y1, int x2, int y2)
{
   int r1 = getR(x1, y1);
   int g1 = getG(x1, y1);
   int b1 = getB(x1, y1);

   int r2 = getR(x2, y2);
   int g2 = getG(x2, y2);
   int b2 = getB(x2, y2);

   return (r1 == r2) && (g1 == g2) && (b1 == b2);
}

bool WindowBitmap::rgbEqual(int x1, int y1, BYTE r, BYTE g, BYTE b)
{
   int r1 = getR(x1, y1);
   int g1 = getG(x1, y1);
   int b1 = getB(x1, y1);

   return (r1 == r) && (g1 == g) && (b1 == b);
}

bool WindowBitmap::rgbNear(int x1, int y1, BYTE r, BYTE g, BYTE b)
{
   int r1 = getR(x1, y1);
   int g1 = getG(x1, y1);
   int b1 = getB(x1, y1);

   return (abs(r1-r)<=10) && (abs(g1-g)<=10) && (abs(b1-b)<=10);
}


bool WindowBitmap::rgbLess(int x1, int y1, BYTE r, BYTE g, BYTE b)
{
   int r1 = getR(x1, y1);
   int g1 = getG(x1, y1);
   int b1 = getB(x1, y1);

   return (r1 < r) && (g1 < g) && (b1 < b);
}

bool WindowBitmap::rgbLarger(int x1, int y1, BYTE r, BYTE g, BYTE b)
{
   int r1 = getR(x1, y1);
   int g1 = getG(x1, y1);
   int b1 = getB(x1, y1);

   return (r1 > r) && (g1 > g) && (b1 > b);
}


bool WindowBitmap::saveHBitmap2File(HBITMAP hBitmap, const std::string& filepath)         
{
	HDC     hDC;

	//当前分辨率下每象素所占字节数
	int     iBits;

	//位图中每象素所占字节数
	WORD     wBitCount;

	//定义调色板大小，     位图中像素字节大小     ，位图文件大小     ，     写入文件字节数  
	DWORD     dwPaletteSize=0,   dwBmBitsSize=0,   dwDIBSize=0,   dwWritten=0;  

	//位图属性结构  
	BITMAP     Bitmap;      

	//位图文件头结构
	BITMAPFILEHEADER     bmfHdr;      

	//位图信息头结构  
	BITMAPINFOHEADER     bi;      

	//指向位图信息头结构      
	LPBITMAPINFOHEADER     lpbi;      

	//定义文件，分配内存句柄，调色板句柄  
	HANDLE     fh,   hDib,   hPal,hOldPal=NULL;  

	//计算位图文件每个像素所占字节数  
	hDC  = CreateDC("DISPLAY",   NULL,   NULL,   NULL);
	iBits = GetDeviceCaps(hDC, BITSPIXEL) * GetDeviceCaps(hDC, PLANES);
	DeleteDC(hDC);

	if(iBits <=  1){
		wBitCount = 1;
    }
	else  if(iBits <=  4){
		wBitCount  = 4;  
    }
	else if(iBits <=  8){
       wBitCount  = 8;
    }
	else{
       wBitCount  = 24;
    }

	GetObject(hBitmap,   sizeof(Bitmap),   (LPSTR)&Bitmap);
	bi.biSize= sizeof(BITMAPINFOHEADER);
	bi.biWidth = Bitmap.bmWidth;
	bi.biHeight =  Bitmap.bmHeight;
	bi.biPlanes =  1;
	bi.biBitCount = wBitCount;
	bi.biCompression= BI_RGB;
	bi.biSizeImage=0;
	bi.biXPelsPerMeter = 0;
	bi.biYPelsPerMeter = 0;
	bi.biClrImportant = 0;
	bi.biClrUsed =  0;

	dwBmBitsSize  = ((Bitmap.bmWidth *wBitCount+31) / 32)*4* Bitmap.bmHeight;

	//为位图内容分配内存  
	hDib  = GlobalAlloc(GHND,dwBmBitsSize+dwPaletteSize+sizeof(BITMAPINFOHEADER));  
	lpbi  = (LPBITMAPINFOHEADER)GlobalLock(hDib);  
	*lpbi  = bi;  

	//     处理调色板      
	hPal  = GetStockObject(DEFAULT_PALETTE);  
	if (hPal)  
	{  
		hDC  = ::GetDC(NULL);  
		hOldPal = ::SelectPalette(hDC,(HPALETTE)hPal, FALSE);  
		RealizePalette(hDC);  
	}

	//     获取该调色板下新的像素值  
	GetDIBits(hDC,hBitmap, 0,(UINT)Bitmap.bmHeight,  
		(LPSTR)lpbi+ sizeof(BITMAPINFOHEADER)+dwPaletteSize,   
		(BITMAPINFO *)lpbi, DIB_RGB_COLORS);  

	//恢复调色板      
	if (hOldPal)  
	{  
		::SelectPalette(hDC,   (HPALETTE)hOldPal,   TRUE);  
		RealizePalette(hDC);  
		::ReleaseDC(NULL,   hDC);  
	}  

	//创建位图文件      
	fh  = CreateFile(filepath.c_str(),   GENERIC_WRITE,0,   NULL,   CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN,   NULL);  

	if (fh == INVALID_HANDLE_VALUE) return true;  

	//     设置位图文件头  
	bmfHdr.bfType  = 0x4D42;     //     "BM"  
	dwDIBSize  = sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+dwPaletteSize+dwBmBitsSize;      
	bmfHdr.bfSize  = dwDIBSize;  
	bmfHdr.bfReserved1  = 0;  
	bmfHdr.bfReserved2  = 0;  
	bmfHdr.bfOffBits  = (DWORD)sizeof(BITMAPFILEHEADER)+(DWORD)sizeof(BITMAPINFOHEADER)+dwPaletteSize;  
	//     写入位图文件头  
	WriteFile(fh,   (LPSTR)&bmfHdr,   sizeof(BITMAPFILEHEADER),   &dwWritten,   NULL);  
	//     写入位图文件其余内容  
	WriteFile(fh,   (LPSTR)lpbi,   dwDIBSize,   &dwWritten,   NULL);  
	//清除      
	GlobalUnlock(hDib);  
	GlobalFree(hDib);  
	CloseHandle(fh);  

	return TRUE;
}
