/*
    //  Copyright © 2018 Zihan Chen. All rights reserved.
*/
#include "reward.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

using std::rand;
using std::srand;
using std::ostream;

Reward::Reward(int r):ruby(r){
    /*
    srand((unsigned)time(0));
    int range = (4-1)+1;
    this->ruby = 1 + int(range*(rand()/(RAND_MAX + 1.0))); 
    */
}

ostream& operator<<( ostream& os, const Reward& r){
    os<<r.ruby;
    return os;
}
Reward::operator int() const{
    return ruby;
}



