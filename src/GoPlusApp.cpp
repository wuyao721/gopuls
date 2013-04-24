#include <Poco/Process.h>
#include <Poco/NamedMutex.h>

#include "GoPlusApp.h"

GoPlusApp::GoPlusApp(): 
   _helpRequested(false)
{
}

GoPlusApp::~GoPlusApp()
{
}
	
void GoPlusApp::initialize(Application& self)
{
   loadConfiguration(); // load default configuration files, if present
   ServerApplication::initialize(self);
}
		
void GoPlusApp::uninitialize()
{
   ServerApplication::uninitialize();
}

void GoPlusApp::defineOptions(Poco::Util::OptionSet& options)
{
	using Poco::Util::Option;
	using Poco::Util::OptionSet;
	using Poco::Util::HelpFormatter;

	Poco::Util::ServerApplication::defineOptions(options);
		
   options.addOption(
      Option("help", "h", "display help information on command line arguments")
      .required(false)
      .repeatable(false));
}

void GoPlusApp::handleOption(const std::string& name, const std::string& value)
{
   ServerApplication::handleOption(name, value);

   if (name == "help")
      _helpRequested = true;
}

void GoPlusApp::displayHelp()
{
	Poco::Util::HelpFormatter helpFormatter(options());
   helpFormatter.setCommand(commandName());
   helpFormatter.setUsage("OPTIONS");
   helpFormatter.setHeader("WebGuard Monitor that protect websites from modify.");
   helpFormatter.format(std::cout);
}

int GoPlusApp::main(const std::vector<std::string>& args)
{
   if( _helpRequested ){
      displayHelp();
      return Application::EXIT_OK;
   }

   //WGMErrorHandler eh;
   //ErrorHandler* pOldEH = Poco::ErrorHandler::set(&eh);
   //WgmContext& context = WgmContext::instance();

   // 始化环境信息
   //context.init();

   //wgm_notice("BDGoPlusApp start.");

   m_goGameWatcher.start();
   // 初始化server
   //string ip = context.getIp();
   //UInt16 port = context.getPort();
   //if( port == 0 ){
   //   m_server.init();
   //}else{
   //   m_server.init(ip, port);
   //}
   
   //m_server.start();
   //m_timer.start();

   // wait for CTRL-C or kill
   waitForTerminationRequest();

   m_goGameWatcher.stop();

   // 停止所有模块
   //m_timer.stop();
   //m_server.stop(); // TCPServer::stop()可能导致线程等待，故注掉

   // 
   //context.finit();

   // Delete all global objects allocated by libprotobuf.
   //google::protobuf::ShutdownProtobufLibrary();

   //Poco::ErrorHandler::set(pOldEH);
   return Application::EXIT_OK;
}

int main(int argc, char** argv)
{
   GoPlusApp app;
   return app.run(argc, argv);
}
