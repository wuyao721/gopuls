#include "GoGameCross.h"
#include "GoGameRule.h"

GoGameCross::GoGameCross():
   _x(-1),
   _y(-1),
   _kind(GoGameRule::PieceKindEmpty)
{

}

GoGameCross::GoGameCross(int x, int y, int kind):
   _x(x),
   _y(y),
   _kind(kind)
{
   
}

bool GoGameCross::valid()
{
   return
      ((_x >= 0)                                 && 
       (_y >= 0)                                 && 
       (_x < GoGameRule::BoardSizeMax)           && 
       (_y < GoGameRule::BoardSizeMax)           && 
       ( (_kind == GoGameRule::PieceKindBlack) ) ||
       ( (_kind == GoGameRule::PieceKindWhite) ) ||
       ( (_kind == GoGameRule::PieceKindEmpty) ) );
}

int GoGameCross::x()
{
   return _x;
}

int GoGameCross::y()
{
   return _y;
}

void GoGameCross::setX(int x)
{
   _x = x;
}

void GoGameCross::setY(int y)
{
   _y = y;
}

int GoGameCross::kind()
{
   return _kind;
}

void GoGameCross::setKind(int kind)
{
   _kind = kind;
}

