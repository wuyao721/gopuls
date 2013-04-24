#include <windows.h>

class MyBitMap
{
   BITMAP m_bmp;
   HBITMAP m_hBmp;
   HBITMAP m_hOldBitmap;
   HDC m_hMemDc;   

public:
   MyBitMap(const std::string path);
   ~MyBitMap();
   bool find(const MyBitMap& myBitMap);
};


MyBitMap::MyBitMap(const std::string path)
{
   m_hBmp = (HBITMAP)LoadImage( AfxGetInstanceHandle(), 
                                path,
                                IMAGE_BITMAP,
                                0,
                                0,
                                LR_LOADFROMFILE);
   if( m_hBmp == NULL ){
      throw std::exception("CreateCompatibleDC NULL");
   }
   GetObject( m_hBmp, sizeof(BITMAP), &m_Bmp);

   if( NULL != (m_hMemDc = CreateCompatibleDC(NULL)) ){
      throw std::exception("CreateCompatibleDC NULL");
   }

   m_hOldBitmap = (HBITMAP)SelectObject(hMemDc, m_hBmp);
}

MyBitMap::~MyBitMap(const std::string path)
{
   SelectObject(m_hMemDc, m_hOldBitmap);
   DeleteDC(m_hMemDc);
   DeleteObject(m_hBmp);
}

bool MyBitMap::find(const MyBitMap& myBitMap)
{
   int i, j, m, n;
   bool match = false;

   for( i = 0 ; i < m_Bmp.bmWidth; i++ ){
      for( j = 0 ; j < m_Bmp.bmHeight; j++ ){
         COLORREF col1 = GetPixel(m_hMemDc, i, j);

         for( m = 0 ; m < myBitMap.m_Bmp.bmWidth; m++ ){
            for( n = 0 ; n < myBitMap.m_Bmp.bmHeight; n++ ){
               COLORREF col2 = GetPixel(myBitMap.m_hMemDc, m, n);
               if( col1 == col2 ){
                  match = true;
               }else{
                  match = false;
                  goto next;
               }
            }
         }

         if( match == true ){
            return true;
         }
        next:
      }
   }

   return false;
}

int main()
{
   MyBitMap bitmap1("big.bmp");
   MyBitMap bitmap2("small.bmp");
   if( true == bitmap1.find(bitmap2) ){
      std::cout << "find." << std::endl;
   }else{
      std::cout << "Not find!!!" << std::endl;
   }
}
