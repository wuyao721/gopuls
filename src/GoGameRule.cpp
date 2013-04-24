#include <Poco/Format.h>
#include <Poco/String.h>

#include "GoGameRule.h"

const int GoGameRule::BoardSize9 = 9;
const int GoGameRule::BoardSize11 = 11;
const int GoGameRule::BoardSize13 = 13;
const int GoGameRule::BoardSize19 = 19;
const int GoGameRule::BoardSizeMax = 19;
const int GoGameRule::PieceKindBlack = 1;
const int GoGameRule::PieceKindWhite = -1;
const int GoGameRule::PieceKindEmpty = 0;
const std::string GoGameRule::StrPieceKindBlack = "black";
const std::string GoGameRule::StrPieceKindWhite = "white";
const std::string GoGameRule::StrPieceKindEmpty = "";

const std::string& GoGameRule::strOfKind(int kind)
{
   if( kind == GoGameRule::PieceKindBlack ){
      return GoGameRule::StrPieceKindBlack;
   }

   else if( kind == GoGameRule::PieceKindWhite ){
      return GoGameRule::StrPieceKindWhite;
   }
      
   return GoGameRule::StrPieceKindEmpty;
}

int GoGameRule::kindOfStr(const std::string& str)
{
   if( 0 == Poco::icompare(str, GoGameRule::StrPieceKindBlack)  ){
      return GoGameRule::PieceKindBlack;
   }

   if( 0 == Poco::icompare(str, GoGameRule::StrPieceKindWhite)  ){
      return GoGameRule::PieceKindWhite;
   }

   return GoGameRule::PieceKindEmpty;
}

bool GoGameRule::isKindBlack(int kind)
{
   return ( kind == GoGameRule::PieceKindBlack );
}

bool GoGameRule::isKindBlack(const std::string& kind)
{
   return ( kind == GoGameRule::StrPieceKindBlack );
}

bool GoGameRule::isKindWhite(int kind)
{
   return ( kind == GoGameRule::PieceKindWhite );
}

bool GoGameRule::isKindWhite(const std::string& kind)
{
   return ( kind == GoGameRule::StrPieceKindWhite );
}

bool GoGameRule::isKindEmpty(int kind)
{
   return ( kind != GoGameRule::PieceKindBlack && kind != GoGameRule::PieceKindWhite );
}

/*
 *   GNUGO's go game board, there is no 'i'
 *
 *       A B C D E F G H J K L M N O P Q R S T
 *    19 . . . . . . . . . . . . . . . . . . . 19
 *    18 . . . . . . . . . . . . . . . . . . . 18
 *    17 . . . . . . . . . . . . . . . . . . . 17
 *    16 . . . + . . . . . + . . . . . X . . . 16
 *    15 . . . . . . . . . . . . . . . . . . . 15
 *    14 . . . . . . . . . . . . . . . . . . . 14
 *    13 . . . . . . . . . . . . . . . . . . . 13
 *    12 . . . . . . . . . . . . . . . . . . . 12
 *    11 . . . . . . . . . . . . . . . . . . . 11     WHITE (O) has captured 0 stones
 *    10 . . . + . . . . . + . . . . . + . . . 10     BLACK (X) has captured 0 stones
 *     9 . . . . . . . . . . . . . . . . . . . 9
 *     8 . . . . . . . . . . . . . . . . . . . 8
 *     7 . . . . . . . . . . . . . . . . . . . 7
 *     6 . . . . . . . . . . . . . . . . . . . 6
 *     5 . . . . . . . . . . . . . . . . . . . 5
 *     4 . . . + . . . . . + . . . . . + . . . 4
 *     3 . . . . . . . . . . . . . . . . . . . 3
 *     2 . . . . . . . . . . . . . . . . . . . 2
 *     1 . . . . . . . . . . . . . . . . . . . 1
 *       A B C D E F G H J K L M N O P Q R S T
*/
std::string GoGameRule::strOfCoordinate(int boardsize, int x, int y)
{
   char c = 'A' + x;
   if(c>='I'){c++;}
   return Poco::format("%c%i", c, static_cast<int>(boardsize - y));
}

int GoGameRule::stringToLocation(int boardsize, const char *str, int *y, int *x)
{
   if (*str == '\0')
      return 0;

   if (!isalpha((int) *str))
      return 0;
   *x = tolower((int) *str) - 'a';
   if (tolower((int) *str) >= 'i')
      --*x;
   if (*x < 0 || *x > boardsize - 1)
      return 0;

   if (!isdigit((int) *(str+1)))
      return 0;
   *y = boardsize - atoi(str + 1);
   if (*y < 0 || *y > boardsize - 1)
      return 0;

   return 1;
}

