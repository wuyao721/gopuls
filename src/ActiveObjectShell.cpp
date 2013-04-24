#include "ActiveObjectShell.h"

ActiveObjectShell::ActiveObjectShell(): 
   _activity(this, &ActiveObjectShell::runActivity)
{
}

void ActiveObjectShell::start()
{
   _activity.start();
}

void ActiveObjectShell::stop()
{
   _activity.stop(); // request stop
   _activity.wait(); // wait until activity actually stops
}

bool ActiveObjectShell::isRunning()
{
   return _activity.isRunning();
}

void ActiveObjectShell::runActivity()
{
//   static GoGameFrame lastFrame(GoGameRule::BoardSize19);
   while (!_activity.isStopped())
   {
      run();
      Poco::Thread::sleep(1000);
   }
}

void ActiveObjectShell::run()
{

}
