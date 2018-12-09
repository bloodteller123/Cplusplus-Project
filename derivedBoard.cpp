#include "board.h"
#include "derivedBoard.h"

#include <string>
#include <vector>


using std::string;
using std::vector;

DerivedBoard::DerivedBoard():Board(){}

void DerivedBoard::setMode(string m){
    _mode = m;
}

vector<string>& DerivedBoard::getNeighbour(const Letter& l,const Number& n){ // get neighbour for a certain card
    string s;
    _neighbours.clear();
    int ind = l*_size + n;
    if((ind-_size)>=0){ // upper row
        s = letter.find(static_cast<Letter>(static_cast<int>(l)-1))->second + number.find(static_cast<Number>(n))->second;
        _neighbours.push_back(s);
    }
    if((ind+_size)<=(size-1)){// lower row
        s = letter.find(static_cast<Letter>(static_cast<int>(l)+1))->second + number.find(static_cast<Number>(n))->second;
        _neighbours.push_back(s);
    }
    if((ind + 1) >0 && (ind%_size)<4){
        s = letter.find(static_cast<Letter>(l))->second + number.find(static_cast<Number>(static_cast<int>(n)+1))->second;
        _neighbours.push_back(s);

    }
    if((ind-1)>=0 && (ind%_size)!=0){
        s = letter.find(static_cast<Letter>(static_cast<int>(l)))->second + number.find(static_cast<Number>(static_cast<int>(n)-1))->second;
        _neighbours.push_back(s);

    }
    return _neighbours;
}

void DerivedBoard::setBlock(bool isBlocked,const Letter& l,const Number& n){ // set the card to be blocked or not
    int ind = l*_size+n;
    isBlock[ind] = isBlocked;
}

int DerivedBoard::getNFUCard(){ // return the number of FaceUp cards on the board
    int num = 0;
    for(int i=0;i<faceup.size();++i){
        if(faceup[i]== true){
            num++;
        }
    }
    return num;
}

void DerivedBoard::updatePosition(const Letter& l1,const Number& n1,const Letter& l2,const Number& n2){ // used for expert display(RUles) mode
    string p_op = letter.find(l1)->second + number.find(n1)->second;
    string p_ex = letter.find(l2)->second + number.find(n2)->second;
    for(int i=0;i<position.size();++i){
        if(position[i] == p_op && !isFaceUp(l2,n2)){
            position.erase(position.begin()+i);
            position.push_back(p_op);
        }
        else if(position[i] == p_op && isFaceUp(l2,n2)){
            position[i] = p_ex;
        }
        if(position[i] == p_ex){  // for sure, it;s the last position
            position[i] = p_op;
            return;
        }
    }
    
}