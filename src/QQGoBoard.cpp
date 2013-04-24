#include "QQGoBoard.h"

QQGoBoard::QQGoBoard():
   FixedGoBoard(35)
{
   // qq go game use directX to draw go board
   if( NULL == (_bitmap = WindowBitmap::getWindowBitmap("Weiqi.exe", true)) || 
       1024 != _bitmap->width()                                             || 
       738 != _bitmap->height()                                             ){
      return;
   }
   
   // black piece color
   _blackColorRedDown = 0;
   _blackColorRedUp = 32;
   _blackColorGreenDown = 0;
   _blackColorGreenUp = 32;
   _blackColorBlueDown = 0;
   _blackColorBlueUp = 32;

   // white piece color
   _whiteColorRedDown = 200;
   _whiteColorRedUp = 255;
   _whiteColorGreenDown = 200;
   _whiteColorGreenUp = 255;
   _whiteColorBlueDown = 200;
   _whiteColorBlueUp = 255;

   // edge color
   _edgeColorRedDown = 88;
   _edgeColorRedUp = 120;
   _edgeColorGreenDown = 68;
   _edgeColorGreenUp = 100;
   _edgeColorBlueDown = 32;
   _edgeColorBlueUp = 70;

   // go board color
   _boardColorRedDown = 220;
   _boardColorRedUp = 235;
   _boardColorGreenDown = 160;
   _boardColorGreenUp = 204;
   _boardColorBlueDown = 80;
   _boardColorBlueUp = 136;

   // last one color
   _lastOneColorRedDown = 248;
   _lastOneColorRedUp = 248;
   _lastOneColorGreenDown = 0;
   _lastOneColorGreenUp = 0;
   _lastOneColorBlueDown = 0;
   _lastOneColorBlueUp = 0;

   _isAbsoluteCoordinate = false;

   // start button position, relative coordinates
   // (230, 360) 
   //                (341, 391)
   _startButtonRect.left = 230;
   _startButtonRect.right = 341;
   _startButtonRect.top = 360;
   _startButtonRect.bottom = 391;

   // pass button position, relative coordinates
   // (744, 236)
   //                (803, 263)
   _passButtonRect.left = 744;
   _passButtonRect.right = 803;
   _passButtonRect.top = 236;
   _passButtonRect.bottom = 263;

   // resign button position, relative coordinates
   // (942, 236)
   //                (1001, 263)
   _resignButtonRect.left = 942;
   _resignButtonRect.right = 1001;
   _resignButtonRect.top = 236;
   _resignButtonRect.bottom = 263;

   scanGoBoard();
}

QQGoBoard::~QQGoBoard()
{
   if( _bitmap ){
      delete _bitmap;
   }
}

bool QQGoBoard::getStatus()
{
   _started = true;
   _prepared = true;
   _nextMoveKind = NEXT_MOVE_KIND_UNKNOW;
   _whichTurnToPlay = NEXT_TURN_TO_PLAY_UNKNOW;

   int emptyBox1MiddleX, emptyBox1MiddleY, emptyBox2MiddleX, emptyBox2MiddleY;

   // empty box 1 position
   // (744, 129)
   //                (1004, 182)
   int emptyBox1Left = 744;
   int emptyBox1Top = 129;
   int emptyBox1Right = 1004;
   int emptyBox1Bottom = 182;

   // empty box 2 position
   // (744, 193)
   //                (1004, 246) 
   int emptyBox2Left = 744;
   int emptyBox2Top = 193;
   int emptyBox2Right = 1004;
   int emptyBox2Bottom = 246;

   // box's middle point
   emptyBox1MiddleX = emptyBox1Right - (emptyBox1Right - emptyBox1Left)/2;
   emptyBox1MiddleY = emptyBox1Bottom - (emptyBox1Bottom - emptyBox1Top)/2;
   emptyBox2MiddleX = emptyBox2Right - (emptyBox2Right - emptyBox2Left)/2;
   emptyBox2MiddleY = emptyBox2Bottom - (emptyBox2Bottom - emptyBox2Top)/2;

   // Weiqi.exe just open a .wgs file localhost, not play with other player
   if( _bitmap->rgbEqual(emptyBox1MiddleX, emptyBox1MiddleY, 216, 184, 112) &&
       _bitmap->rgbEqual(emptyBox2MiddleX, emptyBox2MiddleY, 216, 184, 112) ){
      _started = true;
      _prepared = true;
      _nextMoveKind = NEXT_MOVE_KIND_UNKNOW;
	  _whichTurnToPlay = NEXT_TURN_TO_PLAY_UNKNOW;
	  return true;
   }

   int opponentBoxMiddleX, opponentBoxMiddleY, userBoxMiddleX, userBoxMiddleY;

   // opponent's box position
   int opponentBoxLeft = 744;
   int opponentBoxTop = 63;
   int opponentBoxRight = 1004;
   int opponentBoxBottom = 133;

   // our user's box position
   int userBoxLeft = 744;
   int userBoxTop = 142;
   int userBoxRight = 1004;
   int userBoxBottom = 212;

   // box's middle point
   opponentBoxMiddleX = opponentBoxRight - (opponentBoxRight - opponentBoxLeft)/2;
   opponentBoxMiddleY = opponentBoxBottom - (opponentBoxBottom - opponentBoxTop)/2;
   userBoxMiddleX = userBoxRight - (userBoxRight - userBoxLeft)/2;
   userBoxMiddleY = userBoxBottom - (userBoxBottom - userBoxTop)/2;

   // the opponent's turn to play
   if( _bitmap->rgbEqual(opponentBoxMiddleX, opponentBoxMiddleY, 216, 188, 112) ){
      _started = true;
      _prepared = true;
      _whichTurnToPlay = NEXT_TURN_TO_PLAY_OPPONENT;

      // the opponent's kind is black
      //(x, y)     (r, g, b)
      //(983, 82)  (100, 100, 100)
      if( _bitmap->rgbLess(983, 82, 100, 100, 100) ){
         _nextMoveKind = NEXT_MOVE_KIND_BLACK;
      }
      
      // the opponent's kind is white
      //(x, y)     (r, g, b)
      //(983, 82)  (100, 100, 100)
      else if( _bitmap->rgbLarger(983, 82, 200, 200, 200) ){
         _nextMoveKind = NEXT_MOVE_KIND_WHITE;
      }

      // exception
      else{
         _nextMoveKind = NEXT_MOVE_KIND_UNKNOW;
         return false;
      }

	  return true;
   }

   // our user's turn to play
   else if( _bitmap->rgbEqual(userBoxMiddleX, userBoxMiddleY, 216, 188, 112) ){
      _started = true;
      _prepared = true;
      _whichTurnToPlay = NEXT_TURN_TO_PLAY_USER;

      // our user's kind is black
      //(x, y)     (r, g, b)
      //(983, 161)  (100, 100, 100)
      if( _bitmap->rgbLess(983, 161, 100, 100, 100) ){
         _nextMoveKind = NEXT_MOVE_KIND_BLACK;
      }
      
      // our user's kind is white
      //(x, y)     (r, g, b)
      //(983, 161)  (100, 100, 100)
      else if( _bitmap->rgbLarger(983, 161, 200, 200, 200) ){
         _nextMoveKind = NEXT_MOVE_KIND_WHITE;
      }

      // exception
      else{
         _nextMoveKind = NEXT_MOVE_KIND_UNKNOW;
         return false;
      }

	  return true;
   }
   
   // not started
   else if( _bitmap->rgbEqual(opponentBoxMiddleX, opponentBoxMiddleY, 192, 156, 64) &&
            _bitmap->rgbEqual(userBoxMiddleX, userBoxMiddleY, 192, 156, 64)         ){
      _started = false;
      _nextMoveKind = NEXT_MOVE_KIND_UNKNOW;
      _whichTurnToPlay = NEXT_TURN_TO_PLAY_UNKNOW;

      // (45, 20, 8), 
      // (45, 20, 8), (45, 20, 8)
      // not prepared
//      if( _bitmap->rgbEqual(_startCtrlBoxLeft, _startCtrlBoxTop, 40, 16, 0)     && 
//          _bitmap->rgbEqual(_startCtrlBoxLeft, _startCtrlBoxBottom, 40, 16, 0)  && 
//          _bitmap->rgbEqual(_startCtrlBoxRight, _startCtrlBoxTop, 48, 20, 0)    &&
//          _bitmap->rgbEqual(_startCtrlBoxRight, _startCtrlBoxBottom, 48, 20, 0) ){
      if( _bitmap->rgbNear(_startButtonRect.left,  _startButtonRect.top, 45, 20, 10)     && 
          _bitmap->rgbNear(_startButtonRect.left,  _startButtonRect.bottom, 45, 20, 10)  && 
          _bitmap->rgbNear(_startButtonRect.right, _startButtonRect.top, 45, 20, 10)    &&
          _bitmap->rgbNear(_startButtonRect.right, _startButtonRect.bottom, 45, 20, 10) ){
         _prepared = false;
      }

	  return true;
   }

   // exception
   else{
      return false;
   }
   return false;
}

void QQGoBoard::scanGoBoard()
{
   // get go board's status
   if( false == getStatus() ) {
      return;
   }
   
   // try boardsize 19
   _leftTopX = 54;
   _leftTopY = 64;
   _boardsize = 19;
   _goGameFrame.setBoardsize(_boardsize);
   if( scanAllGrid() ){
      _isGoBoard = true;
      return;
   }

   // try boardsize 13
   _leftTopX = 156;
   _leftTopY = 169;
   _boardsize = 13;
   _goGameFrame.setBoardsize(_boardsize);
   if( scanAllGrid() ){
      _isGoBoard = true;
      return;
   }

   // try boardsize 9
   _leftTopX = 226;
   _leftTopY = 239;
   _boardsize = 9;
   _goGameFrame.setBoardsize(_boardsize);
   if( scanAllGrid() ){
      _isGoBoard = true;
      return;
   }
}

bool QQGoBoard::isPieceBlack(int x, int y, bool& last)
{
   last = isLastPiece(x, y);
   return isPointBlack(x, y);
}

bool QQGoBoard::isPieceWhite(int x, int y, bool& last)
{
   last = isLastPiece(x, y);
   return isPointWhite(x, y);
}

/*
 *
 *        XX      
 *        XX      
 *        XX      
 *        XX      
 *        XX      
 *                
 *   XXXX  0  XXXX      
 *   XXXX     XXXX      
 *                
 *        XX      
 *        XX      
 *        XX      
 *        XX      
 *        XX      
 *
 */
bool QQGoBoard::isLastPiece(int x, int y)
{
   return 
      GoBoard::isLastPiece(x, y+3) &&
      GoBoard::isLastPiece(x, y-3) &&
      GoBoard::isLastPiece(x-3, y) &&
      GoBoard::isLastPiece(x+3, y);
}
