#include <iostream>
#include <MetaMachine.h>

int main(int argc, char** argv)
{
   MetaMachine* metaMachine;
   metaMachine = MetaMachine::newProcess(NULL);
   if( metaMachine == NULL ){
	   std::cerr << "error." << std::endl;
      return -1;
   }
   int i;
   for( i = 0; i < 20; i++ ){
      Poco::Int32 color;
      if( i % 2 ){
         color = GoBoardPoint::ColorWhite;
      }else{
         color = GoBoardPoint::ColorBlack;
      }
      metaMachine->genMove(color);
	  //std::cout << ptr->getStrColor() << ": " << ptr->getStrPoint() << std::endl;
   }
   metaMachine->_goBoardInfo.writeSgf("aaa.sgf");
   return 0;
}
