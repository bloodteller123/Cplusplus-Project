/*
    //  Copyright © 2018 Zihan Chen. All rights reserved.
*/

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
   
   // cd.shuffles();

    //RewardDeck &rd = RewardDeck::make_RewardDeck();

Board::Board(){
    
    //while(v_card.size()!=24){
    if(cd.isEmpty()){
        throw NoMoreCards();
    }

    while(!cd.isEmpty()){
    
        v_card.push_back(cd.getNext());
        faceup.push_back(false);
        help.push_back(false);
        isBlock.push_back(false);
    }
    

    //while(!rd.isEmpty()){
      //  v_reward.push_back(rd.getNext());
    //}

    size = v_card.size(); // 
    _size = sqrt(size);
    rows = (*v_card[0]).getNRows();
    faceup[12] = true;
    help[12] = true;
     

    initializeBaseBoard(b_array);
    initializeExpertBoard(e_array);
    buildLetter(letter);
    buildNumber(number);
    

       
    /*
        TO BE COMPLETED--- throw exception
    */
}

/*
    TO BE COMPLETED --- throw exception
*/

bool Board::isFaceUp(const Letter& l, const Number& n) const{
    // int q = letter + number
    // v_card[q];
    return faceup[l*_size + n]; 
    
}

bool Board::turnFaceDown(const Letter& l, const Number& n){//turn Facedown iff this card is up
     
    bool face= faceup[l*_size + n];
    help[l*_size + n] = face;
    faceup[l*_size + n] = false;

     if(_mode == "E" || _mode == "e"){
        if(face){
            std::cout<<isFaceUp(l,n)<<"!!!!!"<<std::endl;
            std::cout<<faceup[l*_size+n]<<std::endl;
            std::cout<<l*_size+n<<std::endl;
            std::cout<<"Turning face down"<<std::endl;
            updateExpertBoard(e_array,l,n);
            return true;
        }
    }
    else if(_mode == "B" || _mode == "b"){
        if(face){
                updateBaseBoard(b_array,l,n);
                return true;
            }
    }
    return false;

}

bool Board::turnFaceUp(const Letter& l, const Number& n){ // turnFACEup iff this card is down
     
    bool face= faceup[l*_size + n];
    help[l*_size + n] = face;
    faceup.at(l*_size + n) = true;
 
    if(_mode == "E" || _mode == "e"){
        if(!face){
            updateExpertBoard(e_array,l,n);
            return true;
        }
    }

    else if(_mode == "B" || _mode == "b"){
        if(!face){
 
        updateBaseBoard(b_array,l,n);
        return true;
        }
    }
    
    
    return false;
}                                                                                                                                                          

Card* Board::getCard(const Letter& l, const Number& n){
    if(isBlock[l*_size+n]){
        return nullptr;
    }
    turnFaceUp(l,n);
    
    return v_card[l*_size+n]; 
}


void Board::setCard(const Letter& l, const Number& n,Card* c){

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
    if(_mode == "B" || _mode == "b"){
        initializeBaseBoard(b_array);
    }
    else if(_mode == "E" || _mode == "e"){
        initializeExpertBoard(e_array);
    }

}

ostream& operator<<(ostream& os, const Board& board){
    int check = 1;
    string b_letter[19]=  {" ","A"," "," "," ","B"," "," "," ","C"," "," "," ","D"," "," "," ","E"," "};
    string b_number[19] = {" ","1"," "," "," ","2"," "," "," ","3"," "," "," ","4"," "," "," ","5"," "};
    
    if(board._mode == "B" || board._mode =="b"){ // its under base mode
          

        for(int i=0;i<19;++i){
            os<<b_letter[i]<<" "<<board.b_array[i]<<"\n";
        }

        os<<"\n";
        os<<"   ";
        for(int i=0;i<19;++i){
            os<<b_number[i];
        } 
    }
    else if(board._mode == "E" || board._mode == "e"){
  
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
/*

void Board::setMode(string s){
    mode = s;
}

*/

void Board::updateBaseBoard(string (&b_array)[19],const Letter& l, const Number& n){
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
                   // help[helper+1] = faceup[helper+1];
                }else if((v_card[helper+1])==(v_card[ind])&& !help[helper+1]){
                    arr[1] = (*v_card[helper+1])(j)+" ";
                   // help[helper+1] = faceup[helper+1];
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
                        //help[helper+2] = faceup[helper+2];
                    }else if((v_card[helper+2])==(v_card[ind])&& !help[helper+2]){
                        arr[2] = (*v_card[helper+2])(j)+" ";
                       // help[helper+2] = faceup[helper+2];
                        }else{
                            arr[2] = "zzz ";
                        }   
                }
                
                // fourth column
                if((v_card[helper+3])!=(v_card[ind])&& help[helper+3]){
                    arr[3] = (*v_card[helper+3])(j)+" ";
                   // help[helper+3] = faceup[helper+3];
                }else if((v_card[helper+3])==(v_card[ind])&& !help[helper+3]){
                    arr[3] = (*v_card[helper+3])(j)+" ";
                   // help[helper+3] = faceup[helper+3];
                }
                else{
                    arr[3] = "zzz ";
                }   

                // fifth column 
                if((v_card[helper+4])!=(v_card[ind])&& help[helper+4]){
                    arr[4] = (*v_card[helper+4])(j)+" ";
                   // help[helper+4] = faceup[helper+4];
                }else if((v_card[helper+4])==(v_card[ind])&& !help[helper+4]){
                    arr[4] = (*v_card[helper+4])(j)+" ";
                   // help[helper+4] = faceup[helper+4];
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

void Board::updateExpertBoard(string (&e_array)[3],const Letter& l, const Number& n){
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


/**
vector<string>& Board::getNeighbour(const Letter& l,const Number& n){
    string s;
    neighbours.clear();
    int ind = l*_size + n;
    if((ind-_size)>=0){ // upper row
        s = letter.find(static_cast<Letter>(static_cast<int>(l)-1))->second + number.find(static_cast<Number>(n))->second;
        neighbours.push_back(s);
    }
    if((ind+_size)<=(size-1)){// lower row
        s = letter.find(static_cast<Letter>(static_cast<int>(l)+1))->second + number.find(static_cast<Number>(n))->second;
        neighbours.push_back(s);
    }
    if((ind + 1) >0 && (ind%_size)<4){
        s = letter.find(static_cast<Letter>(l))->second + number.find(static_cast<Number>(static_cast<int>(n)+1))->second;
        neighbours.push_back(s);

    }
    if((ind-1)>=0 && (ind%_size)!=0){
        s = letter.find(static_cast<Letter>(static_cast<int>(l)))->second + number.find(static_cast<Number>(static_cast<int>(n)-1))->second;
        neighbours.push_back(s);

    }
    return neighbours;
}


void Board::setBlock(bool isBlocked,const Letter& l,const Number& n){
    int ind = l*_size+n;
    isBlock[ind] = isBlocked;
}

int Board::getNFUCard(){
    int num = 0;
    for(int i=0;i<faceup.size();++i){
        if(faceup[i]== true){
            num++;
        }
    }
    return num;
}


void Board::updatePosition(const Letter& l1,const Number& n1,const Letter& l2,const Number& n2){// l2,n2 is chosen card(was octopus)
    string p_op = letter.find(l1)->second + number.find(n1)->second;
    string p_ex = letter.find(l2)->second + number.find(n2)->second;
    for(int i=0;i<position.size();++i){
        if(position[i] == p_ex && !isFaceUp(l2,n2)){
            position.erase(position.begin()+i);
        }
    }
    position.push_back(p_op);
}
**/
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