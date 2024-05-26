#ifndef PARTY_H
#define PARTY_H

#include <vector>
#include <memory>

#include <libcombat/character.hpp>

namespace party
{
    using namespace std;
    using namespace character;
    struct Party
    {
        vector<shared_ptr<CharacterDefinition>> members;
    };
} // namespace Party

#endif // PARTY_H
