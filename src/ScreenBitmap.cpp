
#include <windows.h>
#include "ScreenBitmap.h"



/*
 * http://www.vckbase.com/document/viewdoc/?id=404 如何获取某个进程的主窗口以及创建进程的程序名
 * EnumWindows
 * GetWindowThreadProcessId
 * GetDC
 *
*/

//BOOL   CALLBACK   MyEnumProc(HWND   hwnd,   LPARAM   lParam   ) 
//{ 
//   DWORD ProcessID;
//   DWORD ThreadID;
//   ThreadID=GetWindowThreadProcessId(hWnd,&ProcessID);
//
//   GetWindowThreadProcessId
//}
//
//#include   "tlhelp32.h " 
//
//BOOL   GetProcess(int   nID)   
//{         
//   CString   strName; 
//   HANDLE   hProcessSnap=NULL; 
//   PROCESSENTRY32   pe32={0}; 
//   hProcessSnap=CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0); 
//   if(hProcessSnap==(HANDLE)-1) 
//   { 
//      ::MessageBox(NULL, "查询进程失败！:( ", "错误提示 ",MB_OK);   
//      return   FALSE; 
//   } 
//        pe32.dwSize=sizeof(PROCESSENTRY32); 
//        if(Process32First(hProcessSnap,&pe32)) 
//        { 
//                do 
//                { 
//                        if(nID==pe32.th32ProcessID)     //判断制定进程号 
//                            { 
//                                strName.Format( "进程编号%d的进程名为：%s ",nID,pe32.szExeFile); 
//                                AfxMessageBox(strName); 
//                            } 
//                } 
//                while(Process32Next(hProcessSnap,&pe32)); 
//        } 
//        else 
//        { 
//                ::MessageBox(NULL, "出现意外错误！ ", "错误提示 ",MB_OK); 
//                return   FALSE; 
//        } 
//        CloseHandle(hProcessSnap); 
//        return   TRUE; 
//} 
//

ScreenBitmap::ScreenBitmap():
   m_bits(NULL)
{
   HWND hWnd = GetDesktopWindow();
   HDC hdcScreen = GetDC(hWnd);
//   HDC hdcScreen = CreateDC("DISPLAY", NULL, NULL, NULL); 
   HDC hdcBuffer = CreateCompatibleDC(hdcScreen);
   int width = GetDeviceCaps(hdcScreen, HORZRES); 
   int height = GetDeviceCaps(hdcScreen, VERTRES);
   HBITMAP hBitmap = CreateCompatibleBitmap(hdcScreen, width, height);
   HBITMAP hBitTemp = (HBITMAP) SelectObject(hdcBuffer, hBitmap);

   BitBlt(hdcBuffer, 0, 0, width, height, hdcScreen, 0, 0, SRCCOPY);

   hBitmap = (HBITMAP) SelectObject(hdcBuffer, hBitTemp);

   GetObject( hBitmap, sizeof(BITMAP), &m_bmp);
   
   LONG bytes = m_bmp.bmWidthBytes * m_bmp.bmHeight;
   m_bits = new BYTE[bytes];

   GetBitmapBits( hBitmap, bytes, m_bits );

   DeleteObject(hBitmap);
   DeleteObject(hBitTemp);
   DeleteDC(hdcBuffer);
   //DeleteDC(hdcScreen);
   ReleaseDC(hWnd, hdcScreen);
}

ScreenBitmap::~ScreenBitmap()
{
   delete [] m_bits;
}

int ScreenBitmap::width()
{
   return m_bmp.bmWidth;
}

int ScreenBitmap::height()
{
   return m_bmp.bmHeight;
}

BYTE ScreenBitmap::getR(int x, int y)
{
   return *(m_bits + m_bmp.bmWidthBytes * y + 4 * x + 2);
}

BYTE ScreenBitmap::getG(int x, int y)
{
   return *(m_bits + m_bmp.bmWidthBytes * y + 4 * x + 1);
}

BYTE ScreenBitmap::getB(int x, int y)
{
   return *(m_bits + m_bmp.bmWidthBytes * y + 4 * x);
}
