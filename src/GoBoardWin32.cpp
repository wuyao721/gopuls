#include <windows.h>
#include <winnt.h>
#include <stdio.h>

#include "GoBoard.h"

GoBoard* GoBoard::instance()
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
   for( h = 0; h < height - QQ_GO_19_EDGE_BIT_LENGTH; h++){ // 防止棋盘的底已经超过图片的高度
      for( w = 0; w < width - QQ_GO_19_EDGE_BIT_LENGTH; w++){ // 棋盘的右边已经超过图片的宽度
         
         if( isEdge(GetPixel(hDC, w, h)) ) {
            
            // 判断是否为棋盘的横边
            int i;
            for(i = w + 1; i < w + QQ_GO_19_EDGE_BIT_LENGTH - 1; i++ ){
               if( !isEdge(hDC, i, h) ) {
                  goto cont;
               }
            }
				
            // 判断是否为棋盘的竖边
            int j;
            for(j = h + 1; j < h + QQ_GO_19_EDGE_BIT_LENGTH - 1; j++ ){
               if( !isEdge(GetPixel(hDC, w, j)) ) {
                  goto cont;
               }
            }
            
            // 找到棋盘
            return new GoBoard19(w, h);
           cont:
			;
         }
      }
   }
	
   // 没有找到
   return NULL;
}

bool GoBoard::isEdge(HDC& hDC, int x , int y)
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

bool GoBoard::isEmpty(HDC& hDC, int x , int y)
{
   return isEdge(hDC, x, y);
}

bool GoBoard::isBlack(HDC& hDC, int x , int y)
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

bool GoBoard::isWhite(HDC& hDC, int x , int y)
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

void GoBoard::scan()
{
   HDC     hDC;           // 屏幕设备描述表

   // 为屏幕创建设备描述表
   hDC = CreateDC("DISPLAY", NULL, NULL, NULL);

   int i, j;
   for( i = 0; i < _boardSize; i++ ){
      for( j = 0; j < _boardSize; j++ ){
         int x = i * _gridEdgeLen + _left;
         int y = j * _gridEdgeLen + _top;

         // empty
         if( isEmpty(hDC, x, y) ){
            _grids[i][j] = 0;
         }
         
         // black
         else if( isBlack(hDC, x, y) ){
            _grids[i][j] = 0;
         }

         // black
         else if( isBlack(hDC, x, y) ){
            _grids[i][j] = 0;
         }
         
         // error
         else{
            printf("unknow grid(%d, %d) rgb: %d", i, j, rgb);
         }
      }
   }
}

void GoBoard::print(){
   int i, j;
   for( i = 0; i < _boardSize; i++ ){
      for( j = 0; j < _boardSize; j++ ){
         printf(" ");
         
         if( _grids[i][j] == 0 ){
            printf(".");
         }

         else if( _grids[i][j] == 0 ){
            printf("X");
         }

         else if( _grids[i][j] == 0 ){
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
   GoBoard19* goBoard19 = dynamic_cast<GoBoard19*>(GoBoard::instance());
   goBoard19->scan();
   goBoard19->print();
   return 0;
}
#endif
