#include "GoBoardPoint.h"

#include "GoGameRule.h"

GoBoardPoint::GoBoardPoint(WindowBitmap& bitmap, int x, int y):
   _bitmap(bitmap),
   _x(x),
   _y(y)
{
   _r = _bitmap.getR(x, y);
   _g = _bitmap.getG(x, y);
   _b = _bitmap.getB(x, y);
}

//bool GoBoardPoint::valid() const
//{
//   return
//      ((_x >= 0)                       && 
//       (_y >= 0)                       && 
//       (_x < GoGameRule::BoardSizeMax) && 
//       (_y < GoGameRule::BoardSizeMax) );
//       
//}
//

int GoBoardPoint::x() const
{
   return _x;
}

int GoBoardPoint::y() const
{
   return _y;
}

void GoBoardPoint::setX(int x)
{
   _x = x;
}

void GoBoardPoint::setY(int y)
{
   _y = y;
}

//bool GoBoardPoint::rgbEqual(const GoBoardPoint& point)
//{
//   return (_r == point._r) && (_g == point._g) && (_b == point._b);
//}

bool GoBoardPoint::rgbEqual(BYTE r, BYTE g, BYTE b)
{
   return (_r == r) && (_g == g) && (_b == b);
}

bool GoBoardPoint::rgbEqual(const WindowBitmap& bitmap, int x1, int y1, int x2, int y2)
{
   int r1 = bitmap->getR(x1, y1);
   int g1 = bitmap->getG(x1, y1);
   int b1 = bitmap->getB(x1, y1);

   int r2 = bitmap->getR(x2, y2);
   int g2 = bitmap->getG(x2, y2);
   int b2 = bitmap->getB(x2, y2);

   return (r1 == r2) && (g1 == g2) && (b1 == b2);
}

bool GoBoardPoint::rgbEqual(const WindowBitmap& bitmap, int x1, int y1, BYTE r, BYTE g, BYTE b)
{
   int r1 = bitmap->getR(x1, y1);
   int g1 = bitmap->getG(x1, y1);
   int b1 = bitmap->getB(x1, y1);

   return (r1 == r) && (g1 == g) && (b1 == b);
}


static bool GoBoardPoint::rgbLess(const WindowBitmap& bitmap, int x1, int y1, BYTE r, BYTE g, BYTE b)
{
   int r1 = bitmap->getR(x1, y1);
   int g1 = bitmap->getG(x1, y1);
   int b1 = bitmap->getB(x1, y1);

   return (r1 < r) && (g1 < g) && (b1 < b);
}

static bool GoBoardPoint::rgbLess(const WindowBitmap& bitmap, int x1, int y1, BYTE r, BYTE g, BYTE b)
{
   int r1 = bitmap->getR(x1, y1);
   int g1 = bitmap->getG(x1, y1);
   int b1 = bitmap->getB(x1, y1);

   return (r1 < r) && (g1 < g) && (b1 < b);
}

static bool GoBoardPoint::rgbLarger(const WindowBitmap& bitmap, int x1, int y1, BYTE r, BYTE g, BYTE b)
{
   int r1 = bitmap->getR(x1, y1);
   int g1 = bitmap->getG(x1, y1);
   int b1 = bitmap->getB(x1, y1);

   return (r1 > r) && (g1 > g) && (b1 > b);
}
