#include <libcombat/character.hpp>
#include <algorithm>

using namespace character;

// bool Stats::hasModifier(const Modifier &modifier) const
// {
//     int id = modifier.id;
//     auto same_id = [id](const Modifier &m)
//     {
//         return m.id == id;
//     };
//     auto it = std::find_if(modifiers.begin(), modifiers.end(), same_id);
//     return modifiers.end() != it;
// }