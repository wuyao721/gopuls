
#ifndef _WGM_SCANNER_H_
#define _WGM_SCANNER_H_

#define THREAD_STATE_STOPPED 1
#define THREAD_STATE_RUNNING 2
#define THREAD_STATE_STOPPING 3

#include <Poco/Thread.h>
#include <Poco/ThreadPool.h>
#include <Poco/Runnable.h>
#include <Poco/Mutex.h>
#include <Poco/Condition.h>

/** 
 * 定时扫描
 * 
 */
class ScreenCutter: public Poco::Runnable
{
private:
   Poco::Mutex     m_mutex;
   Poco::Condition m_cond;

   int             m_state;     // 模块状态
   int             m_interval;  // 时间间隔

public:

   /** 
    * 构造函数
    * 
    * @param logSender 发送日志句柄
    * @param restorer 篡改处理句柄
    */
   ScreenCutter();

   /** 
    * 初始化
    * 
    */
   void init();
   
   /** 
    * 启动'定时扫描'模块，同时设置策略
    * 
    */
   void start();

   /** 
	* 停止'定时扫描'模块
	* 
	*/
   void stop();
   
   /** 
    * 获取状态
    * 
    * 
    * @return 状态
    */
   int state();
      
   /** 
    * 是否正在运行
    * 
    * 
    * @return 
    */
   bool isRunning();

   /** 
    * 处理线程
    * 
    */
   void run();

   /** 
    * 设置定时扫描时间间隔
    * 
    */
   void setupInterval();
};


#endif /* end of ScreenCutter.h */
