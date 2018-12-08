/*
    //  Copyright © 2018 Zihan Chen. All rights reserved.
*/
//#define CD_DEBUG
#include "card.h"
#include "cardDeck.h"
#include "deck_C.h"

#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <random>   

using std::cout;
using std::endl;
//using std::array;
using std::srand;
using std::shuffle;
using std::vector;

class Card;

CardDeck CardDeck::s_CardDeck;
//CardDeck::CardDeck(){

    /*
    Card::FaceAnimal fa[5];
    Card::FaceBackGround fb[5];
    buildCard(fa, fb);

    int i,j;
    for(i=0;i<d_HEIGHT;++i){
        for(j=0;j<d_WIDTH;++j){
            this->card[i][j] = new Card(fa[i],fb[j]); // building 25 cards 
        }
    }
*/
//}
void CardDeck::buildCard(Card::FaceAnimal (&fa)[5], Card::FaceBackGround (&fb)[5]){
    for(int i = Card::CRAB;i<=Card::WALRUS;++i){
        fa[i] = static_cast<Card::FaceAnimal>(i);
    }
    for(int i = Card::RED;i<=Card::YELLOW;++i){
        fb[i] = static_cast<Card::FaceBackGround>(i);
    }
}

void CardDeck::shuffles(){
    srand((unsigned)time(0));
   // _Random_shuffle1()
    auto rng = std::default_random_engine {};
    shuffle(s_CardDeck.storage.begin(),s_CardDeck.storage.end(),rng);
    // generate missing card for the game 
    //s_CardDeck.storage.erase(s_CardDeck.storage.end());
}


CardDeck& CardDeck::make_CardDeck(){
   // static CardDeck s_CardDeck;

    Card::FaceAnimal fa[5];
    Card::FaceBackGround fb[5];
    buildCard(fa, fb);

    int i,j;
    for(i=0;i<d_HEIGHT;++i){
        for(j=0;j<d_WIDTH;++j){
            /*
            can't use Card c(fa[i],fb[j]) because it will be deleted after this fcuntion done? --yes
            */
            s_CardDeck.storage.push_back(new Card(fa[i],fb[j]));
        }
    }
    s_CardDeck.shuffles();
    return s_CardDeck;
}


// correct way to delete ?-- yes
CardDeck::~CardDeck(){
     for(auto p:s_CardDeck.storage){
         if(p!=nullptr){
             delete p;
         }
         
     }
}

#ifdef CD_DEBUG
#include <cassert>
#include <iostream>
#include <vector>
using namespace std;
    int main(){ // used to tset all public funcs

        CardDeck &cd = CardDeck::make_CardDeck();
        vector<Card*> cv;
        while(!cd.isEmpty()){
            cv.push_back(cd.getNext());
        }
        
        //assert(cv.size()>=0); // there is card in vector
        if(cv.size()>0){
            cout<<"pass first test"<<endl;
        }
    }


#endif