#ifndef REWARD
#define REWARD
/*
    //  Copyright © 2018 Zihan Chen. All rights reserved.
*/
#include "rewardDeck.h"
#include <iostream>

using std::ostream;

class RewardDeck;

class Reward{
    const int ruby;
    friend RewardDeck;
    friend ostream& operator<<( ostream&, const Reward& ); 
    Reward(int r);
    //public:
    Reward( const Reward& ); // non construction-copyable
    Reward& operator=( const Reward& ); // non copyable
    public:
        operator int() const;

};


#endif