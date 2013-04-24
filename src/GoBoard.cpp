#include <stdio.h>
#include "GoBoard.h"

GoBoard::GoBoard():
   _isGoBoard(false),
   _bitmap(NULL),
   _leftTopX(-1),
   _leftTopY(-1),
   _started(true),
   _prepared(true),
   _whichTurnToPlay(NEXT_TURN_TO_PLAY_UNKNOW),
   _nextMoveKind(NEXT_MOVE_KIND_UNKNOW),
   _isAbsoluteCoordinate(true)
{
   _startButtonRect.left = 0;
   _startButtonRect.right = 0;
   _startButtonRect.top = 0;
   _startButtonRect.bottom = 0;

   _passButtonRect.left = 0;
   _passButtonRect.right = 0;
   _passButtonRect.top = 0;
   _passButtonRect.bottom = 0;

   _resignButtonRect.left = 0;
   _resignButtonRect.right = 0;
   _resignButtonRect.top = 0;
   _resignButtonRect.bottom = 0;
}

GoBoard::GoBoard(int boardsize):
   _isGoBoard(false),
   _bitmap(NULL),
   _boardsize(boardsize),
   _goGameFrame(boardsize),
   _leftTopX(-1),
   _leftTopY(-1),
   _started(true),
   _prepared(true),
   _whichTurnToPlay(NEXT_TURN_TO_PLAY_UNKNOW),
   _nextMoveKind(NEXT_MOVE_KIND_UNKNOW),
   _isAbsoluteCoordinate(true)
{
   _startButtonRect.left = 0;
   _startButtonRect.right = 0;
   _startButtonRect.top = 0;
   _startButtonRect.bottom = 0;

   _passButtonRect.left = 0;
   _passButtonRect.right = 0;
   _passButtonRect.top = 0;
   _passButtonRect.bottom = 0;

   _resignButtonRect.left = 0;
   _resignButtonRect.right = 0;
   _resignButtonRect.top = 0;
   _resignButtonRect.bottom = 0;
}

GoBoard::~GoBoard()
{
   
}

bool GoBoard::isGoBoard()
{
   if( _isGoBoard        &&
       -1 != _boardsize  &&
       -1 != _leftTopX   &&
       -1 != _leftTopY   ){
      return true;
   }
   return false;
}

bool GoBoard::isPrepared()
{
   return _prepared;
}

bool GoBoard::isStarted()
{
   return _started;
}

int GoBoard::nextMoveKind()
{
   return _nextMoveKind;
}

int GoBoard::whichTurnToPlay()
{
   return _whichTurnToPlay;
}

void GoBoard::playMove(int x, int y)
{
   _bitmap->clickScreenRelateToWindow(_leftTopX + x * _gridLen, _leftTopY + y * _gridLen);
}

void GoBoard::drawRectangle(int x, int y)
{
   int i = _leftTopX + x * _gridLen;
   int j = _leftTopY + y * _gridLen;
   _bitmap->drawRectangle(i-_gridLen/2, j-_gridLen/2, i+_gridLen/2, j+_gridLen/2);
}

void GoBoard::start()
{
   if( _startButtonRect.left == 0   && 
       _startButtonRect.right == 0  && 
       _startButtonRect.top == 0    && 
       _startButtonRect.bottom == 0 ){
      return;
   }
   
   int x = _startButtonRect.right - (_startButtonRect.right-_startButtonRect.left)/2;
   int y = _startButtonRect.bottom - (_startButtonRect.bottom-_startButtonRect.top)/2;
   if( _isAbsoluteCoordinate ) {
      WindowBitmap::clickScreen(x, y);
   }else{
      _bitmap->clickScreenRelateToWindow(x, y);
   }
}

void GoBoard::pass()
{
   if( _passButtonRect.left == 0   && 
       _passButtonRect.right == 0  && 
       _passButtonRect.top == 0    && 
       _passButtonRect.bottom == 0 ){
      return;
   }

   int x = _passButtonRect.right - (_passButtonRect.right-_passButtonRect.left)/2;
   int y = _passButtonRect.bottom - (_passButtonRect.bottom-_passButtonRect.top)/2;
   if( _isAbsoluteCoordinate ) {
      WindowBitmap::clickScreen(x, y);
   }else{
      _bitmap->clickScreenRelateToWindow(x, y);
   }
}

void GoBoard::resign()
{
   if( _resignButtonRect.left == 0   && 
       _resignButtonRect.right == 0  && 
       _resignButtonRect.top == 0    && 
       _resignButtonRect.bottom == 0 ){
      return;
   }

   int x = _resignButtonRect.right - (_resignButtonRect.right-_resignButtonRect.left)/2;
   int y = _resignButtonRect.bottom - (_resignButtonRect.bottom-_resignButtonRect.top)/2;
   if( _isAbsoluteCoordinate ) {
      WindowBitmap::clickScreen(x, y);
   }else{
      _bitmap->clickScreenRelateToWindow(x, y);
   }
}

//void GoBoard::draw_debug()
//{
//   // 获取一个可供画图的DC，我这里就直接用桌面算了
//   HDC hdc = GetWindowDC( GetDesktopWindow() );
//
//   //HDC hdc = CreateDC("DISPLAY", NULL, NULL, NULL);
//   // 创建实线画笔
//   HPEN hpen1 = CreatePen( PS_SOLID, 1, RGB(255,0,0) );
//   // 创建一个实体画刷
//   HBRUSH hbrush1 = CreateSolidBrush( RGB(255,0,0) );
//
//   // 将hpen1和hbrush1选进HDC，并保存HDC原来的画笔和画刷
//   HPEN hpen_old = (HPEN)SelectObject( hdc, hpen1 );
//   HBRUSH hbrush_old = (HBRUSH)SelectObject( hdc, hbrush1 );
//
//   int x, y;
//   for(y=0; y<_goGameFrame.boardsize();y++)
//   {
//      for(x=0;x<_goGameFrame.boardsize();x++){
//         int i,j;
//         int kind = _goGameFrame.getPieceKind(x,y);
//         if( GoGameRule::isKindEmpty(kind) ) continue;
//         i = _leftTopX + x * _gridLen;
//         j = _leftTopY + y * _gridLen;
//         // 画一个矩形
//         Rectangle( hdc, i-_gridLen/2, j-_gridLen/2, i+_gridLen/2, j+_gridLen/2 );
//
//
////         int kind = _goGameFrame.getPieceKind(j,i);
////         if( GoGameRule::isKindEmpty(kind) ) continue;
////
////         std::string str = GoGameRule::strOfCoordinate(_goGameFrame.boardsize(), j, i);
////         _ostr << "play" << " "
////               << GoGameRule::strOfKind(kind) << " " 
////               << str << std::endl;
////         // TODO: Error Handler
////
////         readDumpResponse();
//      }
//   }
//
//   // 恢复原来的画笔和画刷
//   SelectObject( hdc, hpen_old );
//   SelectObject( hdc, hbrush_old );
//}

const GoGameFrame& GoBoard::getGoGameFrame()
{
   return _goGameFrame;
}

void GoBoard::scanGoBoard()
{
   int width = _bitmap->width();
   int height = _bitmap->height();

   int w; int h;
   
   // 1. find one grid's corner
   // 2. find go board's left-top corner
   // 3. scan all grid

   // scan screen from left to right, top to bottom
   for( h = 0; h < height; h++){ // maybe height -_edgeLen
      for( w = 0; w < width; w++){
         if( isTopEdgeGridTopCorner(w, h) &&
             findLeftTop(w, h)            &&
             scanAllGrid()                ){
            _isGoBoard = true;
			return;
         }
      }
   }
}

bool GoBoard::isEdgeLeftTop(int x, int y)
{
   if( x-1<0 || y-1<0 || x+1>=_bitmap->width() || y+1>=_bitmap->height()){
      return false;
   }

   /*
    * left-top concer of edge like this:
    *    bbb
    *    bee
    *    beb
    */
   return 
      isPointEdge(x, y)           && // middle
      isPointEdge(x+1, y)         && // right
      isPointEdge(x, y+1)         && // down
      isPointBoard(x-1, y)        && // left
      isPointBoard(x, y-1)        && // up
      isPointBoard(x-1, y-1)      && // left-up
      isPointBoard(x+1, y+1)      && // right-down
      isPointBoard(x-1, y+1)      && // left-down
      isPointBoard(x+1, y-1);        // right-down
}

bool GoBoard::isTopEdgeGridTopCorner(int x, int y)
{
   if( x-1<0 || y-1<0 || x+1>=_bitmap->width() || y+1>=_bitmap->height()){
      return false;
   }

/*
 * grid top corner of top edge like this:
 *    bbb
 *     e
 *    beb
 */

   bool b = 
      isPointEdge(x, y)      && // middle
      isPointEdge(x, y+1)    && // down
      isPointBoard(x, y-1)   && // up
      isPointBoard(x-1, y-1) && // left-up
      isPointBoard(x+1, y+1) && // right-down
      isPointBoard(x-1, y+1) && // left-down
      isPointBoard(x+1, y-1);   // right-down
   if(b){
      int i = 0;
      i++;
   }
   return b;
}

bool GoBoard::isGridCorner(int x, int y)
{
   if( x-4<0 || y-4<0 || x+4>=_bitmap->width() || y+4>=_bitmap->height()){
      return false;
   }

/*
 * grid top corner of top edge like this:
 *    b b
 *     e
 *    b b
 */
   return 
      isPointEdge(x, y)      && // middle
      isPointBoard(x-4, y-4) && // left-up
      isPointBoard(x+4, y+4) && // right-down
      isPointBoard(x-4, y+4) && // left-down
      isPointBoard(x+4, y-4);   // right-down
}

bool GoBoard::isGridCrossCorner(int x, int y)
{
   if( x-4<0 || y-4<0 || x+4>=_bitmap->width() || y+4>=_bitmap->height()){
      return false;
   }

   /*
    * grid top corner of top edge like this:
    *    beb
    *    eee
    *    beb
    */
   return 
      isPointEdge(x, y)      && // middle
      isPointEdge(x+1, y)    && // right
      isPointEdge(x, y+1)    && // down
      isPointEdge(x-1, y)    && // left
      isPointEdge(x, y-1)    && // up
      isPointBoard(x-4, y-4) && // left-up
      isPointBoard(x+4, y+4) && // right-down
      isPointBoard(x-4, y+4) && // left-down
      isPointBoard(x+4, y-4);   // right-down
}

bool GoBoard::findLeftTop(int x, int y)
{
   int left = x;
   int top = y;
   int size = 1;
   int offset;
   bool dump;

   // scan from middle to left
   for( offset = x - _gridLen; offset > _gridLen/2; offset -= _gridLen ){
      if( isTopEdgeGridTopCorner(offset, y) || isPieceWhite(offset, y, dump) || isPieceBlack(offset, y, dump) ){
         size++;
         left = offset;
      }else{
         break;
      }
   }

   // scan from middle to right
   for( offset = x + _gridLen; offset < _bitmap->width() - _gridLen/2; offset += _gridLen ){
      if( isTopEdgeGridTopCorner(offset, y) || isPieceWhite(offset, y, dump) || isPieceBlack(offset, y, dump) ){
         size++;
      }else{
         break;
      }
   }
   
   if( size == _boardsize ){
      _leftTopX = left;
      _leftTopY = top;
      return true;
   }else{
      return false;
   }
}

bool GoBoard::scanAllGrid()
{
   int x, y;
   int i, j;

   int count = 0;
   for( i = 0; i < _boardsize; i++ ){
      for( j = 0; j < _boardsize; j++ ){
         x = _leftTopX + j * _gridLen;
         y = _leftTopY + i * _gridLen;
         GoGamePiece piece = scanOneGrid(x, y, j, i);

         if( piece.valid() ){
            _goGameFrame.setPiece(piece);
         }else{
            count++;
            if( count > 1 ){
               return false;
            }
            
            GoGamePiece piece2 = scanOneGridUnderMouse(x, y, j, i);
            if( piece2.valid() ){
               _goGameFrame.setPiece(piece);
            }else{
               return false;
            }
         }
      }
   }
   return true;
}

GoGamePiece GoBoard::scanOneGrid(int x, int y, int i, int j)
{
   bool last = false;
   GoGamePiece piece(i, j);

   if( isGridCorner(x, y) ){
      piece.setKind(GoGameRule::PieceKindEmpty);
   }else if( isPieceWhite(x, y, last) ){
      piece.setKind(GoGameRule::PieceKindWhite);
   }else if( isPieceBlack(x, y, last) ){
      piece.setKind(GoGameRule::PieceKindBlack);
   }else{
      piece.setX(-1);
      piece.setY(-1);
   }
   
   piece.setLastPiece(last);
   return piece;
}

GoGamePiece GoBoard::scanOneGridUnderMouse(int x, int y, int i, int j)
{
   GoGamePiece piece(-1, -1);
   return piece;
}

bool GoBoard::isPointEdge(int x, int y)
{
   int r = _bitmap->getR(x,y);
   int g = _bitmap->getG(x,y);
   int b = _bitmap->getB(x,y);

   if( r < _edgeColorRedDown || r > _edgeColorRedUp ){
      return false;
   }

   if( g < _edgeColorGreenDown || g > _edgeColorGreenUp ){
      return false;
   }

   if( b < _edgeColorBlueDown || b > _edgeColorBlueUp ){
      return false;
   }

   return true;
}

bool GoBoard::isPointBlack(int x, int y)
{
   int r = _bitmap->getR(x,y);
   int g = _bitmap->getG(x,y);
   int b = _bitmap->getB(x,y);

   if( r < _blackColorRedDown || r > _blackColorRedUp ){
      return false;
   }

   if( g < _blackColorGreenDown || g > _blackColorGreenUp ){
      return false;
   }

   if( b < _blackColorBlueDown || b > _blackColorBlueUp ){
      return false;
   }

   return true;
}

bool GoBoard::isPointWhite(int x, int y)
{
   int r = _bitmap->getR(x,y);
   int g = _bitmap->getG(x,y);
   int b = _bitmap->getB(x,y);

   if( r < _whiteColorRedDown || r > _whiteColorRedUp ){
      return false;
   }

   if( g < _whiteColorGreenDown || g > _whiteColorGreenUp ){
      return false;
   }

   if( b < _whiteColorBlueDown || b > _whiteColorBlueUp ){
      return false;
   }

   return true;
}

bool GoBoard::isPointBoard(int x, int y)
{
   int r = _bitmap->getR(x,y);
   int g = _bitmap->getG(x,y);
   int b = _bitmap->getB(x,y);

   if( r < _boardColorRedDown || r > _boardColorRedUp ){
      return false;
   }

   if( g < _boardColorGreenDown || g > _boardColorGreenUp ){
      return false;
   }

   if( b < _boardColorBlueDown || b > _boardColorBlueUp ){
      return false;
   }

   return true;
}

bool GoBoard::isLastPiece(int x, int y)
{
   int r = _bitmap->getR(x,y);
   int g = _bitmap->getG(x,y);
   int b = _bitmap->getB(x,y);

   if( r < _lastOneColorRedDown || r > _lastOneColorRedUp ){
      return false;
   }

   if( g < _lastOneColorGreenDown || g > _lastOneColorGreenUp ){
      return false;
   }

   if( b < _lastOneColorBlueDown || b > _lastOneColorBlueUp ){
      return false;
   }

   return true;
}

bool GoBoard::isLastBlackPiece(int x, int y)
{
   int r = _bitmap->getR(x,y);
   int g = _bitmap->getG(x,y);
   int b = _bitmap->getB(x,y);

   if( r < _lastOneBlackColorRedDown || r > _lastOneBlackColorRedUp ){
      return false;
   }

   if( g < _lastOneBlackColorGreenDown || g > _lastOneBlackColorGreenUp ){
      return false;
   }

   if( b < _lastOneBlackColorBlueDown || b > _lastOneBlackColorBlueUp ){
      return false;
   }

   return true;
}

bool GoBoard::isLastWhitePiece(int x, int y)
{
   int r = _bitmap->getR(x,y);
   int g = _bitmap->getG(x,y);
   int b = _bitmap->getB(x,y);

   if( r < _lastOneWhiteColorRedDown || r > _lastOneWhiteColorRedUp ){
      return false;
   }

   if( g < _lastOneWhiteColorGreenDown || g > _lastOneWhiteColorGreenUp ){
      return false;
   }

   if( b < _lastOneWhiteColorBlueDown || b > _lastOneWhiteColorBlueUp ){
      return false;
   }

   return true;
}
