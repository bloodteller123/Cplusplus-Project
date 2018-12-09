/*
    //  Copyright © 2018 Zihan Chen. All rights reserved.
*/

//#define RULES_DEBUG;
#include "rules.h"
#include "game.h"
#include "player.h"
//#include "card.h"


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
       _count = 0;
       return true;
   }
   restart = false;
   return false;

}

const Player& Rules::getNextPlayer(const Game& game){
 
//till find next active player
    
    if(_count >= players.size()){
        _count = 0;
    }
   // cout<<"_count FOR Current player: "<<_count<<endl;
    const Player& player = game.getPlayer(players[_count].getSide());

     _count++;
   // cout<<"_count for Next player: "<<_count<<endl;
    return player;
    
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
    if(ind >= players.size()){
        ind = 0;
    }
    if(_count>=players.size()){
        _count = 0;
    }
    _count++;
}

void Rules::walrus(){   
    cout<<"Special ability of walrus is activated if round is not over"<<endl;
    
}


#ifdef RULES_DEBUG
#include <cassert>
#include <iostream>
#include <vector>
using namespace std;
    int main(){ // used to tset all public funcs
         Board b;
         Game g(b,"1");
        vector<Player> v;
        v.emplace_back("JOHN",0);
        v.emplace_back("TOM",0);
        v[0].setSide(Player::Side::top);
        v[1].setSide(Player::Side::bottom); // set up for two players


        Rules r(v);
        assert(r.gameOver(g)== false); // gamestart ---> shouldbe false
        cout<<"pass first assert"<<endl;

        assert(r.roundOver(g)== false); //  two players are active, should return false
        cout<<"pass second assert"<<endl;

        g.setCurrentCard(g.getCard(Game::Letter::A,Game::Number::Number1));
        g.setCurrentCard(g.getCard(Game::Letter::B,Game::Number::Number1));
        if(r.isValid(g) || !r.isValid(g)){
            cout<<"pass third test"<<endl;
        }

        while(g.getRound()!=7){
            g.nextRound();
        }
        
        assert(r.gameOver(g)== true); // rounds = 7
        cout<<"pass final assert"<<endl;

    }


#endif