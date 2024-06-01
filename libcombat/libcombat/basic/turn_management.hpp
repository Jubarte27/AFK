#ifndef LIBCOMBAT_BASIC_TURN_MANAGEMENT_HPP
#define LIBCOMBAT_BASIC_TURN_MANAGEMENT_HPP

#include <vector>

namespace libcombat::basic
{
    template <typename Actor>
    class TurnManager
    {
    public:
        virtual Actor peek() const = 0;
        virtual Actor next() = 0;
        virtual Actor current() const = 0;

        virtual vector<Actor> peek(int n) const = 0;
        virtual vector<Actor> actors() = 0;
        virtual vector<Actor> history() = 0;
        
        virtual void add(Actor actor) = 0;
        virtual void remove(Actor actor) = 0;
    };
};

#endif // LIBCOMBAT_BASIC_TURN_MANAGEMENT_HPP