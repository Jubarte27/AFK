#ifndef COMBAT_H
#define COMBAT_H

#include <memory>
#include <random>

#include <libcombat/character.hpp>
#include <libcombat/party.hpp>
#include <libcombat/turn_management.hpp>

namespace combat
{
    using namespace character;
    using namespace turn_management;
    using namespace party;

    enum AttackMessage
    {
        HIT,
        CRITICAL_HIT,

        ERROR_TARGET_SELF,
        ERROR_TARGET_ALLY,
        ERROR_TARGET_NOT_FOUND,
        ERROR_TARGET_DEAD,
    };

    struct AttackResult
    {
        AttackMessage message;
        int damage;
        DamageType damageType;
        SubDamageType subDamageType;
    };

    enum DamageAbilityMessage
    {
        HIT,
        CRITICAL_HIT,

        ERROR_TARGET_SELF,
        ERROR_TARGET_ALLY,
        ERROR_TARGET_NOT_FOUND,
        ERROR_TARGET_DEAD,
        ERROR_NO_MANA,
    };

    struct DamageAbilityResult
    {
        DamageAbilityMessage message;
        int damage;
        DamageType damageType;
        SubDamageType subDamageType;
    };

    struct Combatant
    {
        const PlayerId id;
        const shared_ptr<CharacterDefinition> definition;
        const shared_ptr<Party> party;
        Stats currentStats;
    };

    struct CombatParty
    {
        const shared_ptr<Party> party;
        vector<Combatant> combatants;
        vector<Combatant> summonedCombatants;
    };

    class Combat
    {
    private:
        vector<CombatParty> parties;
        TurnManager manager;
        unordered_map<PlayerId, Combatant *> active_combatants;
        PlayerId idCounter;

        minstd_rand rng;

        PlayerId next_counter();

        void damage(PlayerId target, int damage);
        void spend_mana(PlayerId target, int mana);

    public:
        Combat(const vector<shared_ptr<Party>> &parties);

        Combatant &summon(shared_ptr<CharacterDefinition> character, CombatParty *party);
        void step();

        PlayerId start_turn();
        void end_turn();

        bool finished() const;
        bool alive(PlayerId id) const;
        const vector<CombatParty> &getParties() const;
        const Combatant &getCombatant(PlayerId id) const;
        
        // Commands
        AttackResult basic_attack(PlayerId attacker, PlayerId target);
        DamageAbilityResult use_ability(PlayerId attacker, const DamageAbility &ability, PlayerId target);

    };
} // namespace combat



#endif // COMBAT_H