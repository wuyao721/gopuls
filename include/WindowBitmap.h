/**
 * @file   WindowBitmap.h
 * @author WuYao <wuyao721@163.com>
 * @date   Sat Feb 18 21:46:53 2012
 * 
 * @brief  window bitmap
 * 
 * 
 */

#ifndef _WINDOW_BITMAP_H_
#define _WINDOW_BITMAP_H_

#include "windows.h"

#include <list>
#include <string>


struct HWndProcess
{
   HWND hWnd;
   DWORD processID;
};

extern DWORD getProcessIDFromName(const std::string& processName);
extern BOOL CALLBACK matchProcessWindowEnumProc(HWND hWnd, LPARAM lParam);
extern BOOL CALLBACK matchProcessMessageBoxWindowEnumProc(HWND hWnd, LPARAM lParam);

class WindowBitmap
{
public:
   HWND _hWnd;
   HBITMAP _hBitmap;
   BITMAP m_bmp;
   BYTE* m_bits;

   int m_left;
   int m_top;

public:

   /** 
    * 
    * 
    * @param hWnd window hwnd, maybe windwGetDesktopWindow()
    */
   WindowBitmap(HWND hWnd, bool directx = false);

   /** 
    * 
    * 
    */
   ~WindowBitmap();
   
   /** 
    * click window's position(x, y)
    * 
    * @param x position refer to window
    * @param y position refer to window
    */
   void click(int x, int y);

   /** 
    * click window's position(x, y), but click on the screen
    * 
    * @param x position refer to window
    * @param y position refer to window
    */
   void clickScreenRelateToWindow(int x, int y);

   /** 
    * click window's position(x, y), but click on the screen
    * 
    * @param hWnd 
    * @param x position refer to window
    * @param y position refer to window
    */
   static void clickScreen(HWND hWnd, int x, int y);

   /** 
    * click screen's position(x, y)
    * 
    * @param x position refer to window
    * @param y position refer to window
    */
   static void clickScreen(int x, int y);

   /** 
    * draw rectangle above the window
    * 
    * @param left 
    * @param top 
    * @param right 
    * @param bottom 
    */
   void drawRectangle(int left, int top, int right, int bottom);

   /** 
    * 
    * 
    * @param x 
    * @param y 
    */
   //void draw_debug();

   /** 
    * get width
    * 
    * 
    * @return 
    */
   int width();

   /** 
    * get height
    * 
    * 
    * @return 
    */
   int height();
   
   /** 
    * get point's red ...
    * 
    * @param x 
    * @param y 
    * 
    * @return 
    */
   BYTE getR(int x, int y);

   /** 
    * get point's green ...
    * 
    * @param x 
    * @param y 
    * 
    * @return 
    */
   BYTE getG(int x, int y);

   /** 
    * get point's blue ...
    * 
    * @param x 
    * @param y 
    * 
    * @return 
    */
   BYTE getB(int x, int y);

   /** 
    * is rgb equal
    * 
    * @param x1 
    * @param y1 
    * @param x2 
    * @param y2 
    * 
    * @return 
    */
   bool rgbEqual(int x1, int y1, int x2, int y2);

   /** 
    * is rgb equal
    * 
    * @param x1 
    * @param y1
    * @param r 
    * @param g 
    * @param b 
    * 
    * @return 
    */
   bool rgbEqual(int x1, int y, BYTE r, BYTE g, BYTE b);

   /** 
    * is rgb near
    * 
    * @param x1 
    * @param y1
    * @param r 
    * @param g 
    * @param b 
    * 
    * @return 
    */
   bool rgbNear(int x1, int y, BYTE r, BYTE g, BYTE b);

   /** 
    * is rgb less than
    * 
    * @param x1 
    * @param y1 
    * @param r 
    * @param g 
    * @param b 
    * 
    * @return 
    */
   bool rgbLess(int x1, int y1, BYTE r, BYTE g, BYTE b);

   /** 
    * is rgb larger than
    * 
    * @param x1 
    * @param y1 
    * @param r 
    * @param g 
    * @param b 
    * 
    * @return 
    */
   bool rgbLarger(int x1, int y1, BYTE r, BYTE g, BYTE b);

   /** 
    * 
    * 
    * @param process 
    * 
    * @return 
    */
   static std::list<WindowBitmap> getWindowBitmapList(const std::string& process, bool directx = false);

   /** 
    * 
    * 
    * @param process 
    * 
    * @return 
    */
   static WindowBitmap* getWindowBitmap(const std::string& process, bool directx = false);
   
   /** 
    * 
    * 
    * @param hBitmap 
    * @param filepath 
    * 
    * @return 
    */
   static bool WindowBitmap::saveHBitmap2File(HBITMAP hBitmap, const std::string& filepath);
};
 

#endif /* end of WindowBitmap.h */
