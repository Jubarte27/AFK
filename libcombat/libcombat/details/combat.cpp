#include <libcombat/combat.hpp>

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
                                                               activeCombatants(findActiveCombatants(this->parties)),
                                                               idCounter(firstFreeId(this->parties))

    {
    }

    PlayerId Combat::next_counter()
    {
        return idCounter++;
    }

    void Combat::step()
    {
        // PlayerId player = manager.next();
        // auto combatant = activeCombatants[player];
        // manager.play(player);
    }

    bool Combat::finished() const
    {
        int alive = 0;
        for (const auto &party : parties)
        {
            for (const auto &combatant : party.combatants)
            {
                if (activeCombatants.contains(combatant.id))
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
        return activeCombatants.contains(id);
    }

    const vector<CombatParty> &Combat::getParties() const {
        return parties;
    }

    const Combatant &Combat::getCombatant(PlayerId id) const
    {
        return *activeCombatants.at(id);
    }
    void Combat::damage(PlayerId target, int damage)
    {
        if (!activeCombatants.contains(target))
        {
            return;
        }
        Combatant *combatant = activeCombatants.at(target);
        combatant->currentStats.current_health -= damage;
        if (combatant->currentStats.current_health <= 0)
        {
            activeCombatants.erase(target);
            manager.deactivate(target);
        }
    }

    static int basic_attack_damage(const Stats &attacker, const Stats &target)
    {
        int base_atk_stat = max(attacker.basic_stats.strength, attacker.basic_stats.dexterity);
        int attack = base_atk_stat << 2;

        int base_def_stat = max(target.basic_stats.dexterity, target.basic_stats.constitution);
        int defense = base_def_stat << 1;

        return max(attack - defense, 0);
    }

    static AttackResult _basic_attack(const Combatant &attacker, const Combatant &target)
    {
        int damage = basic_attack_damage(attacker.currentStats, target.currentStats);
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
        if (!activeCombatants.contains(attacker) || !activeCombatants.contains(target))
        {
            return {
                .message = AttackMessage::ERROR_TARGET_NOT_FOUND
            };
        }
        Combatant &attackerCombatant = *activeCombatants.at(attacker);
        Combatant &targetCombatant = *activeCombatants.at(target);

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
        AttackResult result = _basic_attack(attackerCombatant, targetCombatant);
        this->damage(target, result.damage);
        return result;
    }

    void Combat::use_ability(PlayerId attacker, const Ability &ability, PlayerId target)
    {
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
        unordered_map<PlayerId, Combatant *> activeCombatants;
        for (auto &party : parties)
        {
            for (auto &combatant : party.combatants)
            {
                activeCombatants.emplace(combatant.id, &combatant);
            }
        }
        return activeCombatants;
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