/**
 * @file   GoGameCross.h
 * @author WuYao <wuyao721@163.com>
 * @date   Fri Oct 28 10:26:26 2011
 * 
 * @brief  Information Of Go Game Cross
 * 
 * 
 */

#ifndef _GO_GAME_CROSS_H_
#define _GO_GAME_CROSS_H_

class GoGameCross
{
   // position (0, 0) (left, top)
   int _x;          // 0 -- (GoGameRule::BoardSizeMax - 1)
   int _y;          // 0 -- (GoGameRule::BoardSizeMax - 1)

   int _kind;

public:

   /** 
    * 
    * 
    */
   GoGameCross();

   /** 
    * 
    * 
    * @param x 
    * @param y 
    * @param kind 
    */
   GoGameCross(int x, int y, int kind = 0);

   /** 
    * is valid
    * 
    */
   bool valid();

   /** 
    * get x-coordinate of go board cross
    * 
    * 
    * @return 
    */
   int x();
   
   /** 
    * get y-coordinate of go board cross
    * 
    * 
    * @return 
    */
   int y();

   /** 
    * set x-coordinate of go board cross
    * 
    * @param x 
    */
   void setX(int x);
   
   /** 
    * set y-coordinate of go board cross
    * 
    * @param y 
    */
   void setY(int y);

   /** 
    * get kind of go board cross(black, white or empty)
    * 
    * 
    * @return 
    */
   int kind();

   /** 
    * set kind of go board cross 
    * 
    */
   void setKind(int kind);
};

#endif /* end of GoGameCross.h */
