#include "GoGameInfo.h"
#include <Poco/FileStream.h>

GoGameInfo::GoGameInfo(int boardsize):
   _boardsize(boardsize)
{
   
}

int GoGameInfo::boardsize()
{
   return _boardsize;
}

//void setEmpty(int x, int y)
//{
//   _pieces[x][y] = GoBoardCross::PieceEmpty;
//}

void GoGameInfo::move(GoBoardCross& goBoardPoint)
{
   _lastPiece = goBoardPoint;
   _moves.push_back(_lastPiece);
}

void GoGameInfo::move(int x, int y, int kind)
{
   GoBoardCross goBoardPoint = GoBoardCross(x, y, kind);
   _lastPiece = goBoardPoint;
   _moves.push_back(_lastPiece);
}

void GoGameInfo::undo()
{
   if( _moves.begin() != _moves.end() ){
      _moves.pop_back();
   }
}

//void GoGameInfo::writeSgf(const std::string filePath)
//{
//   Poco::FileOutputStream fos(filePath);
//
//   fos << "(;SZ[" << _boardsize << "]PW[W]PB[B]";
//
//   std::list<GoBoardCross>::iterator it;
//   for( it = _moves.begin(); it != _moves.end(); it++ ){
//      if( it->isBlack() ){
//         fos << ";B[";
//      }else if( it->isWhite()){
//         fos << ";W[";
//      }
//      char x = 'a' + (it->x());
//      char y = 'a' + (it->y());
//      fos << x << y << "]";
//   }
//
//   fos << ")";
//   
//   fos.close();
//}
//
bool GoGameInfo::getFirst(GoBoardCross& piece)
{
   _it = _moves.begin();
   if( _it == _moves.end() ){
      return false;
   }
   piece = *_it++;
   return true;
}

bool GoGameInfo::getNext(GoBoardCross& piece)
{
   if( _it == _moves.end() ){
      return false;
   }
   piece = *_it++;
   return true;
}

GoBoardCross GoGameInfo::lastPiece()
{
   return _lastPiece;
}
