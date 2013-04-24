/**
 * @file   WuZhengGoBoard.h
 * @author WuYao <wuyao721@163.com>
 * @date   Thu Oct 27 16:09:28 2011
 * 
 * @brief  What is wuzheng? Please visit www.wuzheng.org.
 *         The board color is Elegant(淡雅黄纹).
 * 
 * 
 */
#ifndef _WU_ZHENG_GO_BOARD_H_
#define _WU_ZHENG_GO_BOARD_H_

#include "GoBoard.h"

class WuZhengGoBoard: public GoBoard
{
public:
   WuZhengGoBoard(int boardSize);

protected:

   /** 
    * whether point(x, y) black chessman
    * 
    * @param x x-coordinate of bitmap
    * @param y y-coordinate of bitmap
    * 
    * @return 
    */
   virtual bool isBlack(int x, int y);

   /** 
    * whether point(x, y) white chessman
    * 
    * @param x x-coordinate of bitmap
    * @param y y-coordinate of bitmap
    * 
    * @return 
    */
   virtual bool isWhite(int x, int y);
   
   /** 
    * whether point(x, y) last chessman
    * 
    * @param x x-coordinate of bitmap
    * @param y y-coordinate of bitmap
    * 
    * @return 
    */
   virtual bool isLastPiece(int x, int y);
};

#endif /* end of WuZhengGoBoard.h */
