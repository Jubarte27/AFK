#ifndef LIBCOMBAT_CONVERSIONS_H
#define LIBCOMBAT_CONVERSIONS_H

#include <libcombat/json.hpp>
#include <libcombat/character.hpp>

template<typename E>
concept EnumType = std::is_enum_v<E>;

namespace nlohmann {
    template<EnumType Key, typename Value, typename Compare, typename Allocator>
    struct adl_serializer<std::map<Key, Value, Compare, Allocator>> {
        static void to_json(json& j, const std::map<Key, Value, Compare, Allocator>& opt) {
            for (auto &it : opt) {
                json helper = it.first;
                j[helper] = it.second;
            }
        }

        static void from_json(const json& j, std::map<Key, Value, Compare, Allocator>& opt) {
            for (auto &it : j.items()) {
                json helper = it.key();
                opt[helper.template get<Key>()] = it.value();
            }
        }
    };
}

namespace character
{
    using json = nlohmann::json;

    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(BasicStats, health, mana, strength, dexterity, intelligence, wisdom, charisma, luck)
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(DamageStats, damage, defense, resistance)
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(CombatStats, critical_chance, critical_damage, damage_stats, sub_damage_stats)

/*Horrible*/
    NLOHMANN_JSON_SERIALIZE_ENUM(
        DamageType,
        {
            {DamageType::PHYSICAL, "PHYSICAL"},
            {DamageType::MAGICAL, "MAGICAL"},
            {DamageType::OVER_TIME, "OVER_TIME"},
            {DamageType::TRUE, "TRUE"},
        })
    NLOHMANN_JSON_SERIALIZE_ENUM(
        SubDamageType,
        {
            {SubDamageType::CUTTING, "CUTTING"},
            {SubDamageType::PIERCING, "PIERCING"},
            {SubDamageType::BLUNT, "BLUNT"},
            {SubDamageType::FIRE, "FIRE"},
            {SubDamageType::ICE, "ICE"},
            {SubDamageType::LIGHTNING, "LIGHTNING"},
            {SubDamageType::EARTH, "EARTH"},
            {SubDamageType::WIND, "WIND"},
            {SubDamageType::WATER, "WATER"},
            {SubDamageType::LIGHT, "LIGHT"},
            {SubDamageType::DARK, "DARK"},
            {SubDamageType::ARCANE, "ARCANE"},
            {SubDamageType::POISON, "POISON"},
            {SubDamageType::BURN, "BURN"},
            {SubDamageType::FREEZE, "FREEZE"},
            {SubDamageType::BLEED, "BLEED"},
            {SubDamageType::SHOCK, "SHOCK"},
        })

} // namespace conversions


#endif //LIBCOMBAT_CONVERSIONS_H