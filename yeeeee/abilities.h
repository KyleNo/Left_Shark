#ifndef ABILITIES_H_INCLUDED
#define ABILITIES_H_INCLUDED
#include <string>
struct hero;
class ability{
public:
     string abilityName;
     bool isAttack;
     bool isHeal;
     bool isBuff;
     int abilityPotency;
     float abilityModifier;
     int range;
     int radius;
     int forTurns;
     int statAffected;
};
class heroClass{
public:
    ability jobAbility;
};
class weapon{
public:
    int attackPower;
    int magicPower;
    int rangeBonus;
};
void abilityDeclare(){
    ability testAbility;
    testAbility.isAttack = true;
    testAbility.abilityPotency = 50;
    testAbility.range = 1000;
    testAbility.abilityModifier = 1;
}

#endif // ABILITIES_H_INCLUDED
