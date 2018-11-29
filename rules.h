#ifndef RULES
#define RULES
/*
    //  Copyright © 2018 Zihan Chen. All rights reserved.
*/
#include "game.h"
#include "player.h"

#include <vector>

using std::vector;

class Game;
class Player;
class Rules{

    bool restart = false;

    
    protected:
        vector<Player> players;
        vector<bool> activeP;
    // vector<Player::Side> s;
        int _count = 0;
        Player::Side helper();
        void crab();
        void penguin();
        void octopus();
        void turtle(int&);
        void walrus();

    
    public:
        Rules(vector<Player>& vec);
        bool isValid(const Game&);
        bool gameOver(const Game&);
        bool roundOver(const Game&);
        const Player& getNextPlayer(const Game&);

//used in expert mode
        //string triggerAbility(const Game&,int& ind);

};


#endif