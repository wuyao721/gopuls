#include "WuZhengGoBoard.h"

WuZhengGoBoard::WuZhengGoBoard(int boardsize)
{
   _boardsize = boardsize;
   _gridLen = 19;

   _edgeLen = (_boardsize - 1) * _gridLen + 1;
   
   // black
   _blackColorRedDown = 0;
   _blackColorRedUp = 82;
   _blackColorGreenDown = 0;
   _blackColorGreenUp = 81;
   _blackColorBlueDown = 0;
   _blackColorBlueUp = 81;

   // white
   _whiteColorRedDown = 200;
   _whiteColorRedUp = 255;
   _whiteColorGreenDown = 200;
   _whiteColorGreenUp = 255;
   _whiteColorBlueDown = 200;
   _whiteColorBlueUp = 255;

   // edge
   _edgeColorRedDown = 111;
   _edgeColorRedUp = 173;
   _edgeColorGreenDown = 94;
   _edgeColorGreenUp = 147;
   _edgeColorBlueDown = 53;
   _edgeColorBlueUp = 83;

   // board
   _boardColorRedDown = 221;
   _boardColorRedUp = 221;
   _boardColorGreenDown = 187;
   _boardColorGreenUp = 187;
   _boardColorBlueDown = 106;
   _boardColorBlueUp = 106;

   // last one
   _lastOneColorRedDown = 236;
   _lastOneColorRedUp = 236;
   _lastOneColorGreenDown = 30;
   _lastOneColorGreenUp = 30;
   _lastOneColorBlueDown = 36;
   _lastOneColorBlueUp = 36;
}

bool WuZhengGoBoard::isBlack(int x, int y)
{
   /*
    * WuZheng's black chessman like this
    *
    * bbbbbbbbb
    * brrrrrrrb
    * brrrrrrrb
    * brrrrrrrb
    * brrrrrrrb
    * brrrrrrrb
    * brrrrrrrb   
    * brrrrrrrb   
    * bbbbbbbbb   
    *
    */

   if( GoBoard::isBlack(x, y) ){
      return true;
   }

   if( GoBoard::isLastOne(x, y)     && 
       GoBoard::isLastOne(x+1, y+1) && 
       GoBoard::isLastOne(x-1, y-1) && 
       GoBoard::isLastOne(x+1, y-1) && 
       GoBoard::isLastOne(x-1, y+1) && 
       GoBoard::isBlack(x+4, y)     && 
       GoBoard::isBlack(x, y+4)     && 
       GoBoard::isBlack(x-4, y)     && 
       GoBoard::isBlack(x, y-4)     ){
      
      // set last piece's coordinate
      _lastPieceX = x;
      _lastPieceY = y;

      return true;
   }
   return false;
}

bool WuZhengGoBoard::isWhite(int x, int y)
{
   /*
    * WuZheng's white chessman like this
    *
    * wwwwwwwww
    * wrrrrrrrw
    * wrrrrrrrw
    * wrrrrrrrw
    * wrrrrrrrw
    * wrrrrrrrw
    * wrrrrrrrw   
    * wrrrrrrrw   
    * wwwwwwwww   
    *
    */

   if( GoBoard::isWhite(x, y) ){
      return true;
   }

   if( GoBoard::isLastOne(x, y)     && 
       GoBoard::isLastOne(x+1, y+1) && 
       GoBoard::isLastOne(x-1, y-1) && 
       GoBoard::isLastOne(x+1, y-1) && 
       GoBoard::isLastOne(x-1, y+1) && 
       GoBoard::isWhite(x+4, y)     && 
       GoBoard::isWhite(x, y+4)     && 
       GoBoard::isWhite(x-4, y)     && 
       GoBoard::isWhite(x, y-4)     ){

      // set last piece's coordinate
      _lastPieceX = x;
      _lastPieceY = y;

      return true;
   }
   return false;
}

bool GoBoard::isLastPiece(int x, int y)
{
   if( GoBoard::isLastOne(x, y)     && 
       GoBoard::isLastOne(x+1, y+1) && 
       GoBoard::isLastOne(x-1, y-1) && 
       GoBoard::isLastOne(x+1, y-1) && 
       GoBoard::isLastOne(x-1, y+1) && 
                                    ){

      // set last piece's coordinate
      _lastPieceX = x;
      _lastPieceY = y;

      return true;
   }
   return false;
}
