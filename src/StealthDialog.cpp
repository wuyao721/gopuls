/**
 * @file   StealthDialog.cpp
 * @author WuYao <wuyao721@163.com>
 * @date   Tue Jan 17 10:05:01 2012
 * 
 * @brief  stealth dialog, thanks to http://www.codeproject.com/KB/shell/StealthDialog.aspx
 * 
 * 
 */

#include <windows.h>
#include <Windowsx.h>
#include <commctrl.h>
#include <Shellapi.h>
#include <Shlwapi.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include "GoPlusContext.h"

#include "res/resource.h"

#define TRAYICONID	1//				ID number for the Notify Icon
#define SWM_TRAYMSG	WM_APP//		the message ID sent to our window

#define SWM_MAIN	WM_APP + 1//	show the main window
#define SWM_ABOUT	WM_APP + 2//	about
#define SWM_EXIT	WM_APP + 3//	close the window
#define SWM_SETTING	WM_APP + 4//	show setting windows

#include "GoGameWatcher.h"
GoGameWatcher g_watcher;

// Global Variables:
HINSTANCE		hInst;	// current instance
NOTIFYICONDATA	niData;	// notify icon data

// Forward declarations of functions included in this code module:
BOOL				InitInstance(HINSTANCE, int);
BOOL				OnInitDialog(HWND hWnd);
void				ShowContextMenu(HWND hWnd);
ULONGLONG			GetDllVersion(LPCTSTR lpszDllName);

INT_PTR CALLBACK	DlgProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

HWND				InitSettingDialog(HINSTANCE, int);

HWND g_hwndsetting;

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
   MSG msg;
   HACCEL hAccelTable;

   GoPlusContext& context = GoPlusContext::instance();
   context.init();

   // Perform application initialization:
   if (!InitInstance (hInstance, nCmdShow)) return FALSE;
   if (! (g_hwndsetting = InitSettingDialog (hInstance, nCmdShow))) return FALSE;

   hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_STEALTHDIALOG);

   // Main message loop:
   while (GetMessage(&msg, NULL, 0, 0))
   {
      if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)||
          !IsDialogMessage(msg.hwnd,&msg) ) 
      {
         TranslateMessage(&msg);
         DispatchMessage(&msg);
      }
   }
   return (int) msg.wParam;
}


//	Initialize the window and tray icon
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   // store instance handle and create dialog
   hInst = hInstance;
   HWND hWnd = CreateDialog( hInstance, MAKEINTRESOURCE(IDD_DIALOG_MAIN),
                             NULL, (DLGPROC)DlgProc );
   if (!hWnd) return FALSE;

   // Fill the NOTIFYICONDATA structure and call Shell_NotifyIcon

   // zero the structure - note:	Some Windows funtions require this but
   //								I can't be bothered which ones do and
   //								which ones don't.
   ZeroMemory(&niData,sizeof(NOTIFYICONDATA));

   // get Shell32 version number and set the size of the structure
   //		note:	the MSDN documentation about this is a little
   //				dubious and I'm not at all sure if the method
   //				bellow is correct
   ULONGLONG ullVersion = GetDllVersion("Shell32.dll");
   if(ullVersion >= MAKEDLLVERULL(5, 0,0,0))
      niData.cbSize = sizeof(NOTIFYICONDATA);
   else niData.cbSize = NOTIFYICONDATA_V2_SIZE;

   // the ID number can be anything you choose
   niData.uID = TRAYICONID;

   // state which structure members are valid
   niData.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;

   // load the icon
   niData.hIcon = (HICON)LoadImage(hInstance,MAKEINTRESOURCE(IDI_STEALTHDLG),
                                   IMAGE_ICON, GetSystemMetrics(SM_CXSMICON),GetSystemMetrics(SM_CYSMICON),
                                   LR_DEFAULTCOLOR);

   // the window to send messages to and the message to send
   //		note:	the message value should be in the
   //				range of WM_APP through 0xBFFF
   niData.hWnd = hWnd;
   niData.uCallbackMessage = SWM_TRAYMSG;

   // tooltip message
   lstrcpyn(niData.szTip, "Time flies like an arrow but\n   fruit flies like a banana!", sizeof(niData.szTip)/sizeof(TCHAR));

   Shell_NotifyIcon(NIM_ADD,&niData);

   // free icon handle
   if(niData.hIcon && DestroyIcon(niData.hIcon))
      niData.hIcon = NULL;

   // call ShowWindow here to make the dialog initially visible

   return TRUE;
}

BOOL OnInitDialog(HWND hWnd)
{
   RECT rect;
   int width = GetSystemMetrics(SM_CXSCREEN);
   int height = GetSystemMetrics(SM_CYSCREEN);
   GetWindowRect(hWnd, &rect);
   SetWindowPos(hWnd, 0, width-(rect.right-rect.left), height/2-(rect.bottom-rect.top)/2, 0, 0, SWP_NOSIZE);

   GoPlusContext& context = GoPlusContext::instance();

   Button_SetCheck(GetDlgItem(hWnd, IDC_RADIO_BLACK), BST_UNCHECKED);
   Button_SetCheck(GetDlgItem(hWnd, IDC_RADIO_WHITE), BST_UNCHECKED);

   if( context.getGoPlayerKind() == "black" ){
      Button_SetCheck(GetDlgItem(hWnd, IDC_RADIO_BLACK), BST_CHECKED);
   }else if( context.getGoPlayerKind() == "white" ){
      Button_SetCheck(GetDlgItem(hWnd, IDC_RADIO_WHITE), BST_CHECKED);
   }

//   HMENU hMenu = GetSystemMenu(hWnd,FALSE);
//   if (hMenu)
//   {
//      AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);
//      AppendMenu(hMenu, MF_STRING, IDM_ABOUT, "About");
//   }
   HICON hIcon = (HICON)LoadImage(hInst,
                                  MAKEINTRESOURCE(IDI_STEALTHDLG),
                                  IMAGE_ICON, 0,0, LR_SHARED|LR_DEFAULTSIZE);
   SendMessage(hWnd,WM_SETICON,ICON_BIG,(LPARAM)hIcon);
   SendMessage(hWnd,WM_SETICON,ICON_SMALL,(LPARAM)hIcon);
   return TRUE;
}

// Name says it all
void ShowContextMenu(HWND hWnd)
{
   GoPlusContext& context = GoPlusContext::instance();

   POINT pt;
   GetCursorPos(&pt);
   HMENU hMenu = CreatePopupMenu();
   if(hMenu)
   {
//      if( g_screenCutter.isRunning() ){
//      if( g_watcher.isRunning() ){
//         InsertMenu(hMenu, -1, MF_BYPOSITION, SWM_STOP, "stop"));
//      }
//      else{
//         InsertMenu(hMenu, -1, MF_BYPOSITION, SWM_START, "start");
//      }
//
//      if( context.getGoPlayerKind() == "black" ){
//         InsertMenu(hMenu, -1, MF_BYPOSITION, SWM_BLACK, "black");
//      }else{
//         InsertMenu(hMenu, -1, MF_BYPOSITION, SWM_BLACK, "white");
//      }

      //IsWindowVisible(hWnd);

      InsertMenu(hMenu, -1, MF_BYPOSITION, SWM_MAIN, "打开");
      InsertMenu(hMenu, -1, MF_BYPOSITION, SWM_SETTING, "设置");

      InsertMenu(hMenu, -1, MF_BYPOSITION|MF_SEPARATOR, 0, "");

      InsertMenu(hMenu, -1, MF_BYPOSITION, SWM_ABOUT, "关于");
      InsertMenu(hMenu, -1, MF_BYPOSITION, SWM_EXIT, "退出");

      // note:	must set window to the foreground or the
      //			menu won't disappear when it should
      SetForegroundWindow(hWnd);

      TrackPopupMenu(hMenu, TPM_BOTTOMALIGN,
                     pt.x, pt.y, 0, hWnd, NULL );
      DestroyMenu(hMenu);
   }
}

// Get dll version number
ULONGLONG GetDllVersion(LPCTSTR lpszDllName)
{
   ULONGLONG ullVersion = 0;
   HINSTANCE hinstDll;
   hinstDll = LoadLibraryA(lpszDllName);
   if(hinstDll)
   {
      DLLGETVERSIONPROC pDllGetVersion;
      pDllGetVersion = (DLLGETVERSIONPROC)GetProcAddress(hinstDll, "DllGetVersion");
      if(pDllGetVersion)
      {
         DLLVERSIONINFO dvi;
         HRESULT hr;
         ZeroMemory(&dvi, sizeof(dvi));
         dvi.cbSize = sizeof(dvi);
         hr = (*pDllGetVersion)(&dvi);
         if(SUCCEEDED(hr))
            ullVersion = MAKEDLLVERULL(dvi.dwMajorVersion, dvi.dwMinorVersion,0,0);
      }
      FreeLibrary(hinstDll);
   }
   return ullVersion;
}

// Message handler for the app
INT_PTR CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
   GoPlusContext& context = GoPlusContext::instance();

   int wmId, wmEvent;

   switch (message) 
   {
      case SWM_TRAYMSG:
      {
         switch(lParam)
         {
            case WM_LBUTTONDBLCLK:
            {
               ShowWindow(hWnd, SW_SHOW);
               //DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
               break;
            }
            case WM_RBUTTONDOWN:
            case WM_CONTEXTMENU:
               ShowContextMenu(hWnd);
         }
         break;
      }
      case WM_SYSCOMMAND:
      {
         if((wParam & 0xFFF0) == SC_MINIMIZE)
         {
			ShowWindow(hWnd, SW_HIDE);
			return 1;
         }
         else if(wParam == IDM_ABOUT)
         {
			DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
            break;
         }
      }
      case WM_COMMAND:
      {
         wmId    = LOWORD(wParam);
         wmEvent = HIWORD(wParam); 

         switch (wmId)
         {
            case SWM_MAIN:
            {
               ShowWindow(hWnd, SW_SHOW);
               break;
            }

//            case SWM_START:
//            {
//               g_watcher.start();
//            }
//            break;
//               
//            case SWM_STOP:
//            {
//               g_watcher.stop();
//            }
//            break;
//
//            case SWM_BLACK:
//            case SWM_WHITE:
//            {
//               context.toggleGoPlayerKind();
//               break;
//            }
            case SWM_SETTING:
            {
               ShowWindow(g_hwndsetting, SW_SHOW);
               break;
            }
            case SWM_ABOUT:
            {
               DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
               break;
            }
            case SWM_EXIT:
            {
               DestroyWindow(hWnd);
               break;
            }
            case IDC_RADIO_BLACK:
            {
               if(wmEvent == BN_CLICKED){
                  context.setGoPlayerKind("black");
               }
               break;
            }
            case IDC_RADIO_WHITE:
            {
               if(wmEvent == BN_CLICKED){
                  context.setGoPlayerKind("white");
               }
               break;
            }
            case IDC_BUTTON_START_STOP:
            {
               static int i = 0;
               if( i == 0 ){
				   i++;
                  g_watcher.start();
                  Button_SetText(GetDlgItem(hWnd, IDC_BUTTON_START_STOP), "停止");
               }else{
                  i--;
                  g_watcher.stop();
                  Button_SetText(GetDlgItem(hWnd, IDC_BUTTON_START_STOP), "开始");
               }
               break;
            }
            case IDC_BUTTON_SETTING:
            {
               ShowWindow(g_hwndsetting, SW_SHOW);
               break;
            }
            default:
            {
			   return 0;
			}
         }
      }
      case WM_INITDIALOG:
      {
         return OnInitDialog(hWnd);
      }
      case WM_CLOSE:
      {
         //DestroyWindow(hWnd);
         ShowWindow(hWnd, SW_HIDE);
         break;
      }
      case WM_DESTROY:
      {
         niData.uFlags = 0;
         Shell_NotifyIcon(NIM_DELETE,&niData);
         PostQuitMessage(0);
         break;
      }
   }
   return 0;
}

// Message handler for about box.
LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
   switch (message)
   {
      case WM_INITDIALOG:
         return TRUE;

      case WM_COMMAND:
         if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) 
         {
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
         }
         break;
   }
   return FALSE;
}
