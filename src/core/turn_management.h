#ifndef TURN_MANAGEMENT_H
#define TURN_MANAGEMENT_H

#include <vector>
#include <map>
#include <functional>

namespace turn_management
{
    using namespace std;

    class Player
    {
    public:
        virtual void act(TurnManager manager) = 0;
    };

    struct Counter
    {
        const int targetCount;
        int count = 0;
        function<void()> action;
    };

    class TurnManager
    {
    private:
        const vector<Player *> startingPlayers;
        vector<Player *> createdPlayers;
        vector<int> activePlayers;
        int lastPlayerIndex = -1;

        /**
         * maps players indices to counters for that player
         */
        map<int, vector<Counter>> counters;

    public:
        /**
         * an index is assigned to each player in the order they are given
         */
        TurnManager(const vector<Player *> players);

        /**
         * returns the total amount of players (starting and created players)
         */
        int count();

        /**
         * the next player to act will be the next remaining player
         */
        void next();
        /**
         * the player with the given index will be the next player to act
         */
        void next(int n);

        /**
         * the player with the given index will be removed from the list of active players
         */
        void remove(int index);

        /**
         * the player will be added to the list of active and created players, at index count()
         */
        void add(Player *player);

        /**
         * adds a counter tht will be updated every turn that the player takes
         */
        void addCounter(int player, Counter counter);
    };
} // namespace turn_management

#endif // TURN_MANAGEMENT_H