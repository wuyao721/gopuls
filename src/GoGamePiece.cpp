#include "GoGamePiece.h"

#include "GoGameRule.h"

GoGamePiece::GoGamePiece():
   _x(-1),
   _y(-1),
   _kind(GoGameRule::PieceKindEmpty),
   _lastPiece(false)
{

}

GoGamePiece::GoGamePiece(int x, int y, int kind, bool last):
   _x(x),
   _y(y),
   _kind(kind),
   _lastPiece(last)
{

}

bool GoGamePiece::valid() const
{
   return
      ((_x >= 0)                       && 
       (_y >= 0)                       && 
       (_x < GoGameRule::BoardSizeMax) && 
       (_y < GoGameRule::BoardSizeMax) );
       
}

bool GoGamePiece::operator==(const GoGamePiece& piece) const 
{
   return (_x == piece.x()) && (_y == piece.y()) && (_kind == piece.kind()) && (_lastPiece == piece.lastPiece());
}

bool GoGamePiece::operator!=(const GoGamePiece& piece) const 
{
   return ! (*this == piece);
}

void GoGamePiece::operator=(const GoGamePiece& piece)
{
   _x = piece.x();
   _y = piece.y();
   _kind = piece.kind();
   _lastPiece = piece.lastPiece();
}

bool GoGamePiece::lastPiece() const
{
   return _lastPiece;
}

void GoGamePiece::setLastPiece(bool b)
{
   _lastPiece = b;
}

int GoGamePiece::x() const
{
   return _x;
}

int GoGamePiece::y() const
{
   return _y;
}

void GoGamePiece::setX(int x)
{
   _x = x;
}

void GoGamePiece::setY(int y)
{
   _y = y;
}

int GoGamePiece::kind() const
{
   return _kind;
}

void GoGamePiece::setKind(int kind)
{
   _kind = kind;
}
