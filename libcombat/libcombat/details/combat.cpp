#include <libcombat/combat.hpp>

#include <chrono>

namespace combat
{
    using namespace character;
    using namespace turn_management;
    using namespace party;

    static Combatant createCombatant(const shared_ptr<CharacterDefinition> &character, const shared_ptr<Party> &party, PlayerId id);
    static vector<CombatParty> createCombatParties(const vector<shared_ptr<Party>> &parties);
    static vector<PlayerId> find_players(const vector<CombatParty> &parties);
    static unordered_map<PlayerId, Combatant *> findActiveCombatants(vector<CombatParty> &parties);
    static PlayerId firstFreeId(const vector<CombatParty> &parties);

    Combat::Combat(const vector<shared_ptr<Party>> &parties) :
                                                               parties(createCombatParties(parties)),
                                                               manager(find_players(this->parties)),
                                                               active_combatants(findActiveCombatants(this->parties)),
                                                               idCounter(firstFreeId(this->parties)),
                                                               rng(std::chrono::system_clock::now().time_since_epoch().count())

    {
    }

    PlayerId Combat::next_counter()
    {
        return idCounter++;
    }

    void Combat::step()
    {
        // PlayerId player = manager.next();
        // auto combatant = active_combatants[player];
        // manager.play(player);
    }

    bool Combat::finished() const
    {
        int alive = 0;
        for (const auto &party : parties)
        {
            for (const auto &combatant : party.combatants)
            {
                if (active_combatants.contains(combatant.id))
                {
                    alive++;
                    break;
                }
            }
        }
        return alive <= 1;
    }

    Combatant &Combat::summon(shared_ptr<CharacterDefinition> character, CombatParty *party)
    {
        party->summonedCombatants.push_back(createCombatant(character, party->party, next_counter()));
        return party->summonedCombatants.back();
    }

    bool Combat::alive(PlayerId id) const {
        return active_combatants.contains(id);
    }

    const vector<CombatParty> &Combat::getParties() const {
        return parties;
    }

    const Combatant &Combat::getCombatant(PlayerId id) const
    {
        return *active_combatants.at(id);
    }
    void Combat::damage(PlayerId target, int damage)
    {
        if (!active_combatants.contains(target))
        {
            return;
        }
        Combatant *combatant = active_combatants.at(target);
        combatant->currentStats.current_health -= damage;
        if (combatant->currentStats.current_health <= 0)
        {
            active_combatants.erase(target);
            manager.deactivate(target);
        }
    }

    void Combat::spend_mana(PlayerId target, int mana) {
        if (!active_combatants.contains(target))
        {
            return;
        }
        Combatant *combatant = active_combatants.at(target);
        combatant->currentStats.current_mana -= mana;
        combatant->currentStats.current_mana = max(combatant->currentStats.current_mana, 0);
    }

    static int basic_attack_damage(const Stats &attacker, const Stats &target)
    {
        int base_atk_stat = max(attacker.basic_stats.strength, attacker.basic_stats.dexterity);
        int attack = base_atk_stat << 2;

        int base_def_stat = max(target.basic_stats.dexterity, target.basic_stats.constitution);
        int defense = base_def_stat << 1;

        return max(attack - defense, 0);
    }

    static bool critical_hit(const Combatant &attacker, const Combatant &target, std::minstd_rand rng)
    {
        int luck = attacker.currentStats.basic_stats.luck;
        int crit = attacker.currentStats.combat_stats.critical_chance * luck;
        return rng() % 100 < crit;
    }

    static AttackResult _basic_attack(const Combatant &attacker, const Combatant &target, std::minstd_rand rng)
    {
        int damage = basic_attack_damage(attacker.currentStats, target.currentStats);

        if (critical_hit(attacker, target, rng))
        {
            int crit_damage = attacker.currentStats.combat_stats.critical_damage;
            return {
                .message = AttackMessage::CRITICAL_HIT,
                .damage = crit_damage * damage,
            };
        }

        return {
            .message = AttackMessage::HIT,
            .damage = damage,
        };
    }
    
    AttackResult Combat::basic_attack(PlayerId attacker, PlayerId target) {
        if (attacker == target)
        {
            return {
                .message = AttackMessage::ERROR_TARGET_ALLY,
            };
        }
        if (!active_combatants.contains(attacker) || !active_combatants.contains(target))
        {
            return {
                .message = AttackMessage::ERROR_TARGET_NOT_FOUND
            };
        }
        Combatant &attackerCombatant = *active_combatants.at(attacker);
        Combatant &targetCombatant = *active_combatants.at(target);

        if (attackerCombatant.party == targetCombatant.party)
        {
            return {
                .message = AttackMessage::ERROR_TARGET_ALLY
            };
        }
        if (targetCombatant.currentStats.current_health <= 0)
        {
            return {
                .message = AttackMessage::ERROR_TARGET_DEAD
            };
        }
        AttackResult result = _basic_attack(attackerCombatant, targetCombatant, rng);
        this->damage(target, result.damage);
        return result;
    }

    static DamageAbilityResult _damageAbility(const Combatant &attacker, const DamageAbility &ability, const Combatant &target, std::minstd_rand rng)
    {
        int damage = ability.damage;
        if (critical_hit(attacker, target, rng))
        {
            int crit_damage = attacker.currentStats.combat_stats.critical_damage;
            damage *= crit_damage;
            return {
                .message = DamageAbilityMessage::CRITICAL_HIT,
                .damage = damage,
                .damageType = ability.damage_type,
                .subDamageType = ability.sub_damage_type,
            };
        }

        return {
            .message = DamageAbilityMessage::HIT,
            .damage = damage,
            .damageType = ability.damage_type,
            .subDamageType = ability.sub_damage_type,
        };
    } 

    DamageAbilityResult Combat::use_ability(PlayerId attacker, const DamageAbility &ability, PlayerId target)
    {
        if (attacker == target)
        {
            return {
                .message = DamageAbilityMessage::ERROR_TARGET_SELF,
            };
        }
        if (!active_combatants.contains(attacker) || !active_combatants.contains(target))
        {
            return {
                .message = DamageAbilityMessage::ERROR_TARGET_NOT_FOUND
            };
        }
        Combatant &attackerCombatant = *active_combatants.at(attacker);
        Combatant &targetCombatant = *active_combatants.at(target);

        if (attackerCombatant.party == targetCombatant.party)
        {
            return {
                .message = DamageAbilityMessage::ERROR_TARGET_ALLY
            };
        }
        if (targetCombatant.currentStats.current_health <= 0)
        {
            return {
                .message = DamageAbilityMessage::ERROR_TARGET_DEAD
            };
        }
        if (attackerCombatant.currentStats.current_mana < ability.mana_cost)
        {
            return {
                .message = DamageAbilityMessage::ERROR_NO_MANA
            };
        }
        DamageAbilityResult result = _damageAbility(attackerCombatant, ability, targetCombatant, rng);
        this->damage(target, result.damage);
        this->spend_mana(attacker, ability.mana_cost);
        return result;
    }

    PlayerId Combat::start_turn()
    {
        return manager.next();
    }

    void Combat::end_turn() {
        manager.play(manager.next());
    }

    static unordered_map<PlayerId, Combatant *> findActiveCombatants(vector<CombatParty> &parties)
    {
        unordered_map<PlayerId, Combatant *> active_combatants;
        for (auto &party : parties)
        {
            for (auto &combatant : party.combatants)
            {
                active_combatants.emplace(combatant.id, &combatant);
            }
        }
        active_combatants[0];
        return active_combatants;
    }

    static vector<PlayerId> find_players(const vector<CombatParty> &parties)
    {
        vector<PlayerId> players;
        for (const auto &party : parties)
        {
            for (const auto &combatant : party.combatants)
            {
                players.push_back(combatant.id);
            }
        }
        return players;
    }

    static PlayerId firstFreeId(const vector<CombatParty> &parties) {
        PlayerId biggestUsedId = -1;
        for (const auto &party : parties)
        {
            for (const auto &combatant : party.combatants)
            {
                biggestUsedId = max(biggestUsedId, combatant.id);
            }
        }
        return biggestUsedId + 1;
    }

    static vector<CombatParty> createCombatParties(const vector<shared_ptr<Party>> &parties)
    {
        vector<CombatParty> combatParties;
        PlayerId id = 0;
        for (const auto &party : parties)
        {
            vector<Combatant> combatants;
            for (const auto &character : party->members)
            {
                combatants.push_back(createCombatant(character, party, id++));
            }
            combatParties.push_back({party, combatants, {}});
        }
        return combatParties;
    }

    static Stats initialStats(const shared_ptr<CharacterDefinition> &character)
    {
        return {
            .basic_stats = character->basic_stats,
            .combat_stats = character->combat_stats,
            .current_health = character->basic_stats.health,
            .current_mana = character->basic_stats.mana,
            // .modifiers = {},
        };
    }

    static Combatant createCombatant(const shared_ptr<CharacterDefinition> &character, const shared_ptr<Party> &party, PlayerId id)
    {
        return {
            .id = id,
            .definition = character,
            .party = party,
            .currentStats = initialStats(character),
        };
    }
}