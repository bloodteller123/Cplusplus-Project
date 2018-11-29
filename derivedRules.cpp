#include "derivedRules.h"
#include "card.h"
#include "rules.h"
#include "derivedGame.h"

#include <vector>

using std::vector;
using std::cout;
using std::endl;


DerivedRules::DerivedRules(vector<Player>& v):Rules(v){}


string DerivedRules::triggerAbility(const DerivedGame& game,int& ind){
    Card::FaceAnimal fa = (*game.getCurrentCard())(true);
    switch(fa){
        case  Card::CRAB: {
            Rules::crab();
            return "CRAB";
            break;
            }
        case  Card::PENGUIN: {
            Rules::penguin();
            return "PENGUIN";
            break;}

        case  Card::OCTOPUS: {
            Rules::octopus();
            return "OCTOPUS";
            break;
            }
        case  Card::TURTLE: {
            Rules::turtle(ind);
            return "TURTLE";
            break;
            }
        case  Card::WALRUS: {
            Rules::walrus();
            return "WALRUS";
            break;
            }
    }

}

