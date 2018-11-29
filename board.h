#ifndef BOARD
#define BOARD
/*
    //  Copyright © 2018 Zihan Chen. All rights reserved.
*/
#include "card.h"
#include "reward.h"
#include "cardDeck.h"

#include <iostream>
#include <vector>
#include <string>
#include <map>

using std::vector;
using std::ostream;
using std::string;
using std::map;

class Card;
class Reward;
class Board{
    public:
        enum Letter{
            A=0,
            B=1,
            C=2,
            D=3,
            E=4
        };
        enum Number{
            Number1=0,
            Number2=1,
            Number3=2,
            Number4=3,
            Number5=4
        };

    protected:
        friend ostream& operator<<(ostream& os, const Board& board);
        CardDeck &cd = CardDeck::make_CardDeck();
        vector<Card*> v_card;
        vector<Reward*> v_reward;
        vector<Card*> v_container;
        
        vector<string> position;
        map<Board::Letter,string> letter;
        map<Board::Number,string> number;

        vector<bool> faceup;
        vector<bool> help;

        string b_array[19];
        string e_array[3];

        int size;
        int rows;
        int _size;

        void updateBaseBoard(string (&)[19],const Letter&, const Number&);
        void initializeBaseBoard(string (&)[19]);
        void initializeExpertBoard(string (&)[3]);
        void updateExpertBoard(string (&)[3],const Letter& l, const Number& n);

        void buildLetter(std::map<Board::Letter,string> &l);
        void buildNumber(std::map<Board::Number,string> &n);
        

        string _mode;
        vector<string> _neighbours;
        vector<bool> isBlock;
        bool block = false;
        vector<Card*> expertHelpCard;
    public:
        Board();
        bool isFaceUp(const Letter&, const Number&) const;
        bool turnFaceUp(const Letter&, const Number&);
        bool turnFaceDown(const Letter&, const Number&);
        Card* getCard(const Letter&, const Number&);
        void setCard(const Letter&, const Number&,Card*);
        void reset();

    // used in expert mode
        //void setMode(string);
        //vector<string>& getNeighbour(const Letter&,const Number&);
        //void setBlock(bool,const Letter&,const Number&);
       // int getNFUCard();
       // void updatePosition(const Letter&  ,const Number&  ,const Letter&  ,const Number&  );

};

#endif