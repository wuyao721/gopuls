/**
 * @file   ActiveObjectShell.h
 * @author WuYao <wuyao721@163.com>
 * @date   Tue Jan 17 11:41:40 2012
 * 
 * @brief  shell of active object
 * 
 * 
 */

#ifndef _ACTIVE_OBJECT_SHELL_H_
#define _ACTIVE_OBJECT_SHELL_H_

#include "Poco/Mutex.h"
#include "Poco/Format.h"
#include "Poco/Activity.h"
#include "Poco/TaskNotification.h"

class ActiveObjectShell
{
public:

   /** 
    * construct
    * 
    */
   ActiveObjectShell();

   /** 
    * start 
    */
   void start();

   /** 
    * stop
    */
   void stop();

   /** 
    * whether running
    */
   bool isRunning();

protected:

   /** 
    * 
    * 
    */
   virtual void run();

private:
   void runActivity();

   Poco::Activity<ActiveObjectShell> _activity;
};

#endif /* end of ActiveObjectShell.h */
