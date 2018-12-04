#ifndef DECK_C
#define DECK_C
/*
    //  Copyright © 2018 Zihan Chen. All rights reserved.
*/
#include <vector>

using std::vector;
template<class C>
class Deck_C{

    private:
       // static C* m_Instance;
       //C data;

    protected:
        //Deck_C();
       
        //C* onCreate();
        // used to store a set of card or rewards
        vector<C*> storage;

        //~Deck_C();
    public:
        Deck_C() = default;

        virtual void shuffles()=0;
        C* getNext();
        bool isEmpty() const;

};





#endif