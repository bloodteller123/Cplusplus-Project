#ifndef GAME
#define GAME
/*
    //  Copyright © 2018 Zihan Chen. All rights reserved.
*/
#include "board.h"
#include "player.h"
#include "card.h"

#include <iostream>
#include <vector>
#include <functional>
#include <string>

using std::ostream;
using std::vector;
using std::string;

class Player;
class Board;

//Board::Number;
class Game{
    
    protected:
        int _round;
        friend ostream& operator<<(ostream& os, const Game& game);
        mutable vector<Player> players; // why can only set to mutable?
        string mode;
    // vector<std::reference_wrapper<const Card*>> CardStorage; // used to store previous/current card
        const Card* currentCard = nullptr;
        const Card* previousCard = nullptr;
        //Board board;
        Board& board;
        vector<string> neighbours;
    public:
        
    
    
        typedef Board::Letter Letter;//////////////////
        typedef Board::Number Number;
        Game(Board&,string);
        int getRound() const;
        void nextRound();
        //void push_back (const value_type& val);---> vector can be used here
        void addPlayer(const Player&);
        Player& getPlayer(Player::Side) const;
        const Card* getPreviousCard() const; // using linked list ? or maybe put create a vector of size 2/3/4 ? 
        const Card* getCurrentCard() const;
        void setCurrentCard(const Card*);
        Card* getCard(const Letter&,const Number&);
        void setCard(const Letter&,const Number&, Card*);

// used in expert mode
        vector<string>& getNeighbour(const Letter&,const Number&);
        void setBlock(bool,const Letter&,const Number&);
        int getNFUCard();
        void updatePosition(const Letter&,const Number&,const Letter&,const Number&);
        //void turnFaceDown(const Letter&,const Number&);
        //bool isFaceUp(const Letter&, const Number&) const;



};




#endif