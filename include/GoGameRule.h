/**
 * @file   GoGameRule.h
 * @author WuYao <wuyao721@163.com>
 * @date   Wed Jan 11 21:26:31 2012
 * 
 * @brief  go game rule
 * 
 * 
 */

#ifndef _GO_GAME_RULE_H_
#define _GO_GAME_RULE_H_

#include <string>

struct GoGameRule
{
   const static int BoardSize9;
   const static int BoardSize11;
   const static int BoardSize13;
   const static int BoardSize19;
   const static int BoardSizeMax;
   const static int PieceKindBlack;
   const static int PieceKindWhite;
   const static int PieceKindEmpty;
   const static std::string StrPieceKindBlack;
   const static std::string StrPieceKindWhite;
   const static std::string StrPieceKindEmpty;

   /** 
    * get the kind's string
    * 
    * @param kind 
    * 
    * @return 
    */
   static const std::string& strOfKind(int kind);

   /** 
    * get the string's kind
    * 
    * @param kind 
    * 
    * @return 
    */
   static int kindOfStr(const std::string& str);

   /** 
    * is kind black
    * 
    * @param kind 
    * 
    * @return 
    */
   static bool isKindBlack(int kind);

   /** 
    * is kind black
    * 
    * @param kind 
    * 
    * @return 
    */
   static bool isKindBlack(const std::string& kind);

   /** 
    * is kind white
    * 
    * @param kind 
    * 
    * @return 
    */
   static bool isKindWhite(int kind);

   /** 
    * is kind white
    * 
    * @param kind 
    * 
    * @return 
    */
   static bool isKindWhite(const std::string& kind);

   /** 
    * is kind empty
    * 
    * @param kind 
    * 
    * @return 
    */
   static bool isKindEmpty(int kind);
   
   /** 
    * generate coordinate's string format
    * 
    * @param x 
    * @param y 
    * 
    * @return 
    */
   static std::string strOfCoordinate(int boardsize, int x, int y);

   /** 
    * get from GNUGO
    * 
    * @param boardsize 
    * @param str 
    * @param m y
    * @param n x
    * 
    * @return 
    */
   static int GoGameRule::stringToLocation(int boardsize, const char *str, int *m, int *n);
};

#endif /* end of GoGameRule.h */
