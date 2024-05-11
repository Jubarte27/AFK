#ifndef COMBAT_H
#define COMBAT_H

#include "character.h"
#include "party.h"
#include "turn_management.h"

namespace combat
{
    using namespace character;
    using namespace turn_management;
    using namespace party;

    class CharacterPlayer : public Player
    {
    private:
        const Character *character;
        Stats stats;
    public:
        CharacterPlayer(const Character *character);
        void act(TurnManager manager) override;
    };

    class Combat
    {
    private:
        TurnManager manager;
        const map<Character *, CharacterPlayer> players;
        map<Character *, CharacterPlayer> createdPlayers;

    public:
        Combat(const vector<Party *> parties);
        void start();

        CharacterPlayer *summon(const Character *character);
    };
} // namespace combat



#endif // COMBAT_H