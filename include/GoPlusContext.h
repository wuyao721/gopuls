/**
 * @file   GoPlusContext.h
 * @author WuYao <wuyao721@163.com>
 * @date   Mon Jan 30 13:56:51 2012
 * 
 * @brief  
 * 
 * 
 */

#ifndef _WGM_CONTEXT_H_
#define _WGM_CONTEXT_H_

#include <vector>

#include <Poco/NotificationCenter.h>
#include <Poco/Util/PropertyFileConfiguration.h>
#include <Poco/Util/IniFileConfiguration.h>
#include <Poco/RefCountedObject.h>
#include <Poco/AutoPtr.h>
#include <Poco/Logger.h>
#include <Poco/Path.h>
#include <Poco/Logger.h>
#include <Poco/LogStream.h>
#include <Poco/Format.h>

#include <list>

class GoPlusContext
{
public:
   
   /** 
    * 
    * singleton 
    * 
    * @return 
    */
   static GoPlusContext& instance();

   /** 
    * init
    * 
    */
   void init();

   /** 
    * finit
    * 
    */
   void finit();

   /** 
    * get notificationcenter
    * 
    * 
    * @return 
    */
   Poco::NotificationCenter& notificationCenter();

   /** 
   * get temp directory
   * 
   */
   std::string tmpDirectory();

   /** 
    * get go game boardsize 
    * 
    * 
    * @return 
    */
   int getBoardSize();

   /** 
    * set go game boardsize
    * 
    * @param boardsize 
    */
   void setBoardSize(int boardsize);

   /** 
    * get go AI engine command 
    * 
    * 
    * @return 
    */
   std::string getGoAIEngineCommand();

   /** 
    * get go AI engine command List
    * 
    * 
    * @return 
    */
   std::list<std::string> getGoAIEngineCommandList();

   /** 
    * set go AI engine command list
    * 
    * @param commandList 
    */
   void setGoAIEngineCommandList(std::list<std::string>& commandList);

   /** 
    * get go AI engine command index
    * 
    * 
    * @return 
    */
   int getGoAIEngineCommandIndex();
   
   /** 
    * set go AI engine command index
    * 
    * 
    * @return 
    */
   void setGoAIEngineCommandIndex(int index);

   /** 
    * get go board name 
    * 
    * 
    * @return 
    */
   std::string getGoBoardName();

   /** 
    * get go board name List
    * 
    * 
    * @return 
    */
   std::list<std::string> getGoBoardNameList();

   /** 
    * set go board name list
    * 
    * @param nameList 
    */
   void setGoBoardNameList(std::list<std::string>& nameList);

   /** 
    * get go board name index
    * 
    * 
    * @return 
    */
   int getGoBoardNameIndex();
   
   /** 
    * set go AI engine command index
    * 
    * 
    * @return 
    */
   void setGoBoardNameIndex(int index);
      
   /** 
    * whether auto play go game
    * 
    * 
    * @return 
    */
   bool isGoAutoPlay();

   /** 
    * set whether auto play go game
    * 
    * @param b 
    */
   void setGoAutoPlay(bool b);

   /** 
    * whether auto start go game
    * 
    * 
    * @return 
    */
   bool isGoAutoStart();

   /** 
    * set whether auto start go game
    * 
    * @param b 
    */
   void setGoAutoStart(bool b);

   /** 
    * whether auto pass one move
    * 
    * 
    * @return 
    */
   bool isGoAutoPass();

   /** 
    * set whether auto pass one move
    * 
    * @param b 
    */
   void setGoAutoPass(bool b);

   /** 
    * whether auto resign go game
    * 
    * 
    * @return 
    */
   bool isGoAutoResign();

   /** 
    * set whether auto resign go game
    * 
    * @param b 
    */
   void setGoAutoResign(bool b);

   /** 
    * whether auto mark go board
    * 
    * 
    * @return 
    */
   bool isGoAutoMark();

   /** 
    * set whether auto mark go board
    * 
    * @param b 
    */
   void setGoAutoMark(bool b);

   /** 
    * get go game player's kind(black or white)
    * 
    * 
    * @return 
    */
   std::string getGoPlayerKind();

   /** 
    * toggle go game player's kind(black or white)
    * 
    */
   void toggleGoPlayerKind();

   /** 
    * set go game player's kind(black or white)
    * 
    * @param b 
    * 
    * @return 
    */
   void setGoPlayerKind(const std::string& kind);

   /** 
    * get go board kind(ex. QQGo)
    * 
    * 
    * @return 
    */
   std::string getGoBoardKind();

   /** 
    * get logger's handler
    * 
    * 
    * @return 
    */
   Poco::Logger& logger();

private:

   /** 
    * init Logger
    * 
    */
   void initLogger();

   /** 
    * init filesystem
    * 
    */
   void initFileSystem();

   /** 
    * init databse
    * 
    */
   void initDatabase();

   /** 
    * finit database
    * 
    */
   void finitDatabase();

   /** 
    * init configure(Property format)
    * 
    */
   void initPropertyConf();

   /** 
    * set Logger
    * 
    * @param filepath logger file
    */
   void setLogger(const std::string& filepath);

   /** 
    * set logger level
    * 
    * @param level 
    */
   void setLoggerLevel(const std::string& level);

   // instance
   static GoPlusContext*                                   m_instance;

   // notificationcenter
   Poco::NotificationCenter m_nc;

   // configure handler
   Poco::AutoPtr<Poco::Util::PropertyFileConfiguration> m_pConf;
};

#define log_fatal(msg)                                                  \
   if (GoPlusContext::instance().logger().fatal()) GoPlusContext::instance().logger().fatal(msg); else (void) 0

#define log_critical(msg)                                               \
   if (GoPlusContext::instance().logger().critical()) GoPlusContext::instance().logger().critical(msg); else (void) 0

#define log_error(msg)                                                  \
   if (GoPlusContext::instance().logger().error()) GoPlusContext::instance().logger().error(msg); else (void) 0

#define log_warning(msg)                                                \
   if (GoPlusContext::instance().logger().warning()) GoPlusContext::instance().logger().warning(msg); else (void) 0
	
#define log_notice(msg)                                                 \
   if (GoPlusContext::instance().logger().notice()) GoPlusContext::instance().logger().notice(msg); else (void) 0

#define log_information(msg)                                            \
   if (GoPlusContext::instance().logger().information()) GoPlusContext::instance().logger().information(msg); else (void) 0

#if defined(_DEBUG)
#define log_debug(msg)                                                  \
   if (GoPlusContext::instance().logger().debug()) GoPlusContext::instance().logger().debug(msg); else (void) 0

#define log_trace(msg)                                                  \
   if (GoPlusContext::instance().logger().trace()) GoPlusContext::instance().logger().trace(msg); else (void) 0
#else
#define log_debug(msg)
#define log_trace(msg)
#endif

#endif /* end of GoPlusContext.h */
