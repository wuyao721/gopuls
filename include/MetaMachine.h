/**
 * @file   MetaMachine.h
 * @author WuYao <wuyao721@163.com>
 * @date   Wed Apr 20 18:18:50 2011
 * 
 * @brief  This class sits between goplus and a GTP engine(eg.gnugo),
 *         thanks to GNUGO's metachine.c.
 *
 *                  internal          pipe a
 *           goplus ----> MetaMachine -----> GTP engine
 *                  <----             <-----
 *                  internal          pipe b
 */

#ifndef _GO_PLUS_METAMACHINE_H_
#define _GO_PLUS_METAMACHINE_H_

#include <list>

#include <Poco/PipeStream.h>
#include <Poco/Pipe.h>

#include "GoGamePiece.h"
#include "GoGameFrame.h"

struct AIMachine
{
   std::string name;
   std::string command;
   std::string args;
};

class MetaMachine
{
public:
   /** 
    * 
    * 
    */
   ~MetaMachine();

   /** 
    * 
    * 
    * @param frame 'one frame of go game'
    */
   void init(const GoGameFrame& frame);

   /** 
    * create a new process(gnugo) and control it through gtp
    * 
    * @param sgfPath filepath of the sgf file
    * 
    * @return 0 Success, -1 False.
    */
   static MetaMachine* newProcess(char* sgfPath);

   /** 
    * update 
    * 
    * @param boardFrame 
    */
   void update(const GoGameFrame& boardFrame);

   /** 
    * get GoGameFrame
    * 
    * 
    * @return 
    */
   GoGameFrame MetaMachine::getGoGameFrame();

   /** 
    * 
    * 
    * 
    * @return 
    */
   static MetaMachine& MetaMachine::getDefault();

   /** 
    * Try to terminate the Go Engine Process, and close all handle.
    * 
    */
   void clearBoard();

   /** 
    * set boardsize
    * 
    * @param boardsize 
    */
   void setBoardSize(int boardsize);

   /** 
    * try to set a new boardsize.
    * if boardsize change, set it. else, do nothing.
    * 
    * @param boardsize 
    */
   void trySetBoardSize(int boardsize);

   /** 
    * 
    * 
    */
   void undo();

   /** 
    * 
    * 
    * @param piece 
    *
    * @return 
    */
   bool play(const GoGamePiece& piece);

   /** 
    * generate one move, refer to boardFrame
    * 
    * @param kind 
    * @param piece 
    * @param boardFrame 
    * 
    * @return 
    */
   int genMove(int kind, GoGamePiece& piece, const GoGameFrame& boardFrame);

   /** 
    * generate one move through Go Engine Process
    * 
    * @param kind 
    */
   int genMove(int kind, GoGamePiece& piece);

   /** 
    * get last move
    * 
    * 
    * @return 
    */
   GoGamePiece MetaMachine::lastMove();

   /** 
    * 
    * 
    * 
    * @return 
    */
   int capturesBlack();

   /** 
    * 
    * 
    * 
    * @return 
    */
   int capturesWhite();

   /** 
    * 
    * 
    * @param color 
    * 
    * @return 
    */
   int captures(const std::string& color);

   /** 
    * 
    * 
    * 
    * @return 
    */
   std::string estimateScore();
   
private:

   /** 
    * 
    * 
    * @param inPipe 
    * @param outPipe 
    */
   MetaMachine(Poco::Pipe& inPipe, Poco::Pipe& outPipe);

   /** 
    * drop dump response
    * 
    */
   void dropDumpResponse();

   /** 
    * read first line, and then drop dump response
    * 
    * @param buf buffer
    * @param size buffer's size
    */
   void readFirstLineDropDumpResponse(char *buf, int size);

   Poco::PipeInputStream _istr;
   Poco::PipeOutputStream _ostr;
   int _boardsize;
   std::list<AIMachine> _aiMachines;
   Poco::Mutex        _mutex;
};


#endif /* end of MetaMachine.h */
