#ifndef LIBCOMBAT_BASIC_CHARACTER_HPP
#define LIBCOMBAT_BASIC_CHARACTER_HPP

#include <string>
#include <libcombat/basic/ability.hpp>

namespace libcombat::basic {
    template<typename AttributeKey, typename AttributeValue>
    class Character
    {
    private:
        std::vector<Ability<Character<AttributeKey, AttributeValue>>> abilities;
    public:
        virtual AttributeValue &operator[](AttributeKey key) const = 0;
    };
    
};

#endif // LIBCOMBAT_BASIC_CHARACTER_HPP