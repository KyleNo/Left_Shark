#ifndef ABILITIES_H_INCLUDED
#define ABILITIES_H_INCLUDED
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
     void useAbility(hero user, hero target);
     void abilityHeal(hero user, hero target);
     void abilityAttack(hero user, hero target);
     void abilityBuff(hero user, hero target);
};
class heroClass{
public:
    vector<ability> jobAbilities;
};

heroClass ninja;
ability throwingKnife;
//throwingKnife.range = 5;

#endif // ABILITIES_H_INCLUDED
