#include "MainDialog.h"

#include <windowsx.h>
#include <commctrl.h>
#include <Shellapi.h>
#include <Shlwapi.h>

#include <Poco/Format.h>

#include "GoPlusContext.h"
#include "MetaMachine.h"

#include "res/resource.h"

#define TRAYICONID	1//				ID number for the Notify Icon
#define SWM_TRAYMSG	WM_APP//		the message ID sent to our window

#define SWM_MAIN	WM_APP + 1//	show the main window
#define SWM_ABOUT	WM_APP + 2//	about
#define SWM_EXIT	WM_APP + 3//	close the window
#define SWM_SETTING	WM_APP + 4//	show setting windows

// Get dll version number
static ULONGLONG GetDllVersion(LPCTSTR lpszDllName)
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

// Message handler for about box.
static LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
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

MainDialog::MainDialog(HINSTANCE hInst):
   BaseDialog(hInst),
   _settingDialog(hInst),
   _context(GoPlusContext::instance())
{ 
   _context.notificationCenter().addObserver(Poco::NObserver<MainDialog, StatusNotification>(*this, &MainDialog::updateStatus));
   _context.notificationCenter().addObserver(Poco::NObserver<MainDialog, CapturesNotification>(*this, &MainDialog::updateCapturesInformation));
   _context.notificationCenter().addObserver(Poco::NObserver<MainDialog, ScoreNotification>(*this, &MainDialog::updateScore));

   create(IDD_DIALOG_MAIN);
   initNotifyIcon();
   initDialog();
}

MainDialog::~MainDialog()
{
   _context.notificationCenter().removeObserver(Poco::NObserver<MainDialog, StatusNotification>(*this, &MainDialog::updateStatus));
}

   bool MainDialog::initDialog()
   {
      RECT rect;
      int width = GetSystemMetrics(SM_CXSCREEN);
      int height = GetSystemMetrics(SM_CYSCREEN);
      GetWindowRect(_hWnd, &rect);
      SetWindowPos(_hWnd, 0, width-(rect.right-rect.left), height/2-(rect.bottom-rect.top)/2, 0, 0, SWP_NOSIZE);

      Button_SetCheck(GetDlgItem(_hWnd, IDC_RADIO_BLACK), BST_UNCHECKED);
      Button_SetCheck(GetDlgItem(_hWnd, IDC_RADIO_WHITE), BST_UNCHECKED);

      if( _context.getGoPlayerKind() == "black" ){
         Button_SetCheck(GetDlgItem(_hWnd, IDC_RADIO_BLACK), BST_CHECKED);
      }else if( _context.getGoPlayerKind() == "white" ){
         Button_SetCheck(GetDlgItem(_hWnd, IDC_RADIO_WHITE), BST_CHECKED);
      }

//   HMENU hMenu = GetSystemMenu(hWnd,FALSE);
//   if (hMenu)
//   {
//      AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);
//      AppendMenu(hMenu, MF_STRING, IDM_ABOUT, "About");
//   }
      HICON hIcon = (HICON)LoadImage(_hInstance,
                                     MAKEINTRESOURCE(IDI_STEALTHDLG),
                                     IMAGE_ICON, 0,0, LR_SHARED|LR_DEFAULTSIZE);
      SendMessage(_hWnd,WM_SETICON,ICON_BIG,(LPARAM)hIcon);
      SendMessage(_hWnd,WM_SETICON,ICON_SMALL,(LPARAM)hIcon);

      //_hWndStatusBar = CreateStatusWindow(WS_CHILD | WS_BORDER | WS_VISIBLE, "test", _hWnd, IDC_STATUS_BAR);
      _hWndStatusBar = CreateWindowEx( 
         0L,                              // 无 扩展样式
         STATUSCLASSNAME,                 // 状态栏
         "",                              // 无 文本
         WS_CHILD | WS_VISIBLE,  // 样式
         -100, -100, 10, 10,              // x, y, cx, cy
         _hWnd,                            // 父 窗口
         (HMENU)IDC_STATUS_BAR,           // 窗口ID
         _hInstance,                      // 实 例句柄
         NULL);                           // 窗口数据

      return TRUE;
   }

void MainDialog::initNotifyIcon()
{
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
   niData.hIcon = (HICON)LoadImage(_hInstance,MAKEINTRESOURCE(IDI_STEALTHDLG),
                                   IMAGE_ICON, GetSystemMetrics(SM_CXSMICON),GetSystemMetrics(SM_CYSMICON),
                                   LR_DEFAULTCOLOR);

   // the window to send messages to and the message to send
   //		note:	the message value should be in the
   //				range of WM_APP through 0xBFFF
   niData.hWnd = _hWnd;
   niData.uCallbackMessage = SWM_TRAYMSG;

   // tooltip message
   lstrcpyn(niData.szTip, "Time flies like an arrow but\n   fruit flies like a banana!", sizeof(niData.szTip)/sizeof(TCHAR));

   Shell_NotifyIcon(NIM_ADD,&niData);

   // free icon handle
   if(niData.hIcon && DestroyIcon(niData.hIcon))
      niData.hIcon = NULL;

   // call ShowWindow here to make the dialog initially visible
}

void MainDialog::showMenu()
{
   POINT pt;
   GetCursorPos(&pt);
   HMENU hMenu = CreatePopupMenu();
   if(hMenu)
   {
      InsertMenu(hMenu, -1, MF_BYPOSITION, SWM_MAIN, "打开");
      InsertMenu(hMenu, -1, MF_BYPOSITION, SWM_SETTING, "设置");

      InsertMenu(hMenu, -1, MF_BYPOSITION|MF_SEPARATOR, 0, "");

      InsertMenu(hMenu, -1, MF_BYPOSITION, SWM_ABOUT, "关于");
      InsertMenu(hMenu, -1, MF_BYPOSITION, SWM_EXIT, "退出");

      // note:	must set window to the foreground or the
      //			menu won't disappear when it should
      SetForegroundWindow(_hWnd);

      TrackPopupMenu(hMenu, TPM_BOTTOMALIGN,
                     pt.x, pt.y, 0, _hWnd, NULL );
      DestroyMenu(hMenu);
   }
}

// the message handler for this window
LRESULT CALLBACK MainDialog::WinMsgHandler(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
   int wmId, wmEvent;

   switch (uMsg) 
   {
      case SWM_TRAYMSG:
      {
         switch(lParam)
         {
            case WM_LBUTTONDOWN:
            case WM_LBUTTONDBLCLK:
            {
               static int i = 0;
               if( i == 0 ){
                  i++;
                  ShowWindow(hWnd, SW_SHOW);
               }else{
                  i--;
                  ShowWindow(hWnd, SW_HIDE);
               }
               break;
            }
            case WM_RBUTTONDOWN:
            case WM_CONTEXTMENU:
            {
               showMenu();
               break;
            }
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
			DialogBox(_hInstance, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
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
            case SWM_SETTING:
			case IDC_BUTTON_SETTING:
			{
               _settingDialog.show(true);
               break;
            }
            case SWM_ABOUT:
            {
               DialogBox(_hInstance, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
               break;
            }
            case SWM_EXIT:
            {
               DestroyWindow(hWnd);
               break;
            }
            case IDC_BUTTON_ANALYSIS_SITUATION:
            {
               std::string str = MetaMachine::getDefault().estimateScore();
               SetWindowText(GetDlgItem(_hWnd, IDC_STATIC_OUTPUT), str.c_str());
               break;
            }
            case IDC_RADIO_BLACK:
            {
               if(wmEvent == BN_CLICKED){
                  _context.setGoPlayerKind("black");
               }
               break;
            }
            case IDC_RADIO_WHITE:
            {
               if(wmEvent == BN_CLICKED){
                  _context.setGoPlayerKind("white");
               }
               break;
            }
            case IDC_BUTTON_START_STOP:
            {
               static int i = 0;
               if( i == 0 ){
				   i++;
                  _watcher.start();
                  Button_SetText(GetDlgItem(hWnd, IDC_BUTTON_START_STOP), "停止");
               }else{
                  i--;
                  _watcher.stop();
                  Button_SetText(GetDlgItem(hWnd, IDC_BUTTON_START_STOP), "开始");
               }
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
         break;
         //return initDialog();
      }
      case WM_CLOSE:
      {
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

void MainDialog::updateStatus(const Poco::AutoPtr<StatusNotification>& pNf)
{
   SendMessage(_hWndStatusBar, SB_SETTEXT, 0, (LPARAM)pNf->des.c_str());
}

void MainDialog::updateCapturesInformation(const Poco::AutoPtr<CapturesNotification>& pNf)
{
   std::string strBlack;
   std::string strWhite;

   Poco::format(strBlack, "黑：%d", pNf->_black);
   Poco::format(strWhite, "白：%d", pNf->_white);
   SetWindowText(GetDlgItem(_hWnd, IDC_STATIC_CAPTURES_BLACK), strBlack.c_str());
   SetWindowText(GetDlgItem(_hWnd, IDC_STATIC_CAPTURES_WHITE), strWhite.c_str());
}

void MainDialog::updateScore(const Poco::AutoPtr<ScoreNotification>& pNf)
{
   SetWindowText(GetDlgItem(_hWnd, IDC_STATIC_OUTPUT), pNf->des.c_str());
}
