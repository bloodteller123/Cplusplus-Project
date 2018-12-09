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

}

ostream& operator<<( ostream& os, const Reward& r){
    os<<r.ruby;
    return os;
}
Reward::operator int() const{
    return ruby;
}



