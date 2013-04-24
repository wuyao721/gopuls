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

class GoBoard
{
protected:
   int _left;           // left coordinates of go board
   int _top;            // top coordinates of go board
   int _boardSize;      // board size(from 9 to 19)
   int _edgeLen;        // the whole edge have bits
   int _gridEdgeLen;    // a grid edge have bits

   // grids
   int _grids[GoBoardInfo::BoardSizeMax][GoBoardInfo::BoardSizeMax];
   
   std::list<COLORREF> _blackColorList;
   std::list<COLORREF> _whiteColorList;
   std::list<COLORREF> _edgeColorList;

public:
   GoBoard* instance();

   /** 
    * whether point(x, y) belong to go board edge
    * 
    * @param hDC
    * @param x 
    * @param y 
    * 
    * @return 
    */
   virtual bool isEdge(HDC& hDC, int x , int y);

   /** 
    * whether point(x, y) empty
    * 
    * @param hDC
    * @param x 
    * @param y 
    * 
    * @return 
    */
   virtual bool isEmpty(HDC& hDC, int x , int y);

   /** 
    * whether point(x, y) black
    * 
    * @param hDC
    * @param x 
    * @param y 
    * 
    * @return 
    */
   virtual bool isBlack(HDC& hDC, int x , int y);

   /** 
    * whether point(x, y) white
    * 
    * @param hDC
    * @param x 
    * @param y 
    * 
    * @return 
    */
   virtual bool isWhite(HDC& hDC, int x , int y);

   /** 
    * scan the go board
    * 
    */
   virtual void scan();
   
   /** 
    * print
    * 
    */
   virtual void print();

   void getGoBoardInfo1();
   
   void 
};

#endif /* end of GoBoard.h */
