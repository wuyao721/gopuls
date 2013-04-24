/**
 * @file   GoBoardPoint.h
 * @author WuYao <wuyao721@163.com>
 * @date   Sun Feb 19 21:55:57 2012
 * 
 * @brief  go board point
 * 
 * 
 */

#ifndef _GO_BOARD_POINT_H_
#define _GO_BOARD_POINT_H_

class GoBoardPoint
{
   // position (0, 0) (left, top)
   int _x;          // 0 -- 18
   int _y;          // 0 -- 18

   // window bitmap reference
   const WindowBitmap& _bitmap;

   // rgb
   BYTE _r;
   BYTE _g;
   BYTE _b;

public:

   /** 
    * 
    * 
    */
   GoBoardPoint(WindowBitmap& bitmap, int x, int y);

   /** 
    * 
    * 
    * @param x 
    * @param y 
    * @param kind 
    */
   GoBoardPoint(int x, int y, int kind = 0, bool last = false);

//   /** 
//    * whether valid
//    * 
//    * @return 
//    */
//   bool valid() const;

   /** 
    * get x-coordinate of go game piece
    * 
    * 
    * @return 
    */
   int x() const;
   
   /** 
    * get y-coordinate of go game piece
    * 
    * 
    * @return 
    */
   int y() const;

   /** 
    * set x-coordinate of go game piece
    * 
    * @param x 
    */
   void setX(int x);
   
   /** 
    * set y-coordinate of go game piece
    * 
    * @param y 
    */
   void setY(int y);

   /** 
    * is rgb equal
    * 
    * @param point 
    * 
    * @return 
    */
   //bool rgbEqual(const GoBoardPoint& point);

   /** 
    * is rgb equal
    * 
    * @param r 
    * @param g 
    * @param b 
    * 
    * @return 
    */
   bool rgbEqual(BYTE r, BYTE g, BYTE b);

   /** 
    * is rgb equal
    * 
    * @param bitmap 
    * @param x1 
    * @param y1 
    * @param x2 
    * @param y2 
    * 
    * @return 
    */
   static bool rgbEqual(const WindowBitmap& bitmap, int x1, int y1, int x2, int y2);

   /** 
    * is rgb equal
    * 
    * @param bitmap 
    * @param x1 
    * @param y1
    * @param r 
    * @param g 
    * @param b 
    * 
    * @return 
    */
   static bool rgbEqual(const WindowBitmap& bitmap, int x1, int y, BYTE r, BYTE g, BYTE b);

   /** 
    * is rgb less than
    * 
    * @param bitmap 
    * @param x1 
    * @param y1 
    * @param r 
    * @param g 
    * @param b 
    * 
    * @return 
    */
   static bool rgbLess(const WindowBitmap& bitmap, int x1, int y1, BYTE r, BYTE g, BYTE b);

   /** 
    * is rgb larger than
    * 
    * @param bitmap 
    * @param x1 
    * @param y1 
    * @param r 
    * @param g 
    * @param b 
    * 
    * @return 
    */
   static bool rgbLarger(const WindowBitmap& bitmap, int x1, int y1, BYTE r, BYTE g, BYTE b);
};

#endif /* end of GoBoardPoint.h */
