#include "QQGoBoard.h"
#include "GoGameInfo.h"

int main()
{
   QQGoBoard goBoard(GoGameInfo::BoardSize19);
   goBoard.scanGoBoardInfo();
   if( ! goBoard.isGoBoard() ){
      return -1;
   }

   goBoard.print();

   GoGameInfo GoGameInfo = goBoard.getGoGameInfo();

   MetaMachine* metaMachine;
   metaMachine = MetaMachine::newProcess(NULL);
   if( metaMachine == NULL ){
	   std::cerr << "error." << std::endl;
      return -1;
   }

   setBoardSize(GoGameInfo::BoardSize19);
   
   metaMachine->init(goBoardInfo);
   GoBoardCross goBoardCross = goBoardInfo.lastPiece();   
   
   if( goBoardCross.isBlack() ){
      goBoardCross = metaMachine->genMove(GoBoardCross::ColorBlack);
   }else if( goBoardCross.isWhite() ){
      goBoardCross = metaMachine->genMove(GoBoardCross::ColorWhite);
   }
   
   goBoardInfo.move(goBoardCross);
   goBoardInfo.writeSgf("aaa.sgf");
   return 0;
}
