#include <windows.h>

HBITMAP GetBitmapFromDC( HDC hDC, DWORD x, DWORD y, DWORD width, DWORD height )
{
   HDC hBufDC;
   HBITMAP hBitmap, hBitTemp;

   hBufDC = CreateCompatibleDC(hDC);

   hBitmap = CreateCompatibleBitmap(hDC, width, height);
   hBitTemp = (HBITMAP) SelectObject(hBufDC, hBitmap);

   BitBlt(hBufDC, 0, 0, width, height, hDC, x, y, SRCCOPY);

   hBitmap = (HBITMAP) SelectObject(hBufDC, hBitTemp);

   DeleteObject(hBitTemp);
   ::DeleteDC(hBufDC);

   return hBitmap;
}


void func()
{

// Create a normal DC and a memory DC for the entire screen. The 
// normal DC provides a "snapshot" of the screen contents. The 
// memory DC keeps a copy of this "snapshot" in the associated 
// bitmap. 
 
   HDC hdcScreen = CreateDC("DISPLAY", NULL, NULL, NULL); 
   HDC hdcCompatible = CreateCompatibleDC(hdcScreen); 
 
   HBITMAP k = GetBitmapFromDC( hdcScreen, 0, 0, GetDeviceCaps(hdcScreen, HORZRES), GetDeviceCaps(hdcScreen, VERTRES) );

   BITMAP b;
   GetObject( k, sizeof(BITMAP), &b);

   BYTE* cbBuffer = new   BYTE[b.bmWidthBytes*b.bmHeight];
   int j = GetBitmapBits(
      k,
      b.bmWidthBytes*b.bmHeight,
      cbBuffer
      );

// Create a compatible bitmap for hdcScreen. 
 
   HBITMAP hbmScreen = CreateCompatibleBitmap(hdcScreen, 
                                              GetDeviceCaps(hdcScreen, HORZRES), 
                                              GetDeviceCaps(hdcScreen, VERTRES)); 

   //if (hbmScreen == 0) 
   //   errhandler("hbmScreen", hwnd); 
 
// Select the bitmaps into the compatible DC. 
 
   //if (!SelectObject(hdcCompatible, hbmScreen)) {
   //return ;
   //}
   //errhandler("Compatible Bitmap Selection", hwnd); 
 
   // Hide the application window. 
   BITMAP m_bmp;
   GetObject( hbmScreen, sizeof(BITMAP), &m_bmp);
   int i = 1;
   i++;
#if 0
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
#endif
}

int main()
{
   func();
}
