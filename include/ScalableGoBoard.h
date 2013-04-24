/**
 * @file   ScalableGoBoard.h
 * @author WuYao <wuyao721@163.com>
 * @date   Tue Feb 07 22:43:31 2012
 * 
 * @brief  scalable go board
 * 
 * 
 */

#ifndef _SCALABLE_GO_BOARD_H_
#define _SCALABLE_GO_BOARD_H_

#include "GoBoard.h"

class ScalableGoBoard: public GoBoard
{
public:
   ScalableGoBoard(int boardsize);

protected:

   // grid edge Max Len
   int _gridLenMax;

   // grid edge Max Len
   int _gridLenMin;

protected:

   /** 
    * scan go board and fetch go game information
    * 
    */
   virtual void scanGoBoard();

   /** 
    * guess a grid's board lenght, 
    * scalable go board should get the gridLen first
    * 
    * @param x x-coordinate of one grid corner
    * @param y y-coordinate of one grid corner
    * 
    * @return 
    */
   bool guessGridLen(int x, int y);
};

#endif /* end of ScalableGoBoard.h */
