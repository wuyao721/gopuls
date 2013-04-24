#include "ScreenCutter.h"

#include "QQGoBoard.h"

ScreenCutter::ScreenCutter(): 
   m_state(THREAD_STATE_STOPPED)
{

}

void ScreenCutter::init()
{
   setupInterval();
}

void ScreenCutter::run()
{
   Poco::Mutex::ScopedLock lock(m_mutex);

   m_state = THREAD_STATE_RUNNING;

   for(;;){
      m_cond.tryWait(m_mutex, m_interval);
      if( m_state == THREAD_STATE_STOPPING ){
         m_state = THREAD_STATE_STOPPED;
         m_cond.broadcast();
         return;
      }

      QQGoBoard19* goBoard19 = dynamic_cast<QQGoBoard19*>(QQGoBoard::instance());
      if( goBoard19 ){
         goBoard19->scan();
         goBoard19->print();
      }
   }
}

void ScreenCutter::start()
{
   {
      Poco::Mutex::ScopedLock lock(m_mutex);
      if( m_state == THREAD_STATE_RUNNING ){
         return;
      }
   }
   Poco::ThreadPool::defaultPool().start(*this, "thread11");
}

void ScreenCutter::stop()
{
   Poco::Mutex::ScopedLock lock(m_mutex);   
   if( m_state != THREAD_STATE_RUNNING ){
      return;
   }
   m_state = THREAD_STATE_STOPPING;
   m_cond.broadcast();
   while( m_state != THREAD_STATE_STOPPED ){
      m_cond.tryWait(m_mutex, 1000);
   }
}

int ScreenCutter::state()
{
   Poco::Mutex::ScopedLock lock(m_mutex);
   return m_state;
}

bool ScreenCutter::isRunning()
{
   return ( m_state == THREAD_STATE_RUNNING );
}

void ScreenCutter::setupInterval()
{
   m_interval = 2;   
}
