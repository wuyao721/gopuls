/**
 * @file   GoPlusShell.h
 * @author WuYao <wuyao721@163.com>
 * @date   Tue Jan 17 11:41:40 2012
 * 
 * @brief  shell of goplus
 * 
 * 
 */

#ifndef _ACTIVE_OBJECT_SHELL_H_
#define _ACTIVE_OBJECT_SHELL_H_

#include "Poco/Mutex.h"
#include "Poco/Format.h"
#include "Poco/Activity.h"
#include "Poco/TaskNotification.h"

class GoPlusShell
{
public:

   /** 
    * construct
    * 
    */
   GoPlusShell();

protected:

   /** 
    * 
    * 
    */
   void run();
};

#endif /* end of GoPlusShell.h */
