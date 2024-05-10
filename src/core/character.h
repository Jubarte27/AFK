#ifndef CHARACTER_H
#define CHARACTER_H

#include <map>
#include <vector>

using namespace std;

class BasicStats
{
private:
    int health;
    int mana;
    int strength;
    int dexterity;
    int intelligence;
    int wisdom;
    int charisma;
    int luck;
};

enum struct DamageType
{
    PHYSICAL,
    MAGICAL,
    OVER_TIME,
    TRUE,
};

enum struct SubDamageType
{
    /*Physical*/
    CUTTING,
    PIERCING,
    BLUNT,

    /*Elemental Magic*/
    FIRE,
    ICE,
    LIGHTNING,
    EARTH,
    WIND,
    WATER,

    /*Magic*/
    LIGHT,
    DARK,
    ARCANE,

    /*Over time*/
    POISON,
    BURN,
    FREEZE,
    BLEED,
    SHOCK,

};

class DamageStats
{
private:
    int damage;
    int defense;
    int resistance;
};

class CombatStats
{
private:
    int criticalChance;
    int criticalDamage;

    map<DamageType, DamageStats> damageStats;
    map<SubDamageType, DamageStats> subDamageStats;
};

class Stats
{
    BasicStats basic_stats;
    CombatStats combat_stats;
    int current_health;
    int current_mana;
    vector<Modifier> modifiers;
};

class Modifier
{
private:
    Stats apply(Stats stats) ;
    Stats remove(Stats stats);
};

class Character
{
private:
    BasicStats basicStats;
    CombatStats combatStats;
};

#endif // CHARACTER_H
