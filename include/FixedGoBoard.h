/**
 * @file   ScalableGoBoard.h
 * @author WuYao <wuyao721@163.com>
 * @date   Tue Feb 07 22:43:31 2012
 * 
 * @brief  fixed go board
 * 
 * 
 */

#ifndef _FIXED_GO_BOARD_H_
#define _FIXED_GO_BOARD_H_

#include "GoBoard.h"

class FixedGoBoard: public GoBoard
{
public:

   /** 
    * 
    * 
    * @param gridLen grid border length
    * 
    */
   FixedGoBoard(int gridLen);

protected:

};

#endif /* end of FixedGoBoard.h */
