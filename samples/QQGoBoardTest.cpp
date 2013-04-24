#include "QQGoBoard.h"

int main()
{
   QQGoBoard goBoard(19);
   goBoard.scanGoBoardInfo();
   if( goBoard.isGoBoard() ){
      goBoard.print();
   }
   return 0;
}
