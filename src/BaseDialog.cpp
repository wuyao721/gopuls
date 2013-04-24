#include "BaseDialog.h"

BaseDialog::BaseDialog(HINSTANCE hInst):
   _hInstance(hInst),
   _hWnd(NULL)
{ 
}

/*
	You can not initialize the window class with a class method as the window 
	procedure unless it is a static method, so the class also needs a static 
	message handler that determines which instance of the class is the recipient 
	of the message and calls that instance's window procedure.

	See "http://www.gamedev.net/reference/articles/article1810.asp" for more info.
*/
LRESULT CALLBACK BaseDialog::stWinMsgHandler(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	BaseDialog* pWnd;

	// get the pointer to the window
	pWnd = GetObjectFromWindow(hwnd);

	// if we have the pointer, go to the message handler of the window
	// else, use DefWindowProc
	if (pWnd)
		return pWnd->WinMsgHandler(hwnd, uMsg, wParam, lParam);
	else
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

bool BaseDialog::create(int id)
{ 
   // store instance handle and create dialog
   _hWnd = CreateDialog( _hInstance, MAKEINTRESOURCE(id),
                             NULL, (DLGPROC)BaseDialog::stWinMsgHandler );
   if (!_hWnd) return false;

   // get the pointer to the window from lpCreateParams which was set in CreateWindow
   SetWindowLong(_hWnd, GWL_USERDATA, (long)(this));

   return true;
}

void BaseDialog::show(bool s)
{
   if(s){
      ShowWindow(_hWnd, SW_SHOW);
      SetForegroundWindow(_hWnd);
   }else{
      ShowWindow(_hWnd, SW_HIDE);
   }
}
