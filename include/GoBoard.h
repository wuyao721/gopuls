/**
 * @file   GoBoard.h
 * @author WuYao <wuyao721@163.com>
 * @date   Sun Apr 17 23:16:40 2011
 * 
 * @brief  
 * 
 * 
 */

#ifndef _GO_BOARD_H_
#define _GO_BOARD_H_

#include <windows.h>
#include <list>
#include "WindowBitmap.h"

#include "GoGameRule.h"
#include "GoGameFrame.h"
#include "GoGamePiece.h"

#define NEXT_TURN_TO_PLAY_OPPONENT -1
#define NEXT_TURN_TO_PLAY_USER 1
#define NEXT_TURN_TO_PLAY_UNKNOW 0

#define NEXT_MOVE_KIND_BLACK 1
#define NEXT_MOVE_KIND_WHITE -1
#define NEXT_MOVE_KIND_UNKNOW 0

class GoBoard
{
public:
   
   /** 
    * boardsize is unknown 
    * 
    */
   GoBoard();

   /** 
    * boardsize is known 
    * 
    * @param boardsize 
    */
   GoBoard(int boardsize);

   /** 
    * 
    * 
    * 
    */
   virtual ~GoBoard();

   /** 
    * whether a go board
    * 
    * 
    * @return 
    */
   virtual bool isGoBoard();

   /** 
    * whether the go game prepared
    * 
    * 
    * @return 
    */
   virtual bool isPrepared();

   /** 
    * whether the go game started
    * 
    * 
    * @return 
    */
   virtual bool isStarted();

   /** 
    * get next move kind
    * 
    * 
    * @return 
    */
   virtual int nextMoveKind();

   /** 
    * get which turn to play
    * 
    * 
    * @return 
    */
   virtual int whichTurnToPlay();
   
   /** 
   * get go board's information
   * 
   * 
   * @return 
   */
   const GoGameFrame& getGoGameFrame();

   /** 
    * get user of player's kind
    * 
    * 
    * @return 
    */
   virtual bool getStatus() = 0;

   /** 
    * play a move
    * 
    * @param x 
    * @param y 
    */
   void playMove(int x, int y);

   /** 
    * 
    * 
    * @param x 
    * @param y 
    */
   void drawRectangle(int x, int y);

   /** 
    * 
    * 
    * @param x 
    * @param y 
    */
   //void draw_debug();

   /** 
    * start, prepared to play
    * 
    */
   virtual void start();

   /** 
    * pass one move
    * 
    */
   virtual void pass();

   /** 
    * resign
    * 
    * @param absoluteCoordinate 
    */
   virtual void resign();

protected:

   // whether the screen is a go board
   bool _isGoBoard;

   // whether the go board started
   bool _started;

   // whether the go board prepared
   bool _prepared;

   // which turn to play
   int _whichTurnToPlay;

   // GoGameRule::PlayerKindBlack, GoGameRule::PlayerKindWhite, GoGameRule::PlayerKindUnknow
   int _nextMoveKind;

   // screen's bitmap data
   WindowBitmap* _bitmap;
   
   // go game frame
   GoGameFrame _goGameFrame;

   // compute from _bitmap
   // left-top coordinate of go board
   int _leftTopX, _leftTopY;

   // compute from _bitmap
   // last chessman's coordinate of go board
   //int _lastPieceX, _lastPieceY;

   // suppose or guess
   // board size(from 9 to 19)
   int _boardsize;

   // a grid edge have bits
   // depend on the go game application
   // eg. QQ go game is 35 bits
   int _gridLen;

   // the whole edge have bits
   // depend on _gridEdgeLen and _boardSize
   //int _edgeLen;        

   int _pieces[19][19];
   
   // black
   int _blackColorRedDown;
   int _blackColorRedUp;
   int _blackColorGreenDown;
   int _blackColorGreenUp;
   int _blackColorBlueDown;
   int _blackColorBlueUp;

   // white
   int _whiteColorRedDown;
   int _whiteColorRedUp;
   int _whiteColorGreenDown;
   int _whiteColorGreenUp;
   int _whiteColorBlueDown;
   int _whiteColorBlueUp;

   // edge
   int _edgeColorRedDown;
   int _edgeColorRedUp;
   int _edgeColorGreenDown;
   int _edgeColorGreenUp;
   int _edgeColorBlueDown;
   int _edgeColorBlueUp;

   // board
   int _boardColorRedDown;
   int _boardColorRedUp;
   int _boardColorGreenDown;
   int _boardColorGreenUp;
   int _boardColorBlueDown;
   int _boardColorBlueUp;

   // last one
   int _lastOneColorRedDown;
   int _lastOneColorRedUp;
   int _lastOneColorGreenDown;
   int _lastOneColorGreenUp;
   int _lastOneColorBlueDown;
   int _lastOneColorBlueUp;

   // last one black
   int _lastOneBlackColorRedDown;
   int _lastOneBlackColorRedUp;
   int _lastOneBlackColorGreenDown;
   int _lastOneBlackColorGreenUp;
   int _lastOneBlackColorBlueDown;
   int _lastOneBlackColorBlueUp;
   
   // last one white
   int _lastOneWhiteColorRedDown;
   int _lastOneWhiteColorRedUp;
   int _lastOneWhiteColorGreenDown;
   int _lastOneWhiteColorGreenUp;
   int _lastOneWhiteColorBlueDown;
   int _lastOneWhiteColorBlueUp;
   
   // buttons box rectangle
   bool _isAbsoluteCoordinate;
   RECT _startButtonRect;
   RECT _passButtonRect;
   RECT _resignButtonRect;

protected:

   /** 
    * scan go board and fetch go game information
    * 
    */
   virtual void scanGoBoard();

   /** 
    * whether point(x, y) board edge, and left-top
    * 
    * @param x x-coordinate of screen
    * @param y y-coordinate of screen
    * 
    * @return 
    */
   virtual bool isEdgeLeftTop(int x, int y);

   /** 
    * whether point(x, y) board edge, and top edge, and grid top corner
    * 
    * @param x x-coordinate of screen
    * @param y y-coordinate of screen
    * 
    * @return 
    */
   virtual bool isTopEdgeGridTopCorner(int x, int y);

   /** 
    * whether point(x, y), and grid corner
    * 
    * @param x x-coordinate of screen
    * @param y y-coordinate of screen
    * 
    * @return 
    */
   virtual bool isGridCorner(int x, int y);

   /** 
    * whether point(x, y), and grid cross corner 
    * 
    * @param x x-coordinate of screen
    * @param y y-coordinate of screen
    * 
    * @return 
    */
   virtual bool isGridCrossCorner(int x, int y);

   /** 
    * find left-top 
    * 
    * @param x x-coordinate of screen
    * @param y y-coordinate of screen
    * 
    * @return 
    */
   virtual bool findLeftTop(int x, int y);

   /** 
    * scan all grid
    * 
    * @return 
    */
   virtual bool scanAllGrid();

   /** 
    * scan one grid
    * 
    * @param x x-coordinate of screen
    * @param y y-coordinate of screen
    * @param i x-coordinate of go game
    * @param j y-coordinate of go game
    * 
    * @return 
    */
   virtual GoGamePiece scanOneGrid(int x, int y, int i, int j);

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
    * whether point(x, y) board edge
    * 
    * @param x x-coordinate of screen
    * @param y y-coordinate of screen
    * 
    * @return 
    */
   bool isPointEdge(int x, int y);

   /** 
    * whether point(x, y) black
    * 
    * @param x x-coordinate of screen
    * @param y y-coordinate of screen
    * 
    * @return 
    */
   bool isPointBlack(int x, int y);

   /** 
    * whether point(x, y) white
    * 
    * @param x x-coordinate of screen
    * @param y y-coordinate of screen
    * 
    * @return 
    */
   bool isPointWhite(int x, int y);

   /** 
    * whether point(x, y) board 
    * 
    * @param x x-coordinate of screen
    * @param y y-coordinate of screen
    * 
    * @return 
    */
   bool isPointBoard(int x, int y);
   
   /** 
    * whether point(x, y)'s piece black
    * 
    * @param x x-coordinate of screen
    * @param y y-coordinate of screen
    * @param last whether last piece
    * 
    * @return 
    */
   virtual bool isPieceBlack(int x, int y, bool& last) = 0;

   /** 
    * whether point(x, y)'s piece white
    * 
    * @param x x-coordinate of screen
    * @param y y-coordinate of screen
    * @param last whether last piece
    * 
    * @return 
    */
   virtual bool isPieceWhite(int x, int y, bool& last) = 0;
   
   /** 
    * whether point(x, y) last piece
    * 
    * @param x x-coordinate of screen
    * @param y y-coordinate of screen
    * 
    * @return 
    */
   virtual bool isLastPiece(int x, int y);

   /** 
    * whether point(x, y) last piece and it's black
    * 
    * @param x x-coordinate of screen
    * @param y y-coordinate of screen
    * 
    * @return 
    */
   virtual bool isLastBlackPiece(int x, int y);

   /** 
    * whether point(x, y) last piece and it's white
    * 
    * @param x x-coordinate of screen
    * @param y y-coordinate of screen
    * 
    * @return 
    */
   virtual bool isLastWhitePiece(int x, int y);

private:
   
};

#endif /* end of GoBoard.h */
