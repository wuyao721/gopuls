/**
 * @file   GoGameInfo.h
 * @author WuYao <wuyao721@163.com>
 * @date   Wed Apr 27 10:16:32 2011
 * 
 * @brief  Information Of Go Board
 * 
 * 
 */

#ifndef _GO_GAME_INFO_H_
#define _GO_GAME_INFO_H_

#include "config.h"

#include <list>

#include <Poco/Types.h>
#include <Poco/Format.h>

#include "GoBoardCross.h"

class GoGameInfo
{
public:

   /** 
    * 
    * 
    * @param boardsize 
    */
   GoGameInfo(int boardsize);

//   void setEmpty(int x , int y);
//
//   void setBlack(int x , int y);
//
//   void setWhite(int x , int y);

   /** 
    * Get Board Size
    * 
    * 
    * @return Board Size
    */
   int boardsize();

   /** 
    * 
    * 
    * @param x 
    * @param y 
    * @param kind
    */
   void move(int x, int y, int kind);

   /** 
    * 
    * 
    * @param ptr 
    */
   void move(GoBoardCross& ptr);

   /** 
    * 
    * 
    */
   void undo();

   /** 
    * Get First Move Of Go Game 
    * 
    * 
    * @return 
    */
   bool getFirst(GoBoardCross& piece);

   /** 
    * Get Next Move Of Go Game 
    * 
    * 
    * @return 
    */
   bool getNext(GoBoardCross& piece);
   
   /** 
    * write go game to sgf file
    * 
    * @param filePath sgf filepath
    */
   void writeSgf(const std::string filePath);

   /** 
    * get last go game piece
    * 
    * 
    * @return 
    */
   GoBoardCross lastPiece();

private:
   int _boardsize;
   std::list<GoBoardCross> _moves;
   std::list<GoBoardCross>::iterator _it;
   GoBoardCross _lastPiece;
};

#endif /* end of GoBoardInfo.h */
