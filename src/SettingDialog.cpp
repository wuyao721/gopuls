#include "SettingDialog.h"

#include <windowsx.h>
#include <commctrl.h>
#include <Shellapi.h>
#include <Shlwapi.h>

#include "GoPlusContext.h"

#include "res/resource.h"

SettingDialog::SettingDialog(HINSTANCE hInst):
   BaseDialog(hInst),
   _context(GoPlusContext::instance())
{ 
   create(IDD_DIALOG_SETTING);
   initDialog();
}

bool SettingDialog::initDialog()
{
   RECT rect;
   int width = GetSystemMetrics(SM_CXSCREEN);
   int height = GetSystemMetrics(SM_CYSCREEN);
   GetWindowRect(_hWnd, &rect);
   SetWindowPos(_hWnd, 0, width/2-(rect.right-rect.left)/2, height/2-(rect.bottom-rect.top)/2, 0, 0, SWP_NOSIZE);
   
   Button_SetCheck(GetDlgItem(_hWnd, IDC_CHECK_PROXY), BST_UNCHECKED);
   Button_SetCheck(GetDlgItem(_hWnd, IDC_CHECK_MARK), BST_UNCHECKED);
   Button_SetCheck(GetDlgItem(_hWnd, IDC_CHECK_AUTO_START), BST_UNCHECKED);
   Button_SetCheck(GetDlgItem(_hWnd, IDC_CHECK_AUTO_PASS), BST_UNCHECKED);
   Button_SetCheck(GetDlgItem(_hWnd, IDC_CHECK_AUTO_RESIGN), BST_UNCHECKED);

   // go proxy
   if(_context.isGoAutoPlay()){
      Button_SetCheck(GetDlgItem(_hWnd, IDC_CHECK_PROXY), BST_CHECKED);
   }

   // go mark
   if(_context.isGoAutoMark()){
      Button_SetCheck(GetDlgItem(_hWnd, IDC_CHECK_MARK), BST_CHECKED);
   }

   // go auto start
   if(_context.isGoAutoStart()){
      Button_SetCheck(GetDlgItem(_hWnd, IDC_CHECK_AUTO_START), BST_CHECKED);
   }
   // go auto start
   if(_context.isGoAutoPass()){
      Button_SetCheck(GetDlgItem(_hWnd, IDC_CHECK_AUTO_PASS), BST_CHECKED);
   }
   // go auto start
   if(_context.isGoAutoResign()){
      Button_SetCheck(GetDlgItem(_hWnd, IDC_CHECK_AUTO_RESIGN), BST_CHECKED);
   }

   // ai command list
   std::list<std::string> commandList = _context.getGoAIEngineCommandList();
   std::list<std::string>::iterator it;
   for( it=commandList.begin(); it!=commandList.end(); it++ ){
      SendMessage(GetDlgItem(_hWnd, IDC_COMBO_AI_ENGINE), (UINT) CB_ADDSTRING,(WPARAM) 0,(LPARAM) it->c_str()); 
   }
   SendMessage(GetDlgItem(_hWnd, IDC_COMBO_AI_ENGINE), CB_SETCURSEL, (WPARAM)_context.getGoAIEngineCommandIndex(), (LPARAM)0);

   // go board list
   std::list<std::string> nameList = _context.getGoBoardNameList();
   for( it=nameList.begin(); it!=nameList.end(); it++ ){
      SendMessage(GetDlgItem(_hWnd, IDC_COMBO_GO_BOARD), (UINT) CB_ADDSTRING,(WPARAM) 0,(LPARAM) it->c_str()); 
   }
   SendMessage(GetDlgItem(_hWnd, IDC_COMBO_GO_BOARD), CB_SETCURSEL, (WPARAM)_context.getGoBoardNameIndex(), (LPARAM)0);

   return true;
}

void SettingDialog::onOK()
{
   GoPlusContext& _context = GoPlusContext::instance();
   
   if( Button_GetCheck(GetDlgItem(_hWnd, IDC_CHECK_PROXY)) == BST_CHECKED ){
      _context.setGoAutoPlay(true);
   }else{
      _context.setGoAutoPlay(false);
   }

   if( Button_GetCheck(GetDlgItem(_hWnd, IDC_CHECK_MARK)) == BST_CHECKED ){
      _context.setGoAutoMark(true);
   }else{
      _context.setGoAutoMark(false);
   }

   if( Button_GetCheck(GetDlgItem(_hWnd, IDC_CHECK_AUTO_START)) == BST_CHECKED ){
      _context.setGoAutoStart(true);
   }else{
      _context.setGoAutoStart(false);
   }

   if( Button_GetCheck(GetDlgItem(_hWnd, IDC_CHECK_AUTO_PASS)) == BST_CHECKED ){
      _context.setGoAutoPass(true);
   }else{
      _context.setGoAutoPass(false);
   }

   if( Button_GetCheck(GetDlgItem(_hWnd, IDC_CHECK_AUTO_RESIGN)) == BST_CHECKED ){
      _context.setGoAutoResign(true);
   }else{
      _context.setGoAutoResign(false);
   }

   // ai engine command list, and index
   {
      int index = SendMessage(GetDlgItem(_hWnd, IDC_COMBO_AI_ENGINE), (UINT) CB_GETCURSEL, 
                              (WPARAM) 0, (LPARAM) 0);
      _context.setGoAIEngineCommandIndex(index);

      int i;
      char  ListItem[256];
      std::list<std::string> commandList;
      int count = ComboBox_GetCount(GetDlgItem(_hWnd, IDC_COMBO_AI_ENGINE));
      for( i=0; i<count; i++ ){
         (TCHAR) SendMessage(GetDlgItem(_hWnd, IDC_COMBO_AI_ENGINE), (UINT) CB_GETLBTEXT, 
                             (WPARAM) i, (LPARAM) ListItem);
         commandList.push_back(ListItem);
      }
      _context.setGoAIEngineCommandList(commandList);
   }

   // go board name list, and index
   {
      int index = SendMessage(GetDlgItem(_hWnd, IDC_COMBO_GO_BOARD), (UINT) CB_GETCURSEL, 
                              (WPARAM) 0, (LPARAM) 0);
      _context.setGoBoardNameIndex(index);

      int i;
      char ListItem[256];
      std::list<std::string> commandList;
      int count = ComboBox_GetCount(GetDlgItem(_hWnd, IDC_COMBO_GO_BOARD));
      for( i=0; i<count; i++ ){
         (TCHAR) SendMessage(GetDlgItem(_hWnd, IDC_COMBO_GO_BOARD), (UINT) CB_GETLBTEXT, 
                             (WPARAM) i, (LPARAM) ListItem);
         commandList.push_back(ListItem);
      }
      _context.setGoBoardNameList(commandList);
   }
}

// the message handler for this window
LRESULT CALLBACK SettingDialog::WinMsgHandler(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
   int i =0;
   int wmId, wmEvent;

   switch (uMsg) 
   {
      case WM_SYSCOMMAND:
         if((wParam & 0xFFF0) == SC_MINIMIZE)
         {
			ShowWindow(hWnd, SW_HIDE);
			return 1;
         }
      case WM_COMMAND:
      {
         wmId    = LOWORD(wParam);
         wmEvent = HIWORD(wParam); 

         switch (wmId)
         {
            case IDOK:
            {
               onOK();
               ShowWindow(hWnd, SW_HIDE);
               break;
            }
            case IDCANCEL:
            {
               ShowWindow(hWnd, SW_HIDE);
               break;
            }
         }
         break;
      }
      case WM_INITDIALOG:
      {
         break;
         //initDialog();
      }
      case WM_CLOSE:
      {
         ShowWindow(hWnd, SW_HIDE);
         break;
      }
      case WM_DESTROY:
      {
         DestroyWindow(hWnd);
         break;
      }
   }
   return 0;
}
