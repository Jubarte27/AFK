#ifndef TURN_MANAGEMENT_H
#define TURN_MANAGEMENT_H

#include <vector>
#include <map>
#include <functional>

using namespace std;

class Side
{
public:
    virtual void act(TurnManager manager) = 0;
};

class Counter
{
public:
    const int target;
    int count = 0;
    function<void()> action;

    Counter(int target);
};

class TurnManager
{
private:
    const vector<Side> startingSides;
    vector<int> sides;
    int lastSideIndex = -1;

    /*maps sides indices to counters for that side*/
    map<int, vector<Counter>> counters;

public:
    TurnManager(const vector<Side> sides);
    void next();
    void next(int n);
    void next(Side side);

    void remove(Side side);
    void remove(int index);

    void addCounter(int side, Counter counter);
};

#endif // TURN_MANAGEMENT_H