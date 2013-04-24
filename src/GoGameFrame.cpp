#include "GoGameFrame.h"

GoGameFrame::GoGameFrame()
{
   memset(_pieces, 0, sizeof(_pieces));
}

GoGameFrame::GoGameFrame(int boardsize):
   _boardsize(boardsize)
{
   memset(_pieces, 0, sizeof(_pieces));
}

int GoGameFrame::boardsize() const
{
   return _boardsize;
}

void GoGameFrame::setBoardsize(int boardsize)
{
   _boardsize = boardsize;
}

int GoGameFrame::getPieceKind(int x, int y) const
{
   return _pieces[y][x];
}

GoGamePiece GoGameFrame::getPiece(int x, int y) const
{
   if( _lastPiece.x() == x && _lastPiece.y() == y ){
      return _lastPiece;
   }
   return GoGamePiece(x, y, getPieceKind(x, y), false);
}

void GoGameFrame::setPieceKind(int x, int y, int kind)
{
   _pieces[y][x] = kind;
}

void GoGameFrame::setPiece(const GoGamePiece& piece)
{
   if(piece.valid()){
      _pieces[piece.y()][piece.x()] = piece.kind();
      if(piece.lastPiece()){
         setLastPiece(piece.x(), piece.y(), piece.kind());
      }
   }
}

bool GoGameFrame::operator==(const GoGameFrame& frame) const 
{
   if( _boardsize != frame.boardsize() ){
      return false;
   }

   //if( _lastPiece != frame.lastPiece() ){
   //   return false;
   //}

   int i,j;
   for(i=0;i<_boardsize;i++){
      for(j=0;j<_boardsize;j++){
         if( getPieceKind(i,j) != frame.getPieceKind(i,j) ){
            return false;
         }
      }
   }
   return true;
}

bool GoGameFrame::operator!=(const GoGameFrame& frame) const 
{
   return ! (*this == frame);
}

const GoGamePiece& GoGameFrame::lastPiece() const
{
   return _lastPiece;
}

void GoGameFrame::setLastPiece(const GoGamePiece& lastPiece)
{
   _lastPiece = lastPiece;
}

void GoGameFrame::setLastPiece(int x, int y, int kind)
{
   _lastPiece.setX(x);
   _lastPiece.setY(y);
   _lastPiece.setKind(kind);
   _lastPiece.setLastPiece(true);
}

bool GoGameFrame::isEmpty() const
{
   int i, j;
   for( i = 0; i < _boardsize; i++ ){
      for( j = 0; j < _boardsize; j++ ){
         if( !GoGameRule::isKindEmpty(_pieces[i][j]) ){
            return false;
         }
      }
   }

   return true;
}

void GoGameFrame::print() const 
{
   int i, j;
   for( i = 0; i < _boardsize; i++ ){
      for( j = 0; j < _boardsize; j++ ){
         printf(" ");
         
         if( _pieces[i][j] == GoGameRule::PieceKindEmpty ){
            printf(".");
         }

         else if( _pieces[i][j] == GoGameRule::PieceKindBlack ){
            printf("X");
         }

         else if( _pieces[i][j] == GoGameRule::PieceKindWhite ){
            printf("O");
         }

         printf(" ");
      }
      printf("\n");
   }
}
