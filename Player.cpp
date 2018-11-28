/*
    //  Copyright © 2018 Zihan Chen. All rights reserved.
*/
#include "player.h"
#include "reward.h"

#include <string>
#include <iostream>

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
    this->ruby += c_Reward.operator int();
}

// TO BE COMPLETED
void Player::setDisplayMode(bool end){
    this->endOfGame = end;
}


//TO BE CHECKED
ostream& operator<<(ostream& os, const Player& player){
    os<<player._name <<": " << player.position<<" ("<<player.sleep<<")"<<"\n"
    <<"Once endOfGame is true: "<<"\n"<<player._name<<": "<<player.ruby<<" rubies";
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