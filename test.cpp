
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cmath>
#define WIDTH 3
#define HEIGHT 3
#define d_WIDTH 3
#define d_HEIGHT 3


using std::cin;
using std::cout;
using std::endl;

using std::string;

using std::rand;
using std::srand;

using std::ostream;
using std::vector;
// What is printed by the program if the user enters 2 and 3?
// Improve the following code by using std::vector instead of a low-level array.
// In particular define a function
// std::vector<int> matrixV( int nRows, int nCols ) and call it properly from main.
// Can you use std::array instead of std::vector? Explain why in one sentence.

class Card{
        //friend ostream& operator<<( ostream&, const Card& );
        public:
        
        string animal,bg;
        enum FaceAnimal 
            {CRAB,PENGUIN,OCTOPUS
                }FA;
        enum FaceBackGround 
            { RED,GREEN,PURPLE
                }FB;
      
        bool faceup = false;

        string card[HEIGHT][WIDTH];

        //Card(FaceAnimal, FaceBackGround);
        bool flip();
        Card( const Card& ); // non construction-copyable
        Card& operator=( const Card& ); // non copyable
        string operator() (int);
   
        Card(FaceAnimal, FaceBackGround);
        Card() = default;
        void setFace(bool);// used to set facedown/up
        bool getFace();// used to get status of face
        void print();
       // Card* getNext();
  
};

bool check;

Card::Card(Card::FaceAnimal fa, Card::FaceBackGround fb): FA(fa),FB(fb){
    int i,j;
    check = false;
    switch(fa){
        case CRAB: animal = "C";break;
        case PENGUIN: animal = "P";break;
        case OCTOPUS: animal = "O";break;

    }
    switch(fb){
        case RED: bg = "r";break;
        case GREEN: bg = "g";break;
        case PURPLE: bg = "p";break;

    }
    if(!(this->faceup)){
        for(i=0;i<HEIGHT;++i){ // initialize card zzzzz
            for(j=0;j<WIDTH;++j){
                card[i][j] = "z";
            } 
        }
    }


}
string Card::operator() (int row){
    int column = 0;
    return (card[row][column++] + card[row][column++]+card[row][column++]);
}
void Card::setFace(bool face){
    this->faceup = face;
   flip();
        
}

bool Card::getFace(){
    return this->faceup;
}

bool Card::flip(){
    cout<< "Now flipping card"<<endl;;
    int i,j;
    cout<<animal<<endl;
    cout<<bg<<endl;
    if(faceup){
        for(i=0;i<HEIGHT;++i){ // set card with color and animal
            for(j=0;j<WIDTH;++j){
                if(j==1 && i==1)
                    card[i][j] = animal;
                else
                    card[i][j] = bg;
            } 
        }
    }
    /**
    else{
        for(i=0;i<HEIGHT;++i){ // initialize card zzzzz
            for(j=0;j<WIDTH;++j){
                card[i][j] = "z";
            } 
        }
    }
    **/
    return true;
}

void Card::print(){ // print the card
    
    for(int row=0; row<HEIGHT;++row){
        int column = 0;
        string rowString = (*this)(row);
        cout<<rowString<<endl;
    }
}


class Reward{
  public:
    int ruby;
    //friend RewardDeck;
    friend ostream& operator<<( ostream&, const Reward& ); 
    Reward();
    //public:
    Reward( const Reward& ); // non construction-copyable
    Reward& operator=( const Reward& ); // non copyable
        

};
Reward::Reward(){
    srand((unsigned)time(0));
    int range = (4-1)+1;
    this->ruby = 1 + int(range*(rand()/(RAND_MAX + 1.0))); 
}

ostream& operator<<( ostream& os, const Reward& r){
    os<<r.ruby;
    return os;
}

class Reward;

class Player{
  public:
    enum Side{
        top, 
        bottom, 
        left, 
        right
    }side;

    friend ostream& operator<<( ostream&, const Player& ); 
    bool active = false;
    string _name;
    int ruby;


    

        Player(string name, Side side, int ruby);
        string getName();
        void setAcive(bool);
        bool isActive();
        int getNRubies();
        void addReward(const Reward&);
        void setDisplayMode(bool endOfGame);
        Side getSide();
        void setSide(Side side);

 
};
string position;
string sleep;
void setAcive(bool status);
Player::Player(string name, Player::Side s, int r):_name(name),side(s),ruby(r){
    switch(s){
        case top: position = "top";break;
        case bottom: position = "bottom";break;
        case left: position = "left";break;
        case right: position = "right";break;
    }
    setAcive(true);
}

string Player::getName(){
    return this->_name;
}

void Player::setAcive(bool status){
    this->active = status;
    this->active?sleep="active":sleep="inactive";
}

bool Player::isActive(){
   
    return this->active;
}
int Player::getNRubies(){
    return this->ruby;
}

/// TO BE COMPLETED
void Player::addReward(const Reward& c_Reward){
    this->ruby += c_Reward.ruby;
}

// TO BE COMPLETED
void Player::setDisplayMode(bool end){

}


//TO BE CHECKED
ostream& operator<<(ostream& os, const Player& player){
    os<<player._name <<": " << position<<" ("<<sleep<<")"<<"\n"
    <<"Once endOfGame is true: "<<"\n"<<player._name<<": "<<player.ruby<<" rubies"<<"\n";
    string a[3] = {"A","B","C"};
    string b[3] = {"1","2","3"};
    for(int i=0;i<3;++i){
        os<<a[i];
    }
    os<<"\n";
    for(int i=0;i<3;++i){
        os<<b[i];
    }

    return os;
}

Player::Side Player::getSide(){
    return this->side;
}

void Player::setSide(Player::Side s){
    this->side = s;
}
int main() {
  /*
  int nRows, nCols;
  string a[3][3] = {{"0","0","0"},{"1","1","1"},{"2","2","2"}};
  for(int row=0; row<3;++row){
        int column = 0;
        string rowString = a[row][column++] + a[row][column++]+a[row][column++];
        cout<<rowString<<endl;
    }
  bool active = true;
  string sleep;
  active?sleep="active":sleep="inactive";

  cout<<sleep<<endl;
*/
/*
  string q;
  Player p("Tom",Player::top,0);
  cout<<p.getName()<<endl;
  Reward r;
  p.addReward(r);
  cout<<p.getNRubies()<<endl;
  cout<<p<<endl;
  p.setAcive(false);
  cout<<p<<endl;
 */ 

  cout<<"----------------------"<<endl;
  
    Card::FaceAnimal fa[3];
    Card::FaceBackGround fb[3];
  for(int a = Card::CRAB;a<=Card::OCTOPUS;++a){
        fa[a] = static_cast<Card::FaceAnimal>(a);
    }
    for(int b = Card::RED;b<=Card::PURPLE;++b){
        fb[b] = static_cast<Card::FaceBackGround>(b);
    }
    vector<Card*> storage;
     int i,j;
    for(i=0;i<d_HEIGHT;++i){
        for(j=0;j<d_WIDTH;++j){
            storage.push_back(new Card(fa[i],fb[j])); // building 25 cards 
            //card[i][j]->print();
            
        }
    }

    cout<<"----------------------"<<endl;
    /**
    for(i=0;i<d_HEIGHT;++i){
        for(j=0;j<d_WIDTH;++j){
            Card* ptr = storage[0];
            storage.erase(storage.begin());
            ptr->setFace(true);
            ptr->print();
            cout<<"!!!!!!!!!!!!!!!!!"<<endl;
            cout<<storage.size()<<endl;
            cout<<"!!!!!!!!!!!!!!!!!"<<endl;
            if(storage.empty())
                cout<<"$$$$$$$$$$$$$$"<<endl;
        }
    }
    **/
    //storage[0]->print();
    //storage[0]->setFace(true);
    //storage[0]->print();

    for(int i=0;i<storage.size();++i){
        storage[i]->setFace(true);
    }
   // storage[0]->setFace(false);
    cout<<(*storage[0])(0)<<endl;
    cout<<(*storage[0])(1)<<endl;
    cout<<(*storage[0])(2)<<endl;
    cout<<storage.size()<<endl;
    string b_array[11];
    //int index = 0;
   // int helper = 0;
    int check = storage.size();
    int h = sqrt(check);
    int q = 0;

    for( i=0;i<11;++i){ // filling board
     int helper=0;
    int buffer = 0;
    //int ind = l*_size + n;
  //  for( int i=0;i<11;++i){ // filling board
            if(i%3==0&&i!=0){
                string s = "";
                int count=11;
                while(count>0){
                    s += " ";
                    --count;
                }
                b_array[i] = s;
                
                continue;
            }
            for(int j=0;j<3;++j){
                string arr[5];
                //if((storage[helper+0])!=(storage[ind])&& storage[helper+0]->getFace()){
                    // when current card is not what we'r looking for and is facing up, used for turnFaceDown()
                    arr[0] = (*storage[helper+0])(j)+" ";
               // }else if((storage[helper+0])==(storage[ind])&& !storage[helper+0]->getFace()){
                        // when current card is what we'r looking for and is facing up,used for turnFaceup()
                   // arr[0] = (*storage[helper+0])(j)+" ";
              //  }
                //else{
                  //  arr[0] = "zzz ";
               // }  
              //  if((storage[helper+1])!=(storage[ind])&& storage[helper+1]->getFace()){
                  if((i>=4)&&(i<=6)){
                      arr[1] = "    ";
                   
                  }
                  else{
                       arr[1] = (*storage[helper+1])(j)+" ";
                  }
                    
               // }else if((storage[helper+1])==(storage[ind])&& !storage[helper+1]->getFace()){
                //    arr[1] = (*storage[helper+1])(j)+" ";
               // }
               // else{
               //     arr[1] = "zzz ";
               // }   
              //  if((storage[helper+2])!=(storage[ind])&& storage[helper+2]->getFace()){
                    arr[2] = (*storage[helper+2])(j)+" ";
             //   }else if((storage[helper+2])==(storage[ind])&& !storage[helper+2]->getFace()){
//
               //     arr[2] = (*storage[helper+2])(j)+" ";
              //  }
              //  else{
              //      arr[2] = "zzz ";
               // }   
               //
                b_array[i] = arr[0]+arr[1]+arr[2]+arr[3]+arr[4];
               
                ++i;
                helper = buffer;
                
            }
            helper+=h;
            buffer = helper;     
        }

    
    for( i=0;i<11;++i){
         cout<<b_array[i]<<endl;}
    //int i,j;
    /**
    for( i=0;i<11;++i){ // filling board
    cout<<i<<"!!!!!!"<<endl;
            if(i%3==0&&i!=0){
                string s = "";
                int count=11;
                while(count>0){
                    s += " ";
                    --count;
                }
                b_array[i] = s;
                
                continue;
            }
            for(j=0;j<3;++j){
                cout<<j<<"@@@@@"<<endl;
                int w =0;
                //cout<<(*storage[helper+(w++)])(j)<<endl;
                string arr[3];
                if((storage[helper+0])!=(storage[q])&& storage[helper+0]->getFace()){
                    arr[0] = (*storage[helper+0])(j)+" ";
                }else{
                    arr[0] = "zzz ";
                }   
                arr[1]  = (*storage[helper+1])(j)+" ";
                arr[2]  = (*storage[helper+2])(j);
                b_array[i] = arr[0]+arr[1]+arr[2] ;
                cout<<b_array[i]<<"  ))))))"<<endl;
                ++i;
                helper = index;
                cout<<helper<<"******"<<endl;
            }
            helper+=h;
            index = helper;
           
        
    }
**/
   // card[1][1]->print();
   // card[1][1]->setFace(true);
   // card[1][1]->print();
     //cout<<"----------------------"<<endl;
  //   for( i=0;i<11;++i){
   //      cout<<b_array[i]<<endl;
   //  }
//
   //  cout<<"-----------------------"<<endl;

    
    //turn face down (letter, number):
       // int q = letter * h + number;
       /**
        for(i=0;i<11;++i){
            if(i%3==0&&i!=0){
                string s = "";
                int count=11;
                while(count>0){
                    s += " ";
                    --count;
                }
                b_array[i] = s;
                continue;
            }
           for(j=0;j<3;++j){
                string arr[3];
//                                                      isFaceUp(letter,number)
                if((storage[helper+0])!=(storage[q])&& storage[helper+0]->getFace()){
                    arr[0] = (*storage[helper+0])(j)+" ";
                }else{
                    arr[0] = "zzz";
                }   
                
                arr[1]  = (*storage[helper+1])(j)+" ";
                arr[2]  = (*storage[helper+2])(j);
                b_array[i] = arr[0]+arr[1]+arr[2] ;
                cout<<b_array[i]<<"  ))))))"<<endl;
                ++i;
                helper = index;
            }
            helper+=h;
            index = helper;
           

        }

         
     }
     **/
  return 0;
}




