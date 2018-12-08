//#define CARD_DEBUG
#ifndef CARD
#define CARD
/*
    //  Copyright © 2018 Zihan Chen. All rights reserved.
*/
#define WIDTH 3
#define HEIGHT 3

//#include "cardDeck.h"
#include <string>
#include <vector>
using std::string;
using std::vector;

using std::ostream; // it have to be put in header file otherwise ostream cann;t access private member


class CardDeck;
 
class Card{
    public:
        enum FaceAnimal 
            {
                CRAB, 
                PENGUIN, 
                OCTOPUS, 
                TURTLE, 
                WALRUS
                }FA;
        
    private:
        string animal,bg;
        friend class CardDeck;
        //friend ostream& operator<<( ostream&, const Card& );
        

        enum FaceBackGround 
            {
                RED, 
                GREEN, 
                PURPLE, 
                BLUE, 
                YELLOW
                }FB;
        

        bool missing = false;

        string card[HEIGHT][WIDTH];

        Card(FaceAnimal, FaceBackGround);
        bool flip();
        Card( const Card& ); // non construction-copyable
        Card& operator=( const Card& ); // non copyable
        //Card(string);
        vector<string> cardType; 

    public:

        Card() = default;
      // void setFace(bool);// used to set facedown/up
        //bool getFace();// used to get status of face
 
        int getNRows();
        string operator() (int);
        //operator vector<string> (); // The public interface of Card is to include conversion operators to type FaceAnimal and FaceBackground.
        FaceAnimal operator() (bool) const{return FA;};
        operator FaceBackGround () const{return FB;} ;
        
};



#endif
