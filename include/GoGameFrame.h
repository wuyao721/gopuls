/**
 * @file   GoGameFrame.h
 * @author WuYao <wuyao721@163.com>
 * @date   Wed Jan 11 21:34:05 2012
 * 
 * @brief  One frame of the go game's information
 * 
 * 
 */

#ifndef _GO_GAME_FRAME_H_
#define _GO_GAME_FRAME_H_

#include "GoGameRule.h"
#include "GoGamePiece.h"

class GoGameFrame
{
public:

   /** 
    * boardsize is unknown
    * 
    * @param boardsize 
    */
   GoGameFrame();

   /** 
    * boardsize is known
    * 
    * @param boardsize 
    */
   GoGameFrame(int boardsize);

   /** 
    * get board size
    * 
    * 
    * @return board size
    */
   int boardsize() const;

   /** 
    * set board size
    * 
    * 
    * @return board size
    */
   void setBoardsize(int boardsize);

   /** 
    * get position (x, y) piece's kind
    * 
    * @param x 
    * @param y 
    */
   int getPieceKind(int x, int y) const;

   /** 
    * get position (x, y) piece
    * 
    * @param x 
    * @param y 
    * 
    * @return 
    */
   GoGamePiece getPiece(int x, int y) const;

   /** 
    * 
    * 
    * @param x 
    * @param y 
    * @param kind 
    */
   void setPieceKind(int x, int y, int kind);

   /** 
    * 
    * 
    * @param x 
    * @param y 
    * @param kind 
    */
   void setPiece(const GoGamePiece& piece);

   /** 
    * 
    * 
    * @param frame 
    * 
    * @return 
    */
   bool operator==(const GoGameFrame& frame) const;
   
   /** 
    * 
    * 
    * @param frame 
    * 
    * @return 
    */
   bool operator!=(const GoGameFrame& frame) const;
   
   /** 
    * get last go game piece
    * 
    * 
    * @return 
    */
   const GoGamePiece& lastPiece() const;

   /** 
    * set last go game piece
    * 
    * @param lastPiece
    */
   void setLastPiece(const GoGamePiece& lastPiece);

   /** 
    * set last go game piece
    * 
    * @param x 
    * @param y 
    * @param kind 
    */
   void setLastPiece(int x, int y, int kind);

   /** 
    * whether go game frame empty
    * 
    * 
    * @return 
    */
   bool isEmpty() const;

   /** 
    * print the go game information
    * 
    */
   void print() const;

private:

   // go board size
   int _boardsize;

   // go game pieces
   //int _pieces[GoGameRule::BoardSizeMax][GoGameRule::BoardSizeMax]; //why can this?
   int _pieces[19][19];

   // last piece
   GoGamePiece _lastPiece;
};

#endif /* end of GoGameFrame.h */
