#include "derivedGame.h"
#include "derivedBoard.h"
#include "game.h"
#include "board.h"

#include <string>
using std::string;


DerivedGame::DerivedGame(DerivedBoard& board,string mode):Game(board,mode),extandableBoard(board){
    extandableBoard.setMode(mode);
}


vector<string>& DerivedGame::getNeighbour(const Letter& l,const Number& n){
    return extandableBoard.getNeighbour(l,n);
}

void DerivedGame::setBlock(bool isBlocked,const Letter& l,const Number& n){
    extandableBoard.setBlock(isBlocked,l,n);
}


int DerivedGame::getNFUCard(){
    return extandableBoard.getNFUCard();
}

void DerivedGame::updatePosition(const Letter& l1,const Number& n1,const Letter& l2,const Number& n2){
    extandableBoard.updatePosition( l1,  n1,  l2,  n2);
}

