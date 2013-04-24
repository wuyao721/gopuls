/**
 * @file   GoGamePiece.h
 * @author WuYao <wuyao721@163.com>
 * @date   Fri Oct 28 10:26:26 2011
 * 
 * @brief  Information Of Go Game Piece
 * 
 * 
 */

#ifndef _GO_GAME_PIECE_H_
#define _GO_GAME_PIECE_H_

class GoGamePiece
{
   // position (0, 0) (left, top)
   int _x;          // 0 -- 18
   int _y;          // 0 -- 18

   int _kind;

   bool _lastPiece;

public:

   /** 
    * 
    * 
    */
   GoGamePiece();

   /** 
    * 
    * 
    * @param x 
    * @param y 
    * @param kind 
    */
   GoGamePiece(int x, int y, int kind = 0, bool last = false);

   /** 
    * whether valid
    * 
    * @return 
    */
   bool valid() const;

   /** 
    * 
    * 
    * @param piece 
    * 
    * @return 
    */
   bool operator==(const GoGamePiece& piece) const;

   /** 
    * 
    * 
    * @param piece 
    * 
    * @return 
    */
   bool operator!=(const GoGamePiece& piece) const;

   /** 
    * 
    * 
    * @param piece 
    * 
    */
   void operator=(const GoGamePiece& piece);

   /** 
    * whether last piece
    * 
    * 
    * @return 
    */
   bool lastPiece() const;

   /** 
    * set last piece flag
    * 
    * @param b 
    */
   void setLastPiece(bool b);

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
    * get kind of go game piece(black, white or empty)
    * 
    * 
    * @return 
    */
   int kind() const;

   /** 
    * set kind of go game piece 
    * 
    */
   void setKind(int kind);
};

#endif /* end of GoGamePiece.h */
