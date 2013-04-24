/**
 * @file   MainDialog.h
 * @author WuYao <wuyao721@163.com>
 * @date   Mon Feb 13 14:30:53 2012
 * 
 * @brief  
 * 
 * 
 */


#ifndef _MAIN_DIALOG_H_
#define _MAIN_DIALOG_H_

#include "BaseDialog.h"
#include "SettingDialog.h"

#include "GoPlusContext.h"
#include "GoGameWatcher.h"
#include "StatusNotification.h"

class MainDialog: public BaseDialog
{
public:
   /** 
    * 
    * 
    * @param hInst 
    */
   MainDialog(HINSTANCE hInst);

   /** 
    * 
    * 
    * 
    */
   ~MainDialog();

   /** 
    * 
    * 
    * 
    * @return 
    */
   virtual bool initDialog();

   /** 
    * 
    * 
    */
   void showMenu();

private:

   HWND _hWndStatusBar;
   GoPlusContext& _context;
   NOTIFYICONDATA niData; // notify icon data
   SettingDialog _settingDialog;

   // 
   GoGameWatcher _watcher;

   /** 
    * 
    * 
    */
   void initNotifyIcon();

   /** 
    * show menu
    * 
    */
   void ShowContextMenu();

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
   virtual LRESULT CALLBACK WinMsgHandler(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

   /** 
    * 
    * 
    * @param pNf 
    */
   void updateStatus(const Poco::AutoPtr<StatusNotification>& pNf);

   /** 
    * 
    * 
    * @param pNf 
    */
   void updateCapturesInformation(const Poco::AutoPtr<CapturesNotification>& pNf);

   /** 
    * 
    * 
    * @param pNf 
    */
   void updateScore(const Poco::AutoPtr<ScoreNotification>& pNf);
};

#endif /* end of MainDialog.h */
