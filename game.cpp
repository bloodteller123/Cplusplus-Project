/*
    //  Copyright © 2018 Zihan Chen. All rights reserved.
*/
#include "game.h"
#include "board.h"

#include <vector>
#include <iostream>
#include <stdexcept>
#include <string>

using std::vector;
using std::ostream;
using std::out_of_range;
using std::string;
class Board;
/*
    note(?) So whenever getCard is called, store the card* in the cardStorage 
    compare it with previous card* (if exists), based on results, perform some actions,
    then delete the previous card from the cardStorage 
*/



Game::Game(Board& b,string s):mode(s),board(b){
    _round = 0;

    if(mode == "b"||(mode == "B")){
        std::cout<<"BASE MODE ON"<<std::endl;
    }
    if(mode == "e"||(mode == "E")){
        std::cout<<"EXPERT MODE ON"<<std::endl;
    }
    board.setMode(mode);
    
    /*
        TO BE COMPLETED
    */    
}

int Game::getRound() const{
    return _round;
}

void Game::nextRound(){ // TO BE COMPLETED 
    _round ++;
    board.reset();
    for(int i=0;i<players.size();++i){
        players[i].setAcive(true);
    }
}


void Game::addPlayer(const Player& player){
   
    players.push_back(player);

}


Player& Game::getPlayer(Player::Side side) const{
    for(int i=0;i<players.size();++i){
        if(players[i].getSide() == side){
            return players[i];
        }
    }

}

const Card* Game::getPreviousCard() const{
    /*
    if(CardStorage.size()<2){
        throw out_of_range("No Previous Card");
    }

    return CardStorage[0];
    */
   if(previousCard==nullptr){
       std::cout<<"NO PREVIOUS"<<std::endl;
       throw out_of_range("No Previous Card");
   }
   return previousCard;
}

const Card* Game::getCurrentCard() const{

    return currentCard;
    //return CardStorage[1];
}

Card* Game::getCard(const Letter& l, const Number& n){
    // get CARD means player choose this card ?
    //board.turnFaceUp(l,n);

    return board.getCard(l,n);
}

void Game::setCurrentCard(const Card* c){
    /*
    if(CardStorage.size()>2){
        CardStorage.erase(CardStorage.begin());
    }
    CardStorage.push_back(c);
    */
   if(c==nullptr){
       previousCard = c;
       currentCard = c;
       return;
   }
   if(previousCard!=nullptr){
       previousCard = currentCard;
       currentCard = c;

       return;
   }
   if(previousCard==nullptr){

       currentCard = c;
       previousCard = currentCard;
   }
   

}

void Game::setCard(const Letter& l, const Number& n, Card* c){
    board.setCard(l,n,c);
}

ostream& operator<<(ostream& os, const Game& game){
   

    os<<game.board<<"\n";
    for(int i=0;i<game.players.size();++i){
        os<<game.players[i]<<"\n";
    }

    return os;

}


vector<string>& Game::getNeighbour(const Letter& l,const Number& n){
    return board.getNeighbour(l,n);
}

void Game::setBlock(bool isBlocked,const Letter& l,const Number& n){
    board.setBlock(isBlocked,l,n);
}

int Game::getNFUCard(){
    return board.getNFUCard();
}

void Game::updatePosition(const Letter& l1,const Number& n1,const Letter& l2,const Number& n2){
    board.updatePosition( l1,  n1,  l2,  n2);
}
