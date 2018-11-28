#ifndef CARDDECK
#define CARDDECK
/*
    //  Copyright © 2018 Zihan Chen. All rights reserved.
*/

#define d_WIDTH 5
#define d_HEIGHT 5
#include "deck_C.h"
#include "card.h"
#include <vector>

using std::vector;
class Card;


class CardDeck: public Deck_C<Card>{
    
    //Card* card[d_HEIGHT][d_WIDTH]; // card array holds 25 cards.

    /*
    one card should be removed ....
    */
    CardDeck( const CardDeck& ); // non construction-copyable
    CardDeck& operator=( const CardDeck& ); // non copyable

    static CardDeck s_CardDeck;
    //vector<Card*> cardStorage;

    protected:
        CardDeck() = default;
        void shuffles() override;
       // Card* getNext();
       // bool isEmpty() const;
        // enum to array 
        static void buildCard(Card::FaceAnimal (&fa)[5], Card::FaceBackGround (&fb)[5]);
        
        ~CardDeck();

    public:
        static CardDeck& make_CardDeck();
};


#endif