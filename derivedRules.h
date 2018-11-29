#ifndef DERIVEDRULES
#define DERIVEDRULES


#include "rules.h"
#include "player.h"
#include "derivedGame.h"

#include <vector>

using std::vector;
class Player;
class DerivedGame;

class DerivedRules:public Rules{


    public:
        DerivedRules(vector<Player>&);
        string triggerAbility(const DerivedGame&,int& ind);


};





#endif