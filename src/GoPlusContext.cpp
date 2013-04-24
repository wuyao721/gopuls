#include <Poco/File.h>
#include <Poco/Data/Common.h>
#include <Poco/Data/SQLite/Connector.h>
#include <Poco/ConsoleChannel.h>
#include <Poco/SimpleFileChannel.h>
#include <Poco/FormattingChannel.h>
#include <Poco/PatternFormatter.h>
#include <Poco/SingletonHolder.h>
#include <Poco/NumberParser.h>
#include <Poco/StringTokenizer.h>

#include "GoPlusContext.h"

#define CONF_FILE "conf/conf.properties"

GoPlusContext* GoPlusContext::m_instance = NULL;

GoPlusContext& GoPlusContext::instance()
{
   if( m_instance ){
      return *m_instance;
   }
   
   else{
      m_instance = new GoPlusContext;
      return *m_instance;
   }
}

void GoPlusContext::finit()
{
   finitDatabase();

   if( m_instance ){
      delete m_instance;
      m_instance = NULL;
   }
}

void GoPlusContext::init()
{
   // init logger
   initLogger();

   // init filesystem
   initFileSystem();

   // init database
   initDatabase();
   
   // init configure
   initPropertyConf();
}

void GoPlusContext::initFileSystem()
{
   //std::string confDir = Poco::Util::Application::instance().config().getString("application.dir") + "conf";
   //std::string dataDir = Poco::Util::Application::instance().config().getString("application.dir") + "data";
   //std::string logDir = Poco::Util::Application::instance().config().getString("application.dir") + "log";
   //std::string tmpDir = Poco::Util::Application::instance().config().getString("application.dir") + "tmp";
   std::string confDir = "conf";
   std::string dataDir = "data";
   std::string logDir = "log";
   std::string tmpDir = "tmp";

   Poco::File file; 

   file = confDir;
   file.createDirectories();

   file = dataDir;
   file.createDirectories();

   file = logDir;
   file.createDirectories();

   file = tmpDir;
   file.createDirectories();
}

Poco::NotificationCenter& GoPlusContext::notificationCenter()
{
   return m_nc;
}

std::string GoPlusContext::tmpDirectory()
{
   //std::string tmpDir = Poco::Util::Application::instance().config().getString("application.dir") + "tmp/";
   std::string tmpDir = "tmp/";

   return tmpDir;
}

void GoPlusContext::initDatabase()
{
   Poco::Data::SQLite::Connector::registerConnector();

   //FileDigestSession fileDigestSession;
   //fileDigestSession.create();
}

void GoPlusContext::finitDatabase()
{
   Poco::Data::SQLite::Connector::unregisterConnector();
}

void GoPlusContext::initPropertyConf()
{
   //std::string propertyPath = Poco::Util::Application::instance().config().getString("application.dir") + WRITE_CONF_FILE;
   std::string propertyPath = CONF_FILE;

   Poco::File file(propertyPath);

   if( file.exists() ){
      m_pConf = new Poco::Util::PropertyFileConfiguration(propertyPath);
   }else{
      m_pConf = new Poco::Util::PropertyFileConfiguration();
      //m_pConf->setInt("Go.BoardSize", 19);
      m_pConf->setString("Go.PlayerKind", "black");

      m_pConf->setBool("Action.AutoPlay", false);
      m_pConf->setBool("Action.AutoStart", false);
      m_pConf->setBool("Action.AutoPass", false);
      m_pConf->setBool("Action.AutoResign", false);
      m_pConf->setBool("Action.AutoMark", true);

      m_pConf->setString("Engine.CommandList", "engine/gnugo/gnugo.exe --mode gtp;engine/fuego/fuego.exe --quiet");
      m_pConf->setInt("Engine.CommandIndex", 0);
      
      m_pConf->setString("GoBoard.NameList", "QQÎ§Æå;ÞÄ³ÇÎ§Æå");
      m_pConf->setInt("GoBoard.NameIndex", 0);

      // logger file
      m_pConf->setString("Logger.Path", "log/goplus.log");
      m_pConf->setString("Logger.Level", "warning");

      m_pConf->save(propertyPath);
   }

   std::string filepath = m_pConf->getString("Logger.Path", "");
   if( filepath != "" ){
      //setLogger(Poco::Util::Application::instance().config().getString("application.dir") + filepath);
      setLogger(filepath);
   }

   std::string level = m_pConf->getString("Logger.Level", "warning");
   setLoggerLevel(level);
}

std::string GoPlusContext::getGoAIEngineCommand()
{
   std::string s = m_pConf->getString("Engine.CommandList", "");
   
   Poco::StringTokenizer tokens(s, ";");
   if( getGoAIEngineCommandIndex() >= tokens.count() ){
      return "engine/gnugo/gnugo.exe --mode gtp";
   }else{
      return tokens[getGoAIEngineCommandIndex()];
   }
}

std::list<std::string> GoPlusContext::getGoAIEngineCommandList()
{
   std::list<std::string> commandList;
   std::string s = m_pConf->getString("Engine.CommandList", "engine/gnugo/gnugo.exe --mode gtp;engine/fuego/fuego.exe --quiet");
   
   Poco::StringTokenizer tokens(s, ";");
   int i; 
   for( i=0; i<tokens.count(); i++ ){
      if(tokens[i] != "") commandList.push_back(tokens[i]);
   }

   return commandList;
}

void GoPlusContext::setGoAIEngineCommandList(std::list<std::string>& commandList)
{
   std::string s;

   std::list<std::string>::iterator it;
   for( it=commandList.begin(); it!=commandList.end(); it++ ){
      s += *it;
      s += ";";
   }

   m_pConf->setString("Engine.CommandList", s);
   m_pConf->save(CONF_FILE);
}   

int GoPlusContext::getGoAIEngineCommandIndex()
{
   return m_pConf->getInt("Engine.CommandIndex", 0);
}

void GoPlusContext::setGoAIEngineCommandIndex(int index)
{
   m_pConf->setInt("Engine.CommandIndex", index);
   m_pConf->save(CONF_FILE);
}

std::string GoPlusContext::getGoBoardName()
{
   std::string s = m_pConf->getString("GoBoard.NameList", "");
   
   Poco::StringTokenizer tokens(s, ";");
   if( getGoBoardNameIndex() >= tokens.count() ){
      return "QQÎ§Æå";
   }else{
      return tokens[getGoBoardNameIndex()];
   }
}

std::list<std::string> GoPlusContext::getGoBoardNameList()
{
   std::list<std::string> commandList;
   std::string s = m_pConf->getString("GoBoard.NameList", "QQÎ§Æå;ÞÄ³ÇÎ§Æå");
   
   Poco::StringTokenizer tokens(s, ";");
   int i; 
   for( i=0; i<tokens.count(); i++ ){
      if(tokens[i] != "") commandList.push_back(tokens[i]);
   }

   return commandList;
}

void GoPlusContext::setGoBoardNameList(std::list<std::string>& nameList)
{
   std::string s;

   std::list<std::string>::iterator it;
   for( it=nameList.begin(); it!=nameList.end(); it++ ){
      s += *it;
      s += ";";
   }

   m_pConf->setString("GoBoard.NameList", s);
   m_pConf->save(CONF_FILE);
}

int GoPlusContext::getGoBoardNameIndex()
{
   return m_pConf->getInt("GoBoard.NameIndex", 0);
}

void GoPlusContext::setGoBoardNameIndex(int index)
{
   m_pConf->setInt("GoBoard.NameIndex", index);
   m_pConf->save(CONF_FILE);
}

bool GoPlusContext::isGoAutoPlay()
{
   return m_pConf->getBool("Action.AutoPlay", false);
}

void GoPlusContext::setGoAutoPlay(bool b)
{
   m_pConf->setBool("Action.AutoPlay", b);
   m_pConf->save(CONF_FILE);
}

bool GoPlusContext::isGoAutoStart()
{
   return m_pConf->getBool("Action.AutoStart", false);
}

void GoPlusContext::setGoAutoStart(bool b)
{
   m_pConf->setBool("Action.AutoStart", b);
   m_pConf->save(CONF_FILE);
}

bool GoPlusContext::isGoAutoPass()
{
   return m_pConf->getBool("Action.AutoPass", false);
}

void GoPlusContext::setGoAutoPass(bool b)
{
   m_pConf->setBool("Action.AutoPass", b);
   m_pConf->save(CONF_FILE);
}

bool GoPlusContext::isGoAutoResign()
{
   return m_pConf->getBool("Action.AutoResign", false);
}

void GoPlusContext::setGoAutoResign(bool b)
{
   m_pConf->setBool("Action.AutoResign", b);
   m_pConf->save(CONF_FILE);
}

bool GoPlusContext::isGoAutoMark()
{
   return m_pConf->getBool("Action.AutoMark", true);
}

void GoPlusContext::setGoAutoMark(bool b)
{
   m_pConf->setBool("Action.AutoMark", b);
   m_pConf->save(CONF_FILE);
}

int GoPlusContext::getBoardSize()
{
   return m_pConf->getInt("Go.BoardSize", 19);
}

void GoPlusContext::setBoardSize(int boardsize)
{
   m_pConf->setInt("Go.BoardSize", boardsize);
   m_pConf->save(CONF_FILE);
}

std::string GoPlusContext::getGoPlayerKind()
{
   return m_pConf->getString("Go.PlayerKind", "black");
}

void GoPlusContext::toggleGoPlayerKind()
{
   std::string str = m_pConf->getString("Go.PlayerKind", "black");
   if(str == "black"){
      m_pConf->setString("Go.PlayerKind", "white");
   }else{
      m_pConf->setString("Go.PlayerKind", "black");
   }
}

void GoPlusContext::setGoPlayerKind(const std::string& kind)
{
   m_pConf->setString("Go.PlayerKind", kind);
}

void GoPlusContext::initLogger()
{
   using Poco::ConsoleChannel;
   using Poco::AutoPtr;
   using Poco::PatternFormatter;
   using Poco::SimpleFileChannel;
   using Poco::FormattingChannel;

   AutoPtr<ConsoleChannel> pChannel(new ConsoleChannel);
   AutoPtr<PatternFormatter> pPF(new PatternFormatter);

   // local time
   pPF->setProperty(Poco::PatternFormatter::PROP_TIMES, "local");

   // format
   pPF->setProperty("pattern", "[%Y-%m-%d %H:%M:%S] [%p] [Thread %I %T]: %t");

   // 
   AutoPtr<FormattingChannel> pFC = new FormattingChannel(pPF, pChannel);
   
   Poco::Logger& logger = Poco::Logger::get("MyLogger");

   // level
   logger.setLevel("warning");

   // channel
   logger.setChannel(pFC);
}

void GoPlusContext::setLogger(const std::string& filepath)
{
   using Poco::ConsoleChannel;
   using Poco::AutoPtr;
   using Poco::PatternFormatter;
   using Poco::SimpleFileChannel;
   using Poco::FormattingChannel;


   // SimpleFileChannel
   AutoPtr<SimpleFileChannel> pChannel(new SimpleFileChannel);
   pChannel->setProperty("path", filepath);
   pChannel->setProperty("rotation", "10 M");

   // Formatter
   AutoPtr<PatternFormatter> pPF(new PatternFormatter);
   pPF->setProperty(Poco::PatternFormatter::PROP_TIMES, "local");
   pPF->setProperty("pattern", "[%Y-%m-%d %H:%M:%S] [%p] [Thread %I %T]: %t");
   
   // 
   AutoPtr<FormattingChannel> pFC = new FormattingChannel(pPF, pChannel);

   Poco::Logger& logger = Poco::Logger::get("MyLogger");

   // 
   logger.setChannel(pFC);
}

void GoPlusContext::setLoggerLevel(const std::string& level)
{
   Poco::Logger& logger = Poco::Logger::get("MyLogger");

   // level
   try{
      logger.setLevel(level);
   }
   catch(...){
	   logger.setLevel("warning");
	   //wgm_error(format("Unkonw Logger Level: %s", level));
   }
}

Poco::Logger& GoPlusContext::logger()
{
   static Poco::Logger& logger = Poco::Logger::get("MyLogger");
   return logger;
}
