#ifndef DERIVEDGAME
#define DERIVEDGAME

#include "game.h"
#include "board.h"
#include "derivedBoard.h"

#include <string>
using std::string;



class DerivedGame : public Game{



    DerivedBoard& extandableBoard;
   // Board& board;
    public:
        //DerivedGame() = default;
        DerivedGame(DerivedBoard&,string);
        vector<string>& getNeighbour(const Letter&,const Number&);
        void setBlock(bool,const Letter&,const Number&);
        int getNFUCard();
        void updatePosition(const Letter&,const Number&,const Letter&,const Number&);

};


#endif