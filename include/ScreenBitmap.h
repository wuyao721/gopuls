
#ifndef _SCREEN_BITMAP_H_
#define _SCREEN_BITMAP_H_

class ScreenBitmap
{
   BITMAP m_bmp;
   BYTE* m_bits;

public:
   ScreenBitmap();
   ~ScreenBitmap();
   
   int width();
   int height();
   BYTE getR(int x, int y);
   BYTE getG(int x, int y);
   BYTE getB(int x, int y);
};
 

#endif /* end of ScreenBitmap.h */
