#include <windows.h>
#include <winnt.h>
#include <stdio.h>

#include "GoBoardDC.h"

GoBoardDC* GoBoardDC::instance(int boardsize)
{
   HDC     hDC;              // 屏幕设备描述表
   int     width, height;    // 位图宽度和高度
   
   // 为屏幕创建设备描述表
   hDC = CreateDC("DISPLAY", NULL, NULL, NULL);

   // 获得屏幕分辨率
   width = GetDeviceCaps(hDC, HORZRES);
   height = GetDeviceCaps(hDC, VERTRES);

   int w; int h;

   // scan screen from left to right, top to bottom
   for( h = 0; h < height - _edgeLen; h++){ // 防止棋盘的底已经超过图片的高度
      for( w = 0; w < width - _edgeLen; w++){ // 棋盘的右边已经超过图片的宽度
         
         if( isEdge(GetPixel(hDC, w, h)) ) {
            
            // 判断是否为棋盘的横边
            int i;
            for(i = w + 1; i < w + _edgeLen - 1; i++ ){
               if( !isEdge(hDC, i, h) ) {
                  goto cont;
               }
            }
            
            // 判断是否为棋盘的竖边
            int j;
            for(j = h + 1; j < h + _edgeLen - 1; j++ ){
               if( !isEdge(GetPixel(hDC, w, j)) ) {
                  goto cont;
               }
            }
            
            // 找到棋盘
            return new GoBoardDC(w, h);
           cont:
			;
         }
      }
   }
	
   // 没有找到
   return NULL;
}

GoBoardDC::GoBoardDC(int boardsize)
   _goBoardInfo(boardsize)
{
   
}

bool GoBoardDC::isEdge(HDC& hDC, int x , int y)
{
   COLORREF rgb = GetPixel(hDC, x, y);

   std::list<COLORREF>::iterator it;
   for( it = _edgeColorList.begin(); it != _edgeColorList.end(); it++ ){
      if( rgb == *it  ){
         return true;
      }
   }
   return false;
}

bool GoBoardDC::isEmpty(HDC& hDC, int x , int y)
{
   return isEdge(hDC, x, y);
}

bool GoBoardDC::isBlack(HDC& hDC, int x , int y)
{
   COLORREF rgb = GetPixel(hDC, x, y);

   std::list<COLORREF>::iterator it;
   for( it = _blackColorList.begin(); it != _blackColorList.end(); it++ ){
      if( rgb == *it  ){
         return true;
      }
   }
   return false;
}

bool GoBoardDC::isWhite(HDC& hDC, int x , int y)
{
   COLORREF rgb = GetPixel(hDC, x, y);

   std::list<COLORREF>::iterator it;
   for( it = _whiteColorList.begin(); it != _whiteColorList.end(); it++ ){
      if( rgb == *it  ){
         return true;
      }
   }
   return false;
}

void GoBoardDC::scan()
{
   HDC     hDC;           // 屏幕设备描述表

   // 为屏幕创建设备描述表
   hDC = CreateDC("DISPLAY", NULL, NULL, NULL);

   int i, j;
   for( i = 0; i < _goBoardInfo.boardsize(); i++ ){
      for( j = 0; j < _goBoardInfo.boardsize(); j++ ){
         int x = i * _gridEdgeLen + _left;
         int y = j * _gridEdgeLen + _top;

         // empty
         if( isEmpty(hDC, x, y) ){
            _pieces[i][j] = 0;
         }
         
         // black
         else if( isBlack(hDC, x, y) ){
            _pieces[i][j] = 0;
         }

         // black
         else if( isBlack(hDC, x, y) ){
            _pieces[i][j] = 0;
         }
         
         // error
         else{
            printf("unknow grid(%d, %d) rgb: %d", i, j, rgb);
         }
      }
   }
}

void GoBoardDC::print(){
   int i, j;
   for( i = 0; i < _goBoardInfo.boardsize(); i++ ){
      for( j = 0; j < _goBoardInfo.boardsize(); j++ ){
         printf(" ");
         
         if( _pieces[i][j] == 0 ){
            printf(".");
         }

         else if( _pieces[i][j] == 0 ){
            printf("X");
         }

         else if( _pieces[i][j] == 0 ){
            printf("O");
         }

         printf(" ");
      }
      printf("\n");
   }
}


#if 0
int main()
{
   GoBoardDC19* goBoard19 = dynamic_cast<GoBoardDC19*>(GoBoardDC::instance());
   goBoard19->scan();
   goBoard19->print();
   return 0;
}
#endif
