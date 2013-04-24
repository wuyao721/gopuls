#include "EWeiQiGoBoard.h"

// TODO
// 对方pass一步
// title 弈城TYGEM对弈 381x144 中间位置
// button 确认 80x25

// 自动开始 
// title 对局申请 477x417
// button 申请 105x37
// button 接受 105x37

EWeiQiGoBoard::EWeiQiGoBoard():
   ScalableGoBoard(GoGameRule::BoardSize19)
{
   if( NULL == (_bitmap = WindowBitmap::getWindowBitmap("LiveBaduk.exe")) ){
      return;
   }

   // black
   _blackColorRedDown = 0;
   _blackColorRedUp = 77;
   _blackColorGreenDown = 0;
   _blackColorGreenUp = 77;
   _blackColorBlueDown = 0;
   _blackColorBlueUp = 77;

   // white
   _whiteColorRedDown = 200;
   _whiteColorRedUp = 255;
   _whiteColorGreenDown = 200;
   _whiteColorGreenUp = 255;
   _whiteColorBlueDown = 200;
   _whiteColorBlueUp = 255;

   // edge
   _edgeColorRedDown = 0;
   _edgeColorRedUp = 30;
   _edgeColorGreenDown = 0;
   _edgeColorGreenUp = 10;
   _edgeColorBlueDown = 0;
   _edgeColorBlueUp = 0;

   // board
   _boardColorRedDown = 220;
   _boardColorRedUp = 255;
   _boardColorGreenDown = 190;
   _boardColorGreenUp = 255;
   _boardColorBlueDown = 60;
   _boardColorBlueUp = 190;

   // last one
   // not useful
   //_lastOneColorRedDown = 255;
   //_lastOneColorRedUp = 255;
   //_lastOneColorGreenDown = 255;
   //_lastOneColorGreenUp = 255;
   //_lastOneColorBlueDown = 255;
   //_lastOneColorBlueUp = 255;

   // last one white color
   _lastOneWhiteColorRedDown = 0;
   _lastOneWhiteColorRedUp = 0;
   _lastOneWhiteColorGreenDown = 0;
   _lastOneWhiteColorGreenUp = 0;
   _lastOneWhiteColorBlueDown = 255;
   _lastOneWhiteColorBlueUp = 255;

   // last one black color
   _lastOneBlackColorRedDown = 255;
   _lastOneBlackColorRedUp = 255;
   _lastOneBlackColorGreenDown = 255;
   _lastOneBlackColorGreenUp = 255;
   _lastOneBlackColorBlueDown = 255;
   _lastOneBlackColorBlueUp = 255;

   _isAbsoluteCoordinate = true;

   getButtonPosition();
   
   ScalableGoBoard::scanGoBoard();
}

EWeiQiGoBoard::~EWeiQiGoBoard()
{
   if( _bitmap ){
      delete _bitmap;
   }
}

bool EWeiQiGoBoard::confirmMessageBox(const std::string& askString)
{
   DWORD processID;
   HWndProcess hWndProcess;

   if( (processID = getProcessIDFromName("LiveBaduk.exe")) == -1 ){
      return false;
   }

   hWndProcess.processID = processID;
   if( false == EnumWindows(matchProcessMessageBoxWindowEnumProc, (LPARAM)&hWndProcess) ){

      // 185, 100
      RECT rect;
      if( ! GetWindowRect(hWndProcess.hWnd, &rect) ||
          (rect.right - rect.left) != 185          ||
          (rect.bottom - rect.top) != 100          ){
         return false;
      }

      char buffer[256];
      HWND hWndYesButton = NULL;
      RECT rectYesButton;
      bool bWindow = false;
      HWND hWndChild = GetWindow(hWndProcess.hWnd, GW_CHILD);
      while( hWndChild ){
         GetWindowText(hWndChild, buffer, 255);
         if( strcmp(askString.c_str(), buffer) == 0 ){
            bWindow = true;
         }else if( strcmp("是(&Y)", buffer) == 0 ){
            //75x23
            hWndYesButton = hWndChild;
         }

         hWndChild = GetNextWindow(hWndChild, GW_HWNDNEXT);
      }

      if( bWindow && hWndYesButton ){
         GetWindowRect(hWndYesButton, &rectYesButton);
         WindowBitmap::clickScreen(rectYesButton.right-(rectYesButton.right-rectYesButton.left)/2,
                                   rectYesButton.bottom-(rectYesButton.bottom-rectYesButton.top)/2);
         return true;
      }
   }
   return false;
}

void EWeiQiGoBoard::pass()
{
   GoBoard::pass();
   
   // TODO
   Sleep(100);
   
   confirmMessageBox("'要‘停一招’吗？");
}

void EWeiQiGoBoard::resign()
{
   GoBoard::resign();
   
   // TODO
   Sleep(100);
   
   confirmMessageBox("要认输吗？");
}

bool EWeiQiGoBoard::getStatus()
{
   _started = true;
   _prepared = true;
   _nextMoveKind = NEXT_MOVE_KIND_UNKNOW;
   _whichTurnToPlay = NEXT_TURN_TO_PLAY_UNKNOW;

   return true;
}

bool EWeiQiGoBoard::isPieceBlack(int x, int y, bool& last)
{
   last = false;

   if( ! isPointBoard(x-(_gridLen-1)/2, y-(_gridLen-1)/2) || // left-top
       ! isPointBoard(x+(_gridLen-1)/2, y-(_gridLen-1)/2) || // right-top
       ! isPointBoard(x-(_gridLen-1)/2, y+(_gridLen-1)/2) || // left-bottom
       ! isPointBoard(x+(_gridLen-1)/2, y+(_gridLen-1)/2) ){ // right-bottom
      goto end;
   }

   // last one
   /*
    *    bbbbb
    *    bgggg
    *    bggg
    *    bgg
    *    bg
    */
   if( isLastBlackPiece(x, y)     && 
       isLastBlackPiece(x+1, y)   && 
       isLastBlackPiece(x, y+1)   && 
       isLastBlackPiece(x+1, y+1) ){
      last = true;
   }
   
   // if mouse move here, will paint a black/white block on the go board
   if( _bitmap->rgbEqual(x, y, x+1, y+1) && 
       _bitmap->rgbEqual(x, y, x-1, y-1) && 
       _bitmap->rgbEqual(x, y, x, y+1)   && 
       _bitmap->rgbEqual(x, y, x+1, y)   ){
      goto end;
   }

   // black 
   if( isPointBlack(x, y-1)   &&
       isPointBlack(x-1, y)   &&
       isPointBlack(x-1, y+1) &&
       isPointBlack(x+1, y-1) ){
      return true;
   }

  end:
   last = false;
   return false;
}

bool EWeiQiGoBoard::isPieceWhite(int x, int y, bool& last)
{
   last = false;

   if( ! isPointBoard(x-(_gridLen-1)/2, y-(_gridLen-1)/2) || // left-top
       ! isPointBoard(x+(_gridLen-1)/2, y-(_gridLen-1)/2) || // right-top
       ! isPointBoard(x-(_gridLen-1)/2, y+(_gridLen-1)/2) || // left-bottom
       ! isPointBoard(x+(_gridLen-1)/2, y+(_gridLen-1)/2) ){ // right-bottom
      goto end;
   }

   /*
    *    wwwww
    *    wgggg
    *    wggg
    *    wgg
    *    wg
    */

   // last one
   if( isLastWhitePiece(x, y)     && 
       isLastWhitePiece(x+1, y)   && 
       isLastWhitePiece(x, y+1)   && 
       isLastWhitePiece(x+1, y+1) ){
      last = true;;
      return true;
   }
   
   // if mouse move here, will paint a black/white block on the go board
   if( _bitmap->rgbEqual(x, y, x+1, y+1) && 
       _bitmap->rgbEqual(x, y, x-1, y-1) && 
       _bitmap->rgbEqual(x, y, x, y+1)   && 
       _bitmap->rgbEqual(x, y, x+1, y)   ){
      goto end;
   }
       
   // white 
   if( isPointWhite(x, y-1)   &&
       isPointWhite(x-1, y)   &&
       isPointWhite(x-1, y+1) &&
       isPointWhite(x+1, y-1) ){
      return true;
   }
   
  end:
   last = false;
   return false;
}

GoGamePiece EWeiQiGoBoard::scanOneGridUnderMouse(int x, int y, int i, int j)
{
   bool last = false;
   GoGamePiece piece(i, j);

   /*
    *  bbbb
    *  bbbb
    *  bbbb
    *  bbbb
    */

   // if mouse move here, will paint a black/white block on the go board
   if( ! _bitmap->rgbEqual(x, y, x+1, y+1) || 
       ! _bitmap->rgbEqual(x, y, x-1, y-1) || 
       ! _bitmap->rgbEqual(x, y, x, y+1)   || 
       ! _bitmap->rgbEqual(x, y, x+1, y)   ){
      piece.setX(-1);
      piece.setY(-1);
      return piece;
   }

   if( GoBoard::isPointBoard(x+_gridLen/2-3, y-1) ){
      piece.setKind(GoGameRule::PieceKindEmpty);
   }else if( GoBoard::isPointBlack(x+_gridLen/2-3, y-1) ){
      piece.setKind(GoGameRule::PieceKindBlack);
   }else{
      piece.setKind(GoGameRule::PieceKindWhite);
   }
   
   piece.setLastPiece(last);
   return piece;
}

bool EWeiQiGoBoard::getButtonPosition()
{
   RECT rectParent;
   RECT rectChild;
   HWND hWndChild;

   GetWindowRect(_bitmap->_hWnd, &rectParent);

   int m, n;
   hWndChild = GetWindow(_bitmap->_hWnd, GW_CHILD);
   while( hWndChild ){
      GetWindowRect(hWndChild, &rectChild);

      m = (rectParent.right - rectParent.left) - (rectChild.right - rectChild.left);
      n = (rectParent.bottom - rectParent.top) - (rectChild.bottom - rectChild.top);
      if( IsWindowVisible(hWndChild) && m > 0 && m < 100 && n > 0 && n < 100 ){
         goto childWindow;
      }
	  hWndChild = GetNextWindow(hWndChild, GW_HWNDNEXT);
   }
   return false;

  childWindow:
   int childChildWindowHeight = 54;
   hWndChild = GetWindow(hWndChild, GW_CHILD);
   while( hWndChild ) {
      RECT childRect;
      GetWindowRect(hWndChild, &childRect);
      if( (childRect.bottom - childRect.top) == childChildWindowHeight ){
         goto childChildWindow;
      }
      hWndChild = GetNextWindow(hWndChild, GW_HWNDNEXT);
   }
   return false;

  childChildWindow:
   int childChildChildWindowHeight = 50;
   hWndChild = GetWindow(hWndChild, GW_CHILD);
   while( hWndChild ) {
      RECT childRect;
      GetWindowRect(hWndChild, &childRect);
      if( (childRect.bottom - childRect.top) == childChildChildWindowHeight ){
         goto last;
      }
      hWndChild = GetNextWindow(hWndChild, GW_HWNDNEXT);
   }
   return false;

  last:
   // get buttons postion
   int buttonBoxWidth = 73;
   int buttonBoxHeight = 20;
   std::list<RECT> buttonBoxList;
   hWndChild = GetWindow(hWndChild, GW_CHILD);
   while( hWndChild ){
      RECT childRect;

      GetWindowRect(hWndChild, &childRect);
      if( (childRect.right - childRect.left) == buttonBoxWidth  &&
          (childRect.bottom - childRect.top) == buttonBoxHeight ){
         buttonBoxList.push_back(childRect);
      }
      hWndChild = GetNextWindow(hWndChild, GW_HWNDNEXT);
   }

   // TODO
   // start button
   // 右上角弟三个

   std::list<RECT>::iterator it;
   RECT leftMostRect;
   RECT secondLeftRect;
   leftMostRect.left = 0;
   leftMostRect.right = 0;
   leftMostRect.top = 0;
   leftMostRect.bottom = 0;
   secondLeftRect.left = 0;
   secondLeftRect.right = 0;
   secondLeftRect.top = 0;
   secondLeftRect.bottom = 0;

   // pass button
   if( (it = buttonBoxList.begin()) != buttonBoxList.end() ){
      secondLeftRect = leftMostRect = *it;
      it++;

      for(; it != buttonBoxList.end(); it++){
         if( it->left < leftMostRect.left ){
            secondLeftRect = leftMostRect;
            leftMostRect = *it;
         }
      }
   }
   _passButtonRect = secondLeftRect;

   RECT bottomRightMostRect;
   bottomRightMostRect.left = 0;
   bottomRightMostRect.right = 0;
   bottomRightMostRect.top = 0;
   bottomRightMostRect.bottom = 0;

   // resign
   if( (it = buttonBoxList.begin()) != buttonBoxList.end() ){
      bottomRightMostRect = *it;
      it++;

      for(; it != buttonBoxList.end(); it++){
         if( it->right >= bottomRightMostRect.right && it->bottom >= bottomRightMostRect.bottom ){
            bottomRightMostRect = *it;
         }
      }
   }
   _resignButtonRect = bottomRightMostRect;

   return true;
}

//
//bool EWeiQiGoBoard::isTopEdgeGridTopCorner(int x, int y)
//{
//   if( x-1<0 || y-1<0 || x+1>=_bitmap.width() || y+1>=_bitmap.height()){
//      return false;
//   }
//
///*
// * grid top corner of top edge like this:
// *    bbb
// *     e
// *    beb
// */
//   bool b = 
//      isEdge(x, y)      && // middle
//      isEdge(x, y+1)    && // down
//      isBoard(x, y-1)   && // up
//      isBoard(x-1, y-1) && // left-up
//      isBoard(x+1, y+1) && // right-down
//      isBoard(x-1, y+1) && // left-down
//      isBoard(x+1, y-1);   // right-down
//   if(b){
//      int i = 0;
//      i++;
//   }
//   return b;
//}
