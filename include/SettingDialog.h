/**
 * @file   SettingDialog.h
 * @author WuYao <wuyao721@163.com>
 * @date   Mon Feb 13 14:30:53 2012
 * 
 * @brief  
 * 
 * 
 */


#ifndef _SETTING_DIALOG_H_
#define _SETTING_DIALOG_H_

#include "BaseDialog.h"

#include "GoPlusContext.h"

class SettingDialog: public BaseDialog
{
public:

   /** 
    * 
    * 
    * @param hInst 
    */
   SettingDialog(HINSTANCE hInst);

   /** 
    * 
    * 
    * 
    * @return 
    */
   virtual bool initDialog();

private:

   GoPlusContext& _context;

   /** 
    * 
    * 
    */
   void onOK();

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
};

#endif /* end of SettingDialog.h */
