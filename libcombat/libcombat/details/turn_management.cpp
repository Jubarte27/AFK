#include <libcombat/turn_management.hpp>
#include <algorithm>

using namespace turn_management;

// static bool updateCounter(Counter &counter);
static int findPlayerIndex(const vector<PlayerId> &players, PlayerId player);

TurnManager::TurnManager(const vector<PlayerId> players) : startingPlayers(players)
{
    activePlayers = players;
}

TurnManager::TurnManager(const TurnManager &other) : startingPlayers(other.startingPlayers),
                                                     createdPlayers(other.createdPlayers),
                                                     activePlayers(other.activePlayers),
                                                     lastPlayerIndex(other.lastPlayerIndex)
                                                     /*, counters(other.counters)*/
{
}

PlayerId turn_management::TurnManager::next() const
{
    int nextIndex = (lastPlayerIndex + 1) % activePlayers.size();
    return activePlayers[nextIndex];
}


void turn_management::TurnManager::play(PlayerId player)
{
    lastPlayerIndex = findPlayerIndex(activePlayers, player);
    // auto &playerCounters = counters[player];
    // std::erase_if(playerCounters, updateCounter);
}

void turn_management::TurnManager::deactivate(PlayerId player)
{
    int index = findPlayerIndex(activePlayers, player);

    if (index <= lastPlayerIndex)
    {
        lastPlayerIndex--;
    }

    // counters[player].clear();
    // counters.erase(player);

    activePlayers.erase(activePlayers.begin() + index);
}

void turn_management::TurnManager::add(PlayerId player)
{
    createdPlayers.push_back(player);
    activePlayers.push_back(player);
}

// void turn_management::TurnManager::addCounter(PlayerId player, Counter counter)
// {
//     counters[player].push_back(counter);
// }

static int findPlayerIndex(const vector<PlayerId> &players, PlayerId player)
{
    return std::find(players.begin(), players.end(), player) - players.begin();
}

// static bool updateCounter(Counter &counter)
// {
//     counter.count++;
//     if (counter.count == counter.targetCount)
//     {
//         if (counter.action())
//         {
//             counter.count = 0;
//         } else {
//             return true;
//         }
//     }
//     return false;
// }