/**
 * @file   BaseDialog.h
 * @author WuYao <wuyao721@163.com>
 * @date   Mon Feb 13 14:51:28 2012
 * 
 * @brief  base class for my windows
 * 
 * 
 */

#ifndef _BASE_WINDOW_H_
#define _BASE_WINDOW_H_

#include <windows.h>

class BaseDialog
{
public:

   /** 
    * 
    * 
    * 
	* @param id 
	*
	* @return 
    */
   virtual bool create(int id);

   /** 
    *  init the dialog
    * 
    * 
    * @return 
    */
   virtual bool initDialog() = 0;

   /** 
    * show or hide
    * 
    * @param s 
    */
   void show(bool s);

   /** 
    * static message handler 
    * 
    * @param hwnd 
    * @param uMsg 
    * @param wParam 
    * @param lParam 
    * 
    * @return 
    */
   static LRESULT CALLBACK stWinMsgHandler(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

protected:
   HINSTANCE _hInstance;
   HWND _hWnd;

   /** 
    * 
    * 
    */
   BaseDialog(HINSTANCE hInst);

   /** 
    * the real message handler
    * 
    * @param hwnd 
    * @param uMsg 
    * @param wParam 
    * @param lParam 
    * 
    * @return 
    */
   virtual LRESULT CALLBACK WinMsgHandler(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;

   /** 
    * returns a pointer the window (stored as the WindowLong)
    * 
    * @param hWnd 
    * 
    * @return 
    */
   inline static BaseDialog *GetObjectFromWindow(HWND hWnd)
   {
      return (BaseDialog *)GetWindowLong(hWnd, GWL_USERDATA);
   }
};

#endif
