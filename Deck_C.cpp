/*
    //  Copyright © 2018 Zihan Chen. All rights reserved.
*/

#include "deck_C.h"
#include <iostream>

using std::cout;
using std::endl;

/**
template <class C>
Deck_C<C>::Deck_C(){}
**/
/*
template <class C>
C* Deck_C<C>::onCreate(){
    cout<< "returning new obejct"<<endl;
    return new C;
}
*/
class Card;
class Reward;

template <class C>
C* Deck_C<C>::getNext(){
    if(!isEmpty()){
        C* ptr = storage[0];
        storage.erase(storage.begin());
        return ptr;
    }   
    return nullptr;
}

template <class C>
bool Deck_C<C>::isEmpty() const{

    return (storage.empty());
}

template class Deck_C<Card>;
template class Deck_C<Reward>;
