# Features

Most things should be just a contract. There should be an implementation for the more basic concepts, but anything that is slightly too complex should be hidden under a contract class.

There will be at least two distinct implementations that are used as an example of the capabilities of these contracts

Maybe the game that comes out of this should be about [contracts](https://en.wikipedia.org/wiki/Sancus)

- [ ] [Turn management](#turn-management) 
- [ ] [Character definitions](#character-definitions])

## Specific descriptions

### Turn management

- [ ] Peek next, advance, last, current
- [ ] Preview n next
- [ ] See n last
- [ ] Move, insert, remove

### Character definitions

- [ ] Can have as many attributes as needed, not known to the contracts
- [ ] Can be upgraded, allowing but not forcing especializations (chosing a tank or damage role, for example).
- [ ] Can have abilities to unlock, with requirements that must be met.
- [ ] 

### Character during combat

- [ ] Will have attributes whose value is determined through functions that use their base attributes
- [ ] May use abilities
- [ ] General purpose "bar" system, that can be use to implement health, mana, vigor, etc.

### Abilities
- [ ] May cost a certain amount of a "bar"
- [ ] May have a cooldown in turns, rounds
- [ ] MAy have "effects": damage, heal, buff, debuff, increase cooldown, decrease attribute permanently (during combat)

### Buffs and debuffs
- [ ] May have effects: deal damage, heal, decrease attribute, increase attribute, mark with "tag", block abilities, block buffs, block debuffs
- [ ] May have duration: turns, rounds, all combat
- [ ] May stack
