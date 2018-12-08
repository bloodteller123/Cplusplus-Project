/*
    //  Copyright © 2018 Zihan Chen. All rights reserved.
*/

//#define RD_DEBUG
#include "rewardDeck.h"
#include "deck_C.h"
#include "reward.h"
#include <vector>

#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <random>  

#define NReward 7
using std::vector;
using std::srand;
using std::shuffle;

class Reward;

RewardDeck RewardDeck::s_RewardDeck;

RewardDeck::RewardDeck(){


}

void RewardDeck::shuffles(){
    srand((unsigned)time(0));
   // _Random_shuffle1()
    auto rng = std::default_random_engine {};
    shuffle(s_RewardDeck.storage.begin(),s_RewardDeck.storage.end(),rng);
}

RewardDeck& RewardDeck::make_RewardDeck(){
    int i;
    for(i=0;i<NReward;++i){
        if(i>2){
            if(i>4){
                if(i==6){// 1 rewards with 4 ruby
                    s_RewardDeck.storage.push_back(new Reward(4));
                }else{
                    s_RewardDeck.storage.push_back(new Reward(3));
                }
            }
            else{// 2 rewards with 2 ruby
                s_RewardDeck.storage.push_back(new Reward(2));
            }
        }
        else{ // 3 rewards with 1 ruby
            s_RewardDeck.storage.push_back(new Reward(1));
        }
    }
    s_RewardDeck.shuffles();
    return s_RewardDeck;
}

RewardDeck::~RewardDeck(){
    for(auto p:s_RewardDeck.storage){
         if(p!=nullptr){
             delete p;
         }
         
     }
}

#ifdef RD_DEBUG
#include <cassert>
#include <iostream>
#include <vector>
using namespace std;
    int main(){ // used to tset all public funcs

        RewardDeck &rd = RewardDeck::make_RewardDeck();
        vector<Reward*> reward;
        while(!rd.isEmpty()){
            reward.push_back(rd.getNext());
        }
        assert(reward.size()>=0); // there is reward in vector

        cout<<"pass first assert"<<endl;
        


    }


#endif
