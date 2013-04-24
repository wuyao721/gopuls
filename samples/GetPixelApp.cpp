#include <windows.h>
#include <stdio.h>

void func()
{
   HDC     hDC;              // 屏幕设备描述表
   int     width, height;    // 位图宽度和高度

   // 为屏幕创建设备描述表
   hDC = CreateDC("DISPLAY", NULL, NULL, NULL);

   // 获得屏幕分辨率
   width = GetDeviceCaps(hDC, HORZRES);
   height = GetDeviceCaps(hDC, VERTRES);
   
   COLORREF* colref = (COLORREF*)malloc(width*height);
   COLORREF* ref;
   int i, j;
   for( i = 0; i < height; i++ ){
      for( j = 0; j < width; j++ ){
         ref = colref + (j + i * j);
         *ref = GetPixel(hDC, i, j);
      }
   }
   free(colref);
}

int main()
{
   func();
}
