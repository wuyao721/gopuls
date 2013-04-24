#include <windows.h>

int main(int argc, char** argv)
{
	while(1){
   Sleep(2000);

   POINT lpPoint;
   GetCursorPos(&lpPoint);

   SetCursorPos(lpPoint.x, lpPoint.y);
   mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,0);
   mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);   
	}
   return 0;
}
