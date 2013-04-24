#include <Poco/SharedPtr.h>
#include <Poco/String.h>

#include "GoGameWatcher.h"

#include "QQGoBoard.h"
#include "EWeiQiGoBoard.h"
#include "GoGameFrame.h"
#include "MetaMachine.h"

#include "GoPlusContext.h"
#include "StatusNotification.h"

GoGameWatcher::GoGameWatcher(): 
   _activity(this, &GoGameWatcher::runActivity),
   _context(GoPlusContext::instance())
{
}

void GoGameWatcher::start()
{
   _activity.start();
}

void GoGameWatcher::stop()
{
   _activity.stop(); // request stop
   _activity.wait(); // wait until activity actually stops
}

bool GoGameWatcher::isRunning()
{
   return _activity.isRunning();
}

void GoGameWatcher::runActivity()
{
   GoPlusContext& context = GoPlusContext::instance();

//   static GoGameFrame lastFrame(GoGameRule::BoardSize19);
   while (!_activity.isStopped())
   {
      try{
         //_context.notificationCenter().postNotification(new StatusNotification("正在分析棋盘..."));
         Poco::SharedPtr<GoBoard> board;
         std::string name = context.getGoBoardName();
         if( name == "弈城围棋" ){
            board = new EWeiQiGoBoard();
         }else if( name == "QQ围棋" ){
            board = new QQGoBoard();
         }

         if( ! board ){
            _context.notificationCenter().postNotification(new StatusNotification("未发现棋盘..."));
         }

         else if( ! board->isPrepared() ){
            if( context.isGoAutoPlay() && context.isGoAutoStart() ){
               board->start();
            }else{
               _context.notificationCenter().postNotification(new StatusNotification("请先准备..."));
            }
         }

         else if( ! board->isGoBoard() ){
            _context.notificationCenter().postNotification(new StatusNotification("未发现棋盘..."));
         }

         else if( ! board->isStarted() ){
            _context.notificationCenter().postNotification(new StatusNotification("等待对方准备..."));
         }

         else{
            //qqGoBoard->print();
            const GoGameFrame& frame = board->getGoGameFrame();
            const GoGamePiece& lastPiece = frame.lastPiece();

			MetaMachine::getDefault().update(frame);
            _context.notificationCenter().postNotification(
               new CapturesNotification(MetaMachine::getDefault().capturesBlack(), 
                                        MetaMachine::getDefault().capturesWhite()));

            // try to guess the next move kind
            int iWhichTurnToPlay = board->whichTurnToPlay();
            int iNextMoveKind = board->nextMoveKind();

            // if can not know next move kind form the 'go board', use the difference kind with last piece
            if( iNextMoveKind == NEXT_MOVE_KIND_UNKNOW ){
               
               // frame empty, turn for black to play
               if( frame.isEmpty() ){
                  iNextMoveKind = NEXT_MOVE_KIND_BLACK;
               }

               // last piece is black, so next move kind is white
               else if( GoGameRule::PieceKindBlack == lastPiece.kind() ){
                  iNextMoveKind = NEXT_MOVE_KIND_WHITE;
               }

               // last piece is white, so next move kind is black
               else if( GoGameRule::PieceKindWhite == lastPiece.kind() ){
                  iNextMoveKind = NEXT_MOVE_KIND_BLACK;
               } 
            }

            context.getGoPlayerKind();

            // if can not know which to play form the 'go board', use the config 
            if( iWhichTurnToPlay == NEXT_TURN_TO_PLAY_UNKNOW ) {
               if( (Poco::icompare(_context.getGoPlayerKind(), "black") == 0 && 
                    iNextMoveKind == NEXT_MOVE_KIND_BLACK                 ) ||
                   (Poco::icompare(_context.getGoPlayerKind(), "white") == 0 &&
                    iNextMoveKind == NEXT_MOVE_KIND_WHITE                 ) ){
                  iWhichTurnToPlay = NEXT_TURN_TO_PLAY_USER;
               }else{
                  iWhichTurnToPlay = NEXT_TURN_TO_PLAY_OPPONENT;
               }
            }

//            (GoGameRule::isKindWhite(nextMoveKind) && GoGameRule::isKindBlack(lastPiece.kind())) ||
//                (GoGameRule::isKindBlack(nextMoveKind) && GoGameRule::isKindWhite(lastPiece.kind())) ||
//                (GoGameRule::isKindBlack(nextMoveKind) && frame.isEmpty())                      
//            //board->draw_debug();

            // whether our turn to play
            if( iWhichTurnToPlay == NEXT_TURN_TO_PLAY_USER ){
               _context.notificationCenter().postNotification(new StatusNotification("正在调用AI引擎..."));
               //frame.print();

               GoGamePiece piece;
               int kind;
               switch(iNextMoveKind)
               {
                  case NEXT_MOVE_KIND_BLACK:
                  {
                     kind = GoGameRule::PieceKindBlack;
                     break;
                  }
                  case NEXT_MOVE_KIND_WHITE:
                  {
                     kind = GoGameRule::PieceKindWhite;
                     break;
                  }
                  default:
                  {
                  }
               }

               MetaMachine& machine = MetaMachine::getDefault();
               //machine.init(frame);
               //machine.play(piece);
               switch(machine.genMove(kind, piece, frame)){
                  case 0:
                  {
                     if( context.isGoAutoPlay() )
                     {
                        board->playMove(piece.x(), piece.y());
                     }
                  
                     if( context.isGoAutoMark() )
                     {
                        board->drawRectangle(piece.x(), piece.y());
                     }
                     break;
                  }
                  case 1:
                  {
                     if( context.isGoAutoPlay() && context.isGoAutoPass() ){
                        board->pass();
                     }
                     _context.notificationCenter().postNotification(new StatusNotification("AI引擎PASS"));
                     break;
                  }
                  case 2:
                  {
                     if( context.isGoAutoPlay() && context.isGoAutoResign() ){
                        board->resign();
                     }
                     _context.notificationCenter().postNotification(new StatusNotification("AI引擎认输"));
                     break;
                  }
               }
            }

            else{
               _context.notificationCenter().postNotification(new StatusNotification("对方还未下棋."));
            }
         }
      }
      catch(Poco::Exception& exc){
         std::string str = "出错了：";
         str += exc.message();
         _context.notificationCenter().postNotification(new StatusNotification(str));
      }
      catch(...){

      }
      Poco::Thread::sleep(1000);
   }
}
