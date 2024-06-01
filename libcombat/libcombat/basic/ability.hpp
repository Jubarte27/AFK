#ifndef LIBCOMBAT_BASIC_ABILITY_HPP
#define LIBCOMBAT_BASIC_ABILITY_HPP

#include <map>
#include <functional>
#include <string>

namespace libcombat::basic {
    template <typename Target>
    struct Ability
    {
        std::string name;
        std::string description;
        std::vector<AbilityEffect<Target> *> effects;
    };

    template <typename Target>
    class AbilityEffect
    {
    public:
        virtual void apply(Target &target) = 0;
        virtual void revert(Target &target) = 0;
    };

    template <typename Target, typename AttributeKey, typename AttributeValue>
    class AttributeAbilityEffect : public AbilityEffect<Target>
    {
    private:
        std::map<Target *, AttributeValue> previousValues;
        AttributeKey key;
        AttributeValue value;
        std::function<AttributeValue(const AttributeValue &)> modifierFunction;
    public:
        AttributeAbilityEffect(AttributeKey key, AttributeValue value, std::function<AttributeValue(const AttributeValue &)> modifierFunction)
            : key(key), value(value), modifierFunction(modifierFunction)
        {
        }

        void apply(Target &target) override
        {
            previousValues[{&target}] = target[key];
            target[key] = modifierFunction(target[key]);
        }

        void revert(Target &target) override
        {
            target[key] = previousValues[{&target}];
        }
    };
};

#endif // LIBCOMBAT_BASIC_ABILITY_HPP