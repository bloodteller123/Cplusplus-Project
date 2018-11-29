/*
    //  Copyright © 2018 Zihan Chen. All rights reserved.
*/
#include "rules.h"
#include "game.h"
#include "player.h"
#include "card.h"


#include <iostream>
#include <algorithm> 
#include <vector>
#include <string>


using std::cout;
using std::endl;
using std::vector;
using std::cin;
using std::string;

class Player;
bool restart = false;
Rules::Rules(vector<Player>& vec):players(vec){
    for(int i=0;i<vec.size();++i){
        activeP.push_back(true);
    }
}


bool Rules::isValid(const Game& game){
    if((*game.getCurrentCard())(true) == (*game.getPreviousCard())(true)){
             cout<<"Animal Macthed"<<endl;
             return true;
         }else if((*game.getCurrentCard())==(*game.getPreviousCard())){
         cout<< "BackGround Matched"<<endl;
         return true;
     }else{
         cout<<"Nothing Matched"<<endl;
         return false;
     }
}



bool Rules::gameOver(const Game& game){
    if(game.getRound() == 7){
        return true;
    }
    return false;

}

bool Rules::roundOver(const Game& game){

    for(int i=0;i<players.size();++i){
        if(game.getPlayer(players[i].getSide()).isActive()){
            activeP.at(i) = true;
        }
        else{
            activeP.at(i) = false;
        }
    }
    int count = 0;
   for(int i=0;i<activeP.size();++i){
       if(activeP[i] == true){
           count ++;
       }
   }
   if(count==1){
       restart = true;
       return true;
   }
   restart = false;
   return false;

}

const Player& Rules::getNextPlayer(const Game& game){
    if(restart)
        _count = 0;
// may be a for loop herer?

//till find next active player
cout<<_count<<endl;
    if(_count >= players.size()){
        _count = 0;
    }
    const Player& player = game.getPlayer(players[_count].getSide());
    _count++;

    return player;
    
}

string Rules::triggerAbility(const Game& game,int& ind){
    Card::FaceAnimal fa = (*game.getCurrentCard())(true);
    switch(fa){
        case  Card::CRAB: {
            crab();
            return "CRAB";
            break;
            }
        case  Card::PENGUIN: {
            penguin();
            return "PENGUIN";
            break;}

        case  Card::OCTOPUS: {
            octopus();
            return "OCTOPUS";
            break;
            }
        case  Card::TURTLE: {
            turtle(ind);
            return "TURTLE";
            break;
            }
        case  Card::WALRUS: {
            walrus();
            return "WALRUS";
            break;
            }
    }

}

void Rules::crab(){
    cout<<"Special ability of crab is activated if round is not over"<<endl;
    _count--;
}
void Rules::penguin(){
    cout<<"Special ability of penguin is activated if round is not over"<<endl;
    
}

void Rules::octopus(){
    cout<<"Special ability of octopus is activated if round is not over"<<endl;
    
}

void Rules::turtle(int& ind){
    cout<<"Special ability of turtle is activated if round is not over"<<endl;
    ind++;
    if(ind == players.size()){
        ind = 0;
    }
    _count++;
}

void Rules::walrus(){   
    cout<<"Special ability of walrus is activated if round is not over"<<endl;
    
}

