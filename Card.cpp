/*
    //  Copyright © 2018 Zihan Chen. All rights reserved.
*/
#include "card.h"
#include <string>
#include <iostream>

#define WIDTH 3
#define HEIGHT 3

using std::string;

using std::cout;
using std::endl;
using std::ostream;


//string card[HEIGHT][WIDTH];
//string animal,bg;
bool check;


Card::Card(Card::FaceAnimal fa, Card::FaceBackGround fb): FA(fa),FB(fb){
    int i,j;
    check = false;
    switch(FA){
        case CRAB: animal = "C";break;
        case PENGUIN: animal = "P";break;
        case OCTOPUS: animal = "O";break;
        case TURTLE: animal = "T";break;
        case WALRUS: animal = "W";break;
    }
    switch(FB){
        case RED: bg = "r";break;
        case GREEN: bg = "g";break;
        case PURPLE: bg = "p";break;
        case BLUE: bg = "b";break;
        case YELLOW: bg = "y";break;
    }
    for(i=0;i<HEIGHT;++i){ // set card with color and animal
            for(j=0;j<WIDTH;++j){
                if(j==1 && i==1)
                    card[i][j] = animal;
                else
                    card[i][j] = bg;
            } 
        }

}

string Card::operator() (int row){
    int column = 0;
    return (card[row][column++] + card[row][column++]+card[row][column++]);
}


int Card::getNRows(){
    return HEIGHT;
}


//TESTING DRIVER

#ifdef CARD_DEBUG
#include <cassert>
#include <iostream>

/* The following public methods are tested
 
 int getNRows;
 
 */

int main (){
    
    Card c;
    assert(c.getNRows() == 3 ); //Height is defined as 3, therefore
    std::cout << "pass first assert" << std::endl; //getNRows must return 3
    
}

#endif
