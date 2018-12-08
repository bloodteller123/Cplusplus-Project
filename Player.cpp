/*
    //  Copyright © 2018 Zihan Chen. All rights reserved.
*/
//#define PLAYER_DEBUG
#include "player.h"
#include "reward.h"

#include <string>
#include <iostream>

//#define PLAYER_DEBUG

using std::ostream;
using std::string;

// constructor

void setAcive(bool status);
Player::Player(string name,int r):_name(name),ruby(r){
    /*
    switch(s){
        case top: position = "top";break;
        case bottom: position = "bottom";break;
        case left: position = "left";break;
        case right: position = "right";break;
    }
    */
    setAcive(true);
    
}

string Player::getName(){
    return this->_name;
}

void Player::setAcive(bool status){
    this->active = status;
    this->active?sleep="active":sleep="inactive";
}

bool Player::isActive() const{
   
    return this->active;
}
int Player::getNRubies(){
    return this->ruby;
}

/// TO BE COMPLETED
void Player::addReward(const Reward& c_Reward){
    this->ruby += c_Reward;
}

// TO BE COMPLETED
void Player::setDisplayMode(bool end){
    this->endOfGame = end;
}


//TO BE CHECKED
ostream& operator<<(ostream& os, const Player& player){
    
    if(player.endOfGame){
        os<<player._name<<": "<<player.ruby<<" rubies";
    }
    else{
        os<<player._name <<": " << player.position<<" ("<<player.sleep<<")"<<"\n";
    }
    
    return os;
}

Player::Side Player::getSide() const{
    return this->side;
}

void Player::setSide(Player::Side s){
    
    this->side = s;
     
    switch(this->side){
        case Side::top: {
            position = "top";
            break;
        }
        case Side::bottom:{
            position = "bottom";
            break;
        } 
        case Side::left:{
            position = "left";
            break;
        } 
        case Side::right:{
            position = "right";
            break;
        } 
    }
     
}



#ifdef PLAYER_DEBUG
#include <cassert>
#include <iostream>
    int main(){ // used to tset all public funcs
        Player p("TOM",0);

        assert(p.getName()=="TOM");
        std::cout<<"pass first assert"<<std::endl;
        p.setAcive(false);

        assert(false==p.isActive());
        std::cout<<"pass second assert"<<std::endl;

        // void addReward(const Reward&)?

        p.setDisplayMode(true);
        std::cout<<p<<std::endl;

        p.setSide(Player::Side::top);
        assert(p.getSide() == Player::Side::top);
        std::cout<<"pass last assert"<<std::endl;

    }


#endif