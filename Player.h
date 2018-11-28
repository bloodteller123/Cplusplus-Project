#ifndef PLAYER
#define PLAYER
/*
    //  Copyright © 2018 Zihan Chen. All rights reserved.
*/
#include <string>
using std::string;
using std::ostream;

#include "reward.h"
class Reward;

class Player{/**
    enum class Side{
        top=0, 
        bottom=1, 
        left=2, 
        right=3
    }side;
**/
    friend ostream& operator<<( ostream&, const Player& ); 
    bool active = false;
    string _name;
    int ruby;
    bool endOfGame = false;

    string position = "";
    string sleep = "";
    public:
        enum Side{
        top=0, 
        bottom=1, 
        left=2, 
        right=3
        }side;

        Player(string name, int ruby);
        string getName();
        void setAcive(bool);
        bool isActive() const;
        int getNRubies();
        void addReward(const Reward&);
        void setDisplayMode(bool endOfGame);
        Side getSide() const;
        void setSide(Side side);

 
};


#endif