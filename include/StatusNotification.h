#ifndef _STATUS_NOTIFICATION_H_
#define _STATUS_NOTIFICATION_H_

#include "Poco/NotificationCenter.h"
#include "Poco/Notification.h"
#include "Poco/Observer.h"
#include "Poco/NObserver.h"
#include "Poco/AutoPtr.h"
using Poco::NotificationCenter;
using Poco::Notification;
using Poco::Observer;
using Poco::NObserver;
using Poco::AutoPtr;

class StatusNotification: public Poco::Notification
{
public:
   StatusNotification(const std::string& str)
   {
      des = str;
   }

   std::string des;
};

class CapturesNotification: public Poco::Notification
{
public:
   CapturesNotification(int black, int white)
   {
      _black = black;
      _white = white;
   }

   int _black;
   int _white;
};


class ScoreNotification: public Poco::Notification
{
public:
   ScoreNotification(const std::string& str)
   {
      des = str;
   }

   std::string des;
};

#endif /* end of StatusNotification.h */
