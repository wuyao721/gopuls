#include <windows.h>

#include "res/resource.h"
#include "GoPlusContext.h"
#include "MainDialog.h"
//#include "SettingDialog.h"

HWND				InitSettingDialog(HINSTANCE, int);


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
   MainDialog mainDialog(hInstance);
   //mainDialog.create();

   //if (!InitInstance (hInstance, nCmdShow)) return FALSE;
   //if (! (g_hwndsetting = InitSettingDialog (hInstance, nCmdShow))) return FALSE;
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
