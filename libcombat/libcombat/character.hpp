#ifndef CHARACTER_H
#define CHARACTER_H

#include <map>
#include <vector>
#include <string>

namespace character
{
    using namespace std;

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

    struct BasicStats
    {
        int health;
        int mana;
        int strength;
        int constitution;
        int dexterity;
        int intelligence;
        int wisdom;
        int charisma;
        int luck;
    };

    struct DamageStats
    {
        int damage;
        int defense;
        int resistance;
    };

    struct CombatStats
    {
        int critical_chance;
        int critical_damage;

        map<DamageType, DamageStats> damage_stats;
        map<SubDamageType, DamageStats> sub_damage_stats;
    };

    struct Stats
    {
        BasicStats basic_stats;
        CombatStats combat_stats;
        int current_health;
        int current_mana;
        // vector<Modifier> modifiers;

        // bool hasModifier(const Modifier &modifier) const;
    };

    // class Modifier
    // {
    // public:
    //     int id;
    //     Stats apply(Stats stats);
    //     Stats remove(Stats stats);
    // };

    struct Ability
    {
        int id;
        string name;
        string description;

        int cooldown;
        int mana_cost;
    };

    struct DamageAbility : Ability
    {
        DamageType damage_type;
        SubDamageType sub_damage_type;
        int damage;
    };

    struct CharacterDefinition
    {
        BasicStats basic_stats;
        CombatStats combat_stats;
        vector<Ability> abilities;
    };

} // namespace character

#endif // CHARACTER_H
