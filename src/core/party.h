#ifndef PARTY_H
#define PARTY_H

#include <vector>
#include "character.h"

namespace party
{
    using namespace std;
    using namespace character;
    class Party
    {
    public:
        Party();
        ~Party();

        void addMember(const Character *member);
        void removeMember(const Character *member);

    private:
        vector<Character *> members;
    };
} // namespace Party

#endif // PARTY_H
