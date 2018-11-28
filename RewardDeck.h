#ifndef REWARDDECK
#define REWARDDECK
/*
    //  Copyright © 2018 Zihan Chen. All rights reserved.
*/
#include "deck_C.h"
#include "reward.h"



class Reward;

class RewardDeck: public Deck_C<Reward>{
    RewardDeck( const RewardDeck& ); // non construction-copyable
    RewardDeck& operator=( const RewardDeck& ); // non copyable

    static RewardDeck s_RewardDeck;
    protected:
        RewardDeck();
        void shuffles() override;
        ~RewardDeck();

    public:
        static RewardDeck& make_RewardDeck();
};



#endif