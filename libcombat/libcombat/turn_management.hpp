#ifndef TURN_MANAGEMENT_H
#define TURN_MANAGEMENT_H

#include <vector>
#include <map>
#include <functional>

namespace turn_management
{
    using namespace std;

    using PlayerId = int;

    // struct Counter
    // {
    //     const int targetCount;
    //     int count = 0;
    //     function<bool()> action;
    // };

    class TurnManager
    {
    private:
        const vector<PlayerId> startingPlayers;
        vector<PlayerId> createdPlayers;
        vector<PlayerId> activePlayers;
        int lastPlayerIndex = -1;

        // map<PlayerId, vector<Counter>> counters;

    public:
        TurnManager(const vector<PlayerId> players);
        TurnManager(const TurnManager &other);

        /**
         * returns who should be the next player to act.
         */
        PlayerId next() const;
        /**
         * the player acts and its counters are updated.
         */
        void play(PlayerId player);

        /**
         * the player with the given index will be removed from the list of active players
         */
        void deactivate(PlayerId player);

        /**
         * the player will be added to the end of the list of active and created players
         */
        void add(PlayerId player);

        /**
         * adds a counter that will be updated every turn that the player takes
         */
        // void addCounter(PlayerId player, Counter counter);
    };
} // namespace turn_management

#endif // TURN_MANAGEMENT_H