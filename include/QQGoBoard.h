/**
 * @file   QQGoBoard.h
 * @author WuYao <wuyao721@163.com>
 * @date   Sun Apr 17 23:16:40 2011
 * 
 * @brief  
 * 
 * 
 */

#ifndef _QQ_GO_BOARD_H_
#define _QQ_GO_BOARD_H_

#include "FixedGoBoard.h"

class QQGoBoard: public FixedGoBoard
{
public:

   /** 
    * 
    * 
    */
   QQGoBoard();

   /** 
    * 
    * 
    * 
    */
   ~QQGoBoard();

   /** 
    * get the go board's status
    * 
    * 
    * @return 
    */
   virtual bool getStatus();

protected:

   /** 
    * scan go board and fetch go game information
    * 
    */
   virtual void scanGoBoard();

   /** 
    * whether point(x, y)'s piece black
    * 
    * @param x x-coordinate of screen
    * @param y y-coordinate of screen
    * @param last whether last piece
    * 
    * @return 
    */
   virtual bool isPieceBlack(int x, int y, bool& last);

   /** 
    * whether point(x, y)'s piece white
    * 
    * @param x x-coordinate of screen
    * @param y y-coordinate of screen
    * @param last whether last piece
    * 
    * @return 
    */
   virtual bool isPieceWhite(int x, int y, bool& last);

   /** 
    * whether point(x, y) last piece
    * 
    * @param x x-coordinate of screen
    * @param y y-coordinate of screen
    * 
    * @return 
    */
   virtual bool isLastPiece(int x, int y);

private:
};

#endif /* end of QQGoBoard.h */
