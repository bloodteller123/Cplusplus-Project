/*
    //  Copyright © 2018 Zihan Chen. All rights reserved.
*/
//#define BOARD_DEBUG 
#include "board.h"
#include "cardDeck.h"
#include "rewardDeck.h"
#include "card.h"
#include "reward.h"

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <map>
#include <algorithm>
#include <exception>

using std::string;
using std::vector;
using std::ostream;
using std::map;



 
class NoMoreCards : public std::exception {
	public:
    const char * what () const throw(){
      return "No More Cards Available";
   }
};
   

Board::Board(){

    if(cd.isEmpty()){
        throw NoMoreCards();
    }

    while(!cd.isEmpty()){
    
        v_card.push_back(cd.getNext());
        faceup.push_back(false);
        help.push_back(false);
        isBlock.push_back(false);
    }
    

    size = v_card.size(); 
    _size = sqrt(size);
    rows = (*v_card[0]).getNRows();
    faceup[12] = true;
    help[12] = true;
     

    initializeBaseBoard(b_array);
    initializeExpertBoard(e_array);
    buildLetter(letter);
    buildNumber(number);
    
}



bool Board::isFaceUp(const Letter& l, const Number& n) const{

    if((!letter.count(l)||!number.count(n))){
        throw std::out_of_range("invalid position");
    }
    return faceup[l*_size + n]; 
    
}

bool Board::turnFaceDown(const Letter& l, const Number& n){//turn Facedown iff this card is up
    if((!letter.count(l)||!number.count(n))){
            throw std::out_of_range("invalid position");
        }
     
    bool face= faceup[l*_size + n]; // update corresponding variables
    help[l*_size + n] = face;
    faceup[l*_size + n] = false;

     if(_mode == "2" || _mode == "3"){ // it is for expert display mode
        if(face){

            std::cout<<"Turning face down"<<std::endl;
            updateExpertBoard(e_array,l,n);
            return true;
        }
    }
    else if(_mode == "1" || _mode=="4"){ // it is for base display mode
        if(face){
                updateBaseBoard(b_array,l,n);
                return true;
            }
    }
    return false;

}

bool Board::turnFaceUp(const Letter& l, const Number& n){ // turnFACEup iff this card is down
     if((!letter.count(l)||!number.count(n))){
        throw std::out_of_range("invalid position");
    }

     
    bool face= faceup[l*_size + n];// update corresponding variables
    help[l*_size + n] = face;
    faceup.at(l*_size + n) = true;
 
    if(_mode ==  "2"|| _mode == "3"){  // it is for expert display mode
        if(!face){
            updateExpertBoard(e_array,l,n);
            return true;
        }
    }

    else if(_mode == "1"|| _mode=="4"){// it is for base display mode
        if(!face){
            
        updateBaseBoard(b_array,l,n);
        return true;
        }
    }
    
    return false;
}                                                                                                                                                          

Card* Board::getCard(const Letter& l, const Number& n){
    if((!letter.count(l)||!number.count(n))){
        throw std::out_of_range("invalid position");
    }

    if(isBlock[l*_size+n]){ // is the card is blocked, return nullptr
        return nullptr;
    }
    turnFaceUp(l,n); // in my assumpition, if getcard is called, usually this card is being turned faceup
    
    return v_card[l*_size+n]; 
}


void Board::setCard(const Letter& l, const Number& n,Card* c){
    if((!letter.count(l)||!number.count(n))){
        throw std::out_of_range("invalid position");
    }
    /*
        preface is used to keep track of fu of the previous position
    */
    if(!preFace){           // if this card is FD, update faceup[at new position]
        preFace = isFaceUp(l,n);
        faceup[l*_size+n] = false;
        std::cout<<"This card is face down"<<std::endl;
    }
    else{                       // otherwise it's FU,update faceup
        preFace = isFaceUp(l,n);
        faceup[l*_size+n] = true;
        std::cout<<"This card is face up"<<std::endl;
    }
    v_card[l*_size+n] = c;

}


void Board::reset(){
    for(int i=0;i<faceup.size();++i){
        faceup[i] = false;
        help[i] = faceup[i];
        isBlock[i] = false;
    }
    faceup[12] = true;
    help[12] = true;
    position.clear();
    expertHelpCard.clear();
    preFace = true;
    if(_mode == "1"|| _mode=="4"){
        initializeBaseBoard(b_array);
    }
    else if(_mode == "2"|| _mode == "3"){
        initializeExpertBoard(e_array);
    }

}

ostream& operator<<(ostream& os, const Board& board){
    int check = 1;
    string b_letter[19]=  {" ","A"," "," "," ","B"," "," "," ","C"," "," "," ","D"," "," "," ","E"," "};
    string b_number[19] = {" ","1"," "," "," ","2"," "," "," ","3"," "," "," ","4"," "," "," ","5"," "};
    
    if(board._mode == "1"|| board._mode=="4"){ // its under base mode
          

        for(int i=0;i<19;++i){
            os<<b_letter[i]<<" "<<board.b_array[i]<<"\n";
        }

        os<<"\n";
        os<<"   ";
        for(int i=0;i<19;++i){
            os<<b_number[i];
        } 
    }
    else if(board._mode == "2"|| board._mode == "3"){
  
        for(int i=0;i<3;++i){
            os<<board.e_array[i]<<"\n";
        }
        os<<"\n";
        for(int i=0;i<board.position.size();++i){
            os<<board.position[i]<<"  ";
        } 

    }
    

    return os;
}


void Board::updateBaseBoard(string (&b_array)[19],const Letter& l, const Number& n){ // used to update base board display
    int helper=0;
    int buffer = 0;
    int ind = l*_size + n;
    for( int i=0;i<19;++i){ // filling board
            if(i==3 || i==7 || i==11 || i==15){
                string s = "";
                int count=19;
                while(count>0){
                    s += " ";
                    --count;
                }
                b_array[i] = s;
                
                continue;
            }
            for(int j=0;j<rows;++j){
                string arr[5];

                // First column (column = column of cards)
                if((v_card[helper+0])!=(v_card[ind])&& help[helper]){
                    // when current card is not what we'r looking for and is facing up, used for turnFaceDown()
                    arr[0] = (*v_card[helper+0])(j)+" ";
                }else if((v_card[helper+0])==(v_card[ind])&& !help[helper]){
                        // when current card is what we'r looking for and isnot facing up,used for turnFaceup()
                    arr[0] = (*v_card[helper+0])(j)+" ";
                }
                else{
                    arr[0] = "zzz ";
                }  
                //second column 
                if((v_card[helper+1])!=(v_card[ind])&& help[helper+1]){
                    arr[1] = (*v_card[helper+1])(j)+" ";
                }else if((v_card[helper+1])==(v_card[ind])&& !help[helper+1]){
                    arr[1] = (*v_card[helper+1])(j)+" ";
                }
                else{
                    arr[1] = "zzz ";
                }   

                // third column, first if --> let the middle "cards" be empty
                if((i>=8)&&(i<=10)){
                    arr[2] = "    ";
                }
                else{
                    if((v_card[helper+2])!=(v_card[ind])&& help[helper+2]){
                        arr[2] = (*v_card[helper+2])(j)+" ";
                    }else if((v_card[helper+2])==(v_card[ind])&& !help[helper+2]){
                        arr[2] = (*v_card[helper+2])(j)+" ";
                        }else{
                            arr[2] = "zzz ";
                        }   
                }
                
                // fourth column
                if((v_card[helper+3])!=(v_card[ind])&& help[helper+3]){
                    arr[3] = (*v_card[helper+3])(j)+" ";
                }else if((v_card[helper+3])==(v_card[ind])&& !help[helper+3]){
                    arr[3] = (*v_card[helper+3])(j)+" ";
                }
                else{
                    arr[3] = "zzz ";
                }   

                // fifth column 
                if((v_card[helper+4])!=(v_card[ind])&& help[helper+4]){
                    arr[4] = (*v_card[helper+4])(j)+" ";
                }else if((v_card[helper+4])==(v_card[ind])&& !help[helper+4]){
                    arr[4] = (*v_card[helper+4])(j)+" ";
                }
                else{
                    arr[4] = "zzz ";
                }   
                b_array[i] = arr[0]+arr[1]+arr[2]+arr[3]+arr[4];
               
                if(j!=rows-1)
                    ++i;
                helper = buffer;
                
            }
            help[helper] = faceup[helper];
            help[helper+1] = faceup[helper+1];
            help[helper+2] = faceup[helper+2];
            help[helper+3] = faceup[helper+3];
            help[helper+4] = faceup[helper+4];

            helper+=_size;
            buffer = helper;     
    }
}

void Board::initializeBaseBoard(string (&b_array)[19]){
    int buffer = 0;
    int helper = 0;
    
    for( int i=0;i<19;++i){ // filling board
            if(i==3 || i==7 || i==11 || i==15){
                string s = "";
                int count=19;
                while(count>0){
                    s += " ";
                    --count;
                }
                 
                b_array[i] = s;
                continue;
            }
             
            for(int j=0;j<rows;++j){
                 
                string arr[5];
                arr[0] = "zzz ";
                arr[1] = "zzz ";
                if((i>=8)&&(i<=10)){
                    arr[2] = "    ";
                }else{
                    arr[2] = "zzz ";
                }
                arr[3] = "zzz ";
                arr[4] = "zzz "; 
                b_array[i] = arr[0]+arr[1]+arr[2]+arr[3]+arr[4];  
                if(j!=rows-1)
                    ++i;
                helper = buffer;
                
            }
            helper+=_size;
            buffer = helper; 
    }

}
void Board::initializeExpertBoard(string (&e_array)[3]){

    for(int i=0;i<3;++i){
        e_array[i] = "";
    }
}

void Board::updateExpertBoard(string (&e_array)[3],const Letter& l, const Number& n){// used to update expert board display
    int ind = l*_size + n;
    string p = letter.find(l)->second + number.find(n)->second;
    string row1 = "";
    string row2 = "";
    string row3 = "";
    if(faceup[ind]){ // turning card face up
    expertHelpCard.push_back(v_card[ind]);
 
        for(int i=0;i<3;++i){
            e_array[i] = e_array[i] + (*v_card[ind])(i) + " ";
        }
        position.push_back(p);
    }
    else if(!faceup[ind]){ // turning card face down
        for(int i=0;i<expertHelpCard.size();++i){
            if(expertHelpCard[i] == v_card[ind]){
                expertHelpCard.erase(expertHelpCard.begin()+i);
            }
        }
        for(int i=0;i<expertHelpCard.size();++i){
            row1 = row1 + (*expertHelpCard[i])(0)+" ";
            row2 = row2 + (*expertHelpCard[i])(1)+" ";
            row3 = row3 + (*expertHelpCard[i])(2)+" ";
        }
        e_array[0] = row1;
        e_array[1] = row2;
        e_array[2] = row3;
        std::vector<string>::iterator p_it = std::find(position.begin(), position.end(), p);
        int p_index = std::distance(position.begin(), p_it);
        position.erase(position.begin()+p_index);
    }
}

void Board::buildLetter(std::map<Board::Letter,string> &l){
    l.insert(std::pair<Board::Letter,string>(Board::Letter::A,"A"));
    l.insert(std::pair<Board::Letter,string>(Board::Letter::B,"B"));
    l.insert(std::pair<Board::Letter,string>(Board::Letter::C,"C"));
    l.insert(std::pair<Board::Letter,string>(Board::Letter::D,"D"));
    l.insert(std::pair<Board::Letter,string>(Board::Letter::E,"E"));
}
void Board::buildNumber(std::map<Board::Number,string> &n){
    n.insert(std::pair<Board::Number,string>(Board::Number::Number1,"1"));
    n.insert(std::pair<Board::Number,string>(Board::Number::Number2,"2"));
    n.insert(std::pair<Board::Number,string>(Board::Number::Number3,"3"));
    n.insert(std::pair<Board::Number,string>(Board::Number::Number4,"4"));
    n.insert(std::pair<Board::Number,string>(Board::Number::Number5,"5"));
}



//Testing Driver


#ifdef BOARD_DEBUG
#include <cassert>
#include <iostream>

/* The following public methods are tested

 
 
 */
 
int main(){ // used to tset all public funcs
    
    Board b;
    
    //const Letter aLetter = A;
    //const Number aNumber = Number1;
    
    //all cards start face down, therefor should return false
    assert(b.isFaceUp(Board::Letter::A, Board::Number::Number1) == false );
    std::cout<<"pass first assert"<<std::endl;
    
    //turning card face up, then verifying that it is face up
    b.turnFaceUp(Board::Letter::A, Board::Number::Number1); //turn card face up
    assert(b.isFaceUp(Board::Letter::A, Board::Number::Number1) == true); //verify that it is face up
    std::cout<<"pass second assert"<<std::endl;
    
    //turning card face down again, then verifying it is face down
    b.turnFaceDown(Board::Letter::A, Board::Number::Number1);//turn card face down
    assert(b.isFaceUp(Board::Letter::A, Board::Number::Number1) == false); //verifying the card is now face down
    std::cout << "pass third assert" << std::endl;
    
    Card *c = b.getCard(Board::Letter::A, Board::Number::Number1);
    
    b.setCard(Board::Letter::B, Board::Number::Number2, b.getCard(Board::Letter::A, Board::Number::Number1));//setting card B2 to the card @ A1
    assert(c == b.getCard(Board::Letter::B, Board::Number::Number2) );//verifying that the cards should be ==
    std::cout<<"pass final assert"<<std::endl;
    
    
}


#endif
