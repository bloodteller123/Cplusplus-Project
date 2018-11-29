#ifndef DERIVEDBOARD
#define DERIVEDBOARD

#include "board.h"

class DerivedBoard: public Board{


    public:
        DerivedBoard();
        void setMode(string);
        vector<string>& getNeighbour(const Letter&,const Number&);
        void setBlock(bool,const Letter&,const Number&);
        int getNFUCard();
        void updatePosition(const Letter&  ,const Number&  ,const Letter&  ,const Number& );




};







#endif