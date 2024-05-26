#include <iostream>
#include <sstream>

#include <libcombat/combat.hpp>
#include <tests/definitions.hpp>

static void clearScreen()
{
    std::cout << "\033[2J\033[1;1H";
}

static std::string show(const combat::Combatant &combatant)
{
    std::ostringstream text;
    text << "Combatant: " << combatant.id << std::endl;
    text << "Health: " << combatant.currentStats.current_health << std::endl;
    return text.str();
}

static std::string show(const combat::CombatParty &party)
{
    std::ostringstream text;
    for (const auto &combatant : party.combatants)
    {
        if (combatant.currentStats.current_health > 0)
        {
            text << show(combatant) << std::endl;
        }
    }
    return text.str();
}

static std::string show(const combat::Combat &combat, int attacker)
{
    std::ostringstream text;
    text << "Attacker: " << attacker << std::endl;

    text << "Enemies: " << std::endl;
    for (const auto &party : combat.getParties())
    {
        if (combat.getCombatant(attacker).party == party.party)
        {
            continue;
        }
        text << "Party" << std::endl;
        text << show(party) << std::endl;
    }
    return text.str();
}

static std::string show(const combat::AttackResult &result)
{
    std::ostringstream text;
    switch (result.message)
    {
    case combat::HIT:
    case combat::CRITICAL_HIT:
        text << "Hit for " << result.damage << " damage" <<  std::endl;
        break;
    default:
        text << "Error" << std::endl;
        break;
    }
    
    return text.str();
}

static void play(combat::Combat &combat)
{
    while (!combat.finished())
    {
        clearScreen();
        int attacker = combat.start_turn();

        std::cout << show(combat, attacker) << std::endl;
        std::cout << "Choose a target: " << std::endl;

        int defender;
        std::cin >> defender;
        
        std::cout << show(combat.basic_attack(attacker, defender)) << std::endl;

        combat.end_turn();
    }
}

int main(int argc, char *argv[])
{
    using namespace std;
    using namespace combat;
    using namespace character;
    for (int i = 0; i < argc; i++)
    {
        cout << "Argument " << i << ": " << argv[i] << endl;
    }

    auto allies = make_shared<Party>(vector<shared_ptr<CharacterDefinition>>({
        make_shared<CharacterDefinition>(definitions::rogue),
        make_shared<CharacterDefinition>(definitions::mage),
        make_shared<CharacterDefinition>(definitions::tank),
    }));
    auto enemies = make_shared<Party>(vector<shared_ptr<CharacterDefinition>>({
        make_shared<CharacterDefinition>(definitions::john_doe),
        make_shared<CharacterDefinition>(definitions::john_doe),
        make_shared<CharacterDefinition>(definitions::john_doe),
    }));

    Combat combat({allies, enemies});

    play(combat);

    return EXIT_SUCCESS;
}
