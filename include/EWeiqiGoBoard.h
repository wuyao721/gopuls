/**
 * @file   EWeiQiGoBoard.h
 * @author WuYao <wuyao721@163.com>
 * @date   Thu Oct 27 20:41:26 2011
 * 
 * @brief  http://www.eweiqi.com
 * 
 * 
 */

#ifndef _E_WEI_QI_GO_BOARD_H_
#define _E_WEI_QI_GO_BOARD_H_

#include "ScalableGoBoard.h"

class EWeiQiGoBoard: public ScalableGoBoard
{
public:

   /** 
    * 
    * 
    * 
    */
   EWeiQiGoBoard();

   /** 
    * 
    * 
    * 
    */
   ~EWeiQiGoBoard();

   /** 
    * pass one move
    * 
    */
   virtual void pass();

   /** 
    * resign
    * 
    */
   virtual void resign();

   /** 
    * get the go board's status
    * 
    * 
    * @return 
    */
   virtual bool getStatus();

protected:

   /** 
    * get buttons position
    * 
    * 
    * @return 
    */
   bool getButtonPosition();

   /** 
    * scan one grid, which is under mouse 
    * 
    * @param x x-coordinate of screen
    * @param y y-coordinate of screen
    * @param i x-coordinate of go game
    * @param j y-coordinate of go game
    * 
    * @return 
    */
   virtual GoGamePiece scanOneGridUnderMouse(int x, int y, int i, int j);

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

private:
   
   /** 
    * confirm message box
    * 
    * @param askString 
    * 
    * @return 
    */
   bool confirmMessageBox(const std::string& askString);
};

#endif /* end of EWeiqiGoBoard.h */
