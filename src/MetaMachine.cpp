/**
 * @file   MetaMachine.cpp
 * @author WuYao <wuyao721@163.com>
 * @date   Wed Apr 20 17:18:22 2011
 * 
 * @brief  This class sits between goplus and a GTP engine,
 *         thanks to GNUGO's metachine.c.
 *
 *                  internal          pipe a
 *           goplus ----> MetaMachine -----> GTP engine
 *                  <----             <-----
 *                  internal          pipe b
 */

//#include <windows.h>

#include <fstream>

#include <Poco/Mutex.h>
#include <Poco/ScopedLock.h>
#include <Poco/Process.h>
#include <Poco/PipeStream.h>
#include <Poco/StreamCopier.h>
#include <Poco/StringTokenizer.h>

#include "MetaMachine.h"
#include "ProcessHack_WIN32.h"
#include "GoPlusContext.h"

#define GTP_BUFSIZE 1000

MetaMachine::MetaMachine(Poco::Pipe& inPipe, Poco::Pipe& outPipe):
   _istr(outPipe),
   _ostr(inPipe),
   _boardsize(GoGameRule::BoardSize19)
{
}

MetaMachine::~MetaMachine()
{
   Poco::Mutex::ScopedLock lock(_mutex);
   _ostr << "quit" << std::endl;
}

MetaMachine* MetaMachine::newProcess(char* sgfPath)
{
   GoPlusContext& context = GoPlusContext::instance();

   std::string command = context.getGoAIEngineCommand();

//   Poco::StringTokenizer tokens(command, " ");
//   Poco::StringTokenizer::Iterator it;
//   if( tokens.count() == 0 ){
//      return NULL;
//   }
//   std::string cmd(tokens[0]);
//   std::vector<std::string> args;
//   int i; 
//   for( i=1; i<tokens.count(); i++ ){
//      args.push_back(tokens[i]);
//   }
//      
   Poco::Pipe outPipe;
   Poco::Pipe inPipe;
   //Poco::ProcessHandle ph = Poco::Process::launch(cmd, args, &inPipe, &outPipe, 0);
   ProcessHack::launch(command, &inPipe, &outPipe, 0);

   return new MetaMachine(inPipe, outPipe);
}


void MetaMachine::init(const GoGameFrame& frame)
{
   clearBoard();

   int i, j;
   for(i=0; i<frame.boardsize();i++)
   {
      for(j=0;j<frame.boardsize();j++){
         play(frame.getPiece(j, i));
      }
   }
}

void MetaMachine::setBoardSize(int boardsize)
{
   Poco::Mutex::ScopedLock lock(_mutex);
   _ostr << "boardsize " << boardsize << std::endl;
   _boardsize = boardsize;
   dropDumpResponse();
}

void MetaMachine::trySetBoardSize(int boardsize)
{
   Poco::Mutex::ScopedLock lock(_mutex);
   char line[GTP_BUFSIZE];

   _ostr << "query_boardsize" << std::endl;
   readFirstLineDropDumpResponse(line, sizeof(line));

   if( strlen(line) < 2 || line[0] != '=' || line[1] != ' ' ){
      return;
   }
   int currentBoardSize = atoi(line + 2);
   if( currentBoardSize != boardsize ){
      setBoardSize(boardsize);
   }
}

int MetaMachine::capturesBlack()
{
   return captures("black");
}

int MetaMachine::capturesWhite()
{
   return captures("white");
}

int MetaMachine::captures(const std::string& color)
{
   Poco::Mutex::ScopedLock lock(_mutex);
   char line[GTP_BUFSIZE];

   _ostr << "captures " << color << std::endl;

   readFirstLineDropDumpResponse(line, sizeof(line));
   
   if( strlen(line) < 2 || line[0] != '=' || line[1] != ' ' ){
      return 0;
   }

   if (!isdigit((int) *(line+2))){
      return 0;
   }

   return atoi(line + 2);
}

std::string MetaMachine::estimateScore()
{
   Poco::Mutex::ScopedLock lock(_mutex);
   std::string output;
   char line[GTP_BUFSIZE];

   _ostr << "estimate_score" << std::endl;

   readFirstLineDropDumpResponse(line, sizeof(line));
   
   if( strlen(line) < 2 || line[0] != '=' || line[1] != ' ' ){
      return output;
   }

   output = line+2;
   
   return output;
}

void MetaMachine::clearBoard()
{
   Poco::Mutex::ScopedLock lock(_mutex);
   _ostr << "clear_board" << std::endl;

   dropDumpResponse();
}

GoGameFrame MetaMachine::getGoGameFrame()
{
   Poco::Mutex::ScopedLock lock(_mutex);
   GoGameFrame frame(_boardsize);
   char line[GTP_BUFSIZE];

   // black pieces
   _ostr << "list_stones black" << std::endl;
   readFirstLineDropDumpResponse(line, sizeof(line));
   if( strlen(line) < 2 || line[0] != '=' || line[1] != ' ' ){
      return frame;
   }
   Poco::StringTokenizer tokensBlack(line+2, " ",
                                Poco::StringTokenizer::TOK_TRIM | Poco::StringTokenizer::TOK_IGNORE_EMPTY);
   Poco::StringTokenizer::Iterator it;
   for(it=tokensBlack.begin(); it != tokensBlack.end(); it++){
      int x;
      int y;
      GoGameRule::stringToLocation(_boardsize, it->c_str(), &y, &x);
      GoGamePiece piece(x, y, GoGameRule::PieceKindBlack);
      frame.setPiece(piece);
   }
   
   // white pieces
   _ostr << "list_stones white" << std::endl;
   readFirstLineDropDumpResponse(line, sizeof(line));
   if( strlen(line) < 2 || line[0] != '=' || line[1] != ' ' ){
      return frame;
   }
   Poco::StringTokenizer tokensWhite(line+2, " ",
                                Poco::StringTokenizer::TOK_TRIM | Poco::StringTokenizer::TOK_IGNORE_EMPTY);
   for(it=tokensWhite.begin(); it != tokensWhite.end(); it++){
      int x;
      int y;
      GoGameRule::stringToLocation(_boardsize, it->c_str(), &y, &x);
      GoGamePiece piece(x, y, GoGameRule::PieceKindWhite);
      frame.setPiece(piece);
   }

   //last piece
   GoGamePiece lastPiece = MetaMachine::lastMove();
   frame.setLastPiece(lastPiece);
   
   return frame;
}

GoGamePiece MetaMachine::lastMove()
{
   Poco::Mutex::ScopedLock lock(_mutex);
   GoGamePiece piece;

   _ostr << "last_move" << std::endl;

   char line[GTP_BUFSIZE];

   readFirstLineDropDumpResponse(line, sizeof(line));

   if( strlen(line) < 2 || line[0] != '=' || line[1] != ' ' ){
      return piece;
   }

   if( strstr(line, "BLACK") || strstr(line, "black") ){
      piece.setKind(GoGameRule::PieceKindBlack);
   }else if( strstr(line, "WHITE") || strstr(line, "white") ){
      piece.setKind(GoGameRule::PieceKindWhite);
   }else{
      return piece;
   }

   int x;
   int y;
   GoGameRule::stringToLocation(_boardsize, line+8, &y, &x);

   piece.setX(x);
   piece.setY(y);
   piece.setLastPiece(true);
   return piece;
}

bool MetaMachine::play(const GoGamePiece& piece)
{
   Poco::Mutex::ScopedLock lock(_mutex);
   if( GoGameRule::isKindEmpty(piece.kind()) ){
      return false;
   }

   std::string str = GoGameRule::strOfCoordinate(_boardsize, piece.x(), piece.y());
   _ostr << "play" << " "
         << GoGameRule::strOfKind(piece.kind()) << " " 
         << str << std::endl;

   char line[GTP_BUFSIZE];

   readFirstLineDropDumpResponse(line, sizeof(line));
   if( strstr(line, "? illegal move") ){
      return false;
   }
   return true;
}

void MetaMachine::undo()
{
   Poco::Mutex::ScopedLock lock(_mutex);
   _ostr << "undo" << std::endl; 
   dropDumpResponse();
}

void MetaMachine::update(const GoGameFrame& boardFrame)
{
   trySetBoardSize(boardFrame.boardsize());

   GoGameFrame engineFrame = getGoGameFrame();
   if( engineFrame == boardFrame ){
      return;
   }

   if( ! play(boardFrame.lastPiece()) ){
      return;
   }

   engineFrame = getGoGameFrame();
   if( engineFrame == boardFrame ){
      return;
   }else{
      undo();
   }
}

int MetaMachine::genMove(int kind, GoGamePiece& piece, const GoGameFrame& boardFrame)
{
   trySetBoardSize(boardFrame.boardsize());

   GoGameFrame engineFrame = getGoGameFrame();
   if( engineFrame == boardFrame ){
      return genMove(kind, piece);
   }

   play(boardFrame.lastPiece());
   engineFrame = getGoGameFrame();
   if( engineFrame == boardFrame ){
      return genMove(kind, piece);
   }else{
      init(boardFrame);
      return genMove(kind, piece);
   }
}

int MetaMachine::genMove(int kind, GoGamePiece& piece)
{
   Poco::Mutex::ScopedLock lock(_mutex);
   _ostr << "reg_genmove " << GoGameRule::strOfKind(kind) << std::endl; 

   char line[GTP_BUFSIZE];

   readFirstLineDropDumpResponse(line, sizeof(line));

   if( strlen(line) < 2 || line[0] != '=' || line[1] != ' ' ){
      return -1;
   }

   if( strstr(line, "PASS") || strstr(line, "pass") ){
      return 1;
   }

   if( strstr(line, "RESIGN") || strstr(line, "resign") ){
      return 2;
   }

   int x;
   int y;
   GoGameRule::stringToLocation(_boardsize, line+2, &y, &x);

   piece.setX(x);
   piece.setY(y);
   piece.setKind(kind);

   return 0;
}

void MetaMachine::dropDumpResponse()
{
   int line_length = 0;
   char line[GTP_BUFSIZE];

   while(line_length != 1){
      _istr.getline(line, sizeof(line));
      line_length = strlen(line);
   }
}

void MetaMachine::readFirstLineDropDumpResponse(char *line, int size)
{
   _istr.getline(line, size);

   dropDumpResponse();
}

class MetaMachineSingletonHolder
{
public:
	MetaMachineSingletonHolder()
	{
		_pObject = 0;
	}
	~MetaMachineSingletonHolder()
	{
       if(_pObject) delete _pObject;
	}
	MetaMachine* getDefault()
	{
		Poco::FastMutex::ScopedLock lock(_mutex);
		
		if (!_pObject)
		{
			_pObject = MetaMachine::newProcess(NULL);
		}
		return _pObject;
	}
	
private:
	MetaMachine* _pObject;
	Poco::FastMutex   _mutex;
};

namespace
{
	static MetaMachineSingletonHolder ct;
}


MetaMachine& MetaMachine::getDefault()
{
	return *ct.getDefault();
}
