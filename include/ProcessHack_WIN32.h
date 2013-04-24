#include <string>
#include <Poco/Pipe.h>

class ProcessHack
{
public:
   static void launch(const std::string& commandLine, Poco::Pipe* inPipe, Poco::Pipe* outPipe, Poco::Pipe* errPipe);
};
