/**
 * @file   GoGameWatcher.h
 * @author WuYao <wuyao721@163.com>
 * @date   Thu Jan 05 17:15:52 2012
 * 
 * @brief  
 * 
 * 
 */

#ifndef _GO_GAME_WATCHER_H_
#define _GO_GAME_WATCHER_H_

#include <iostream>
#include <string>
#include <map>

#include "Poco/Mutex.h"
#include "Poco/Format.h"
#include "Poco/Activity.h"
#include "Poco/TaskNotification.h"
#include "GoPlusContext.h"

class GoGameWatcher
{
public:

   /** 
    * construct
    * 
    */
   GoGameWatcher();

   /** 
    * start spider manager
    * for Poco::Activity
    */
   void start();

   /** 
    * stopspider manager
    * for Poco::Activity
    */
   void stop();

   /** 
    * whether running
    * for Poco::Activity
    */
   bool isRunning();

private:
   void runActivity();

   GoPlusContext& _context;

   Poco::Mutex m_mutex;

   // activity
   Poco::Activity<GoGameWatcher> _activity;
};

#endif /* end of GoGameWatcher.h */
