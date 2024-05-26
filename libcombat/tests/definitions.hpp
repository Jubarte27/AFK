#include <libcombat/combat.hpp>
#include <libcombat/character.hpp>


namespace definitions {
    using namespace std;
    using namespace combat;
    using namespace character;
    CharacterDefinition john_doe = {
        .basic_stats = {
            .health = 1 << 6,
            .mana = 1 << 6,
            .strength = 1 << 3,
            .dexterity = 1 << 3,
            .intelligence = 1 << 3,
            .wisdom = 1 << 3,
            .charisma = 1 << 3,
            .luck = 1 << 3,
        },
    };

    CharacterDefinition tank = {
        .basic_stats = {
            .health = john_doe.basic_stats.health << 2,
            .mana = john_doe.basic_stats.mana,
            .strength = john_doe.basic_stats.strength << 1,
            .dexterity = john_doe.basic_stats.dexterity >> 1,
            .intelligence = john_doe.basic_stats.intelligence,
            .wisdom = john_doe.basic_stats.wisdom,
            .charisma = john_doe.basic_stats.charisma,
            .luck = john_doe.basic_stats.luck,
        },
        .combat_stats = {
            .critical_chance = 1,
            .critical_damage = 1 << 1,
        },
    };

    CharacterDefinition mage = {
        .basic_stats = {
            .health = john_doe.basic_stats.health >> 1,
            .mana = john_doe.basic_stats.mana << 2,
            .strength = john_doe.basic_stats.strength,
            .dexterity = john_doe.basic_stats.dexterity,
            .intelligence = john_doe.basic_stats.intelligence << 1,
            .wisdom = john_doe.basic_stats.wisdom,
            .charisma = john_doe.basic_stats.charisma,
            .luck = john_doe.basic_stats.luck,
        },
        .combat_stats = john_doe.combat_stats,
    };

    CharacterDefinition rogue = {
        .basic_stats = {
            .health = john_doe.basic_stats.health,
            .mana = john_doe.basic_stats.mana,
            .strength = john_doe.basic_stats.strength,
            .dexterity = john_doe.basic_stats.dexterity << 2,
            .intelligence = john_doe.basic_stats.intelligence,
            .wisdom = john_doe.basic_stats.wisdom,
            .charisma = john_doe.basic_stats.charisma,
            .luck = john_doe.basic_stats.luck << 1,
        },
        .combat_stats = {
            .critical_chance = john_doe.combat_stats.critical_chance << 4,
            .critical_damage = john_doe.combat_stats.critical_damage << 1,
        },
    };
}