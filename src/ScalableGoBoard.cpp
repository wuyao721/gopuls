#include "ScalableGoBoard.h"

ScalableGoBoard::ScalableGoBoard(int boardsize):
   GoBoard(boardsize),
   _gridLenMax(50),
   _gridLenMin(10)
{

}

bool ScalableGoBoard::guessGridLen(int x, int y)
{
   int offset;

   // middle to right
   for( offset = _gridLenMin; offset <= _gridLenMax; offset++ ){
      if( isTopEdgeGridTopCorner(x+offset, y) ){
         _gridLen = offset;
         return true;
      }
   }

   // middle to left
   for( offset = _gridLenMin; offset <= _gridLenMax; offset++ ){
      if( isTopEdgeGridTopCorner(x-offset, y) ){
         _gridLen = offset;
         return true;
      }
   }

   return false;
}

void ScalableGoBoard::scanGoBoard()
{
   int width = _bitmap->width();
   int height = _bitmap->height();

   int w; int h;
   
   // scan bitmap from left to right, top to bottom
   for( h = 0; h < height; h++){ // maybe height -_edgeLen
      for( w = 0; w < width; w++){
         if( isTopEdgeGridTopCorner(w, h) &&
             guessGridLen(w, h)           &&
             findLeftTop(w, h)            &&
             scanAllGrid()                ){
            _isGoBoard = true;
			return;
         }
      }
   }
}
