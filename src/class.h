#pragma once
#include "ability.h"

#include <memory>
#include <optional>
#include <variant>
using AbilityType = Ability::Type;

class Class
{
public:
  enum class Type
  {
    Barbarian,
    Bard,
    Cleric,
    Druid,
    Fighter,
    Ranger,
    Rogue,
    Sorcerer,
    Warlock,
    Wizard
  };

  Class(Abilities& abilities, int hit_die, int hit_die_per_level):
    hit_die_{hit_die},
    hit_die_per_level_{hit_die_per_level}
  {}
  int GetHitDie()
  {
    return hit_die_;
  }

protected:
  int hit_die_;
  int hit_die_per_level_;
};

class Barbarian: public Class
{
public:
  Barbarian(Abilities& abilities): Class(abilities, 14, 0)
  {
    abilities.map[AbilityType::Strength] += 15;
    abilities.map[AbilityType::Dexterity] += 13;
    abilities.map[AbilityType::Constitution] += 14;
    abilities.map[AbilityType::Intelligence] += 8;
    abilities.map[AbilityType::Wisdom] += 12;
    abilities.map[AbilityType::Charisma] += 10;
  }
};
class Bard: public Class
{
public:
  Bard(Abilities& abilities): Class(abilities, 10, 0)
  {
    abilities.map[AbilityType::Strength] += 8;
    abilities.map[AbilityType::Dexterity] += 14;
    abilities.map[AbilityType::Constitution] += 13;
    abilities.map[AbilityType::Intelligence] += 12;
    abilities.map[AbilityType::Wisdom] += 10;
    abilities.map[AbilityType::Charisma] += 15;
  }
};
class Cleric: public Class
{
public:
  enum class Type
  {
    LifeDomainCleric,
    LightDomainCleric,
    TrickeryDomainCleric
  };
  struct Visitor
  {
    std::optional<Type> operator()(Type type) const
    {
      return type;
    }
    template<typename T>
    std::optional<Type> operator()(T) const
    {
      return std::nullopt;
    }
  };
  Cleric(Abilities& abilities): Class(abilities, 10, 0) {}
};

class LifeDomainCleric: public Cleric
{
public:
  LifeDomainCleric(Abilities& abilities): Cleric(abilities)
  {
    abilities.map[AbilityType::Strength] += 14;
    abilities.map[AbilityType::Dexterity] += 10;
    abilities.map[AbilityType::Constitution] += 13;
    abilities.map[AbilityType::Intelligence] += 8;
    abilities.map[AbilityType::Wisdom] += 15;
    abilities.map[AbilityType::Charisma] += 12;
  }
};

class LightDomainCleric: public Cleric
{
public:
  LightDomainCleric(Abilities& abilities): Cleric(abilities)
  {
    abilities.map[AbilityType::Strength] += 10;
    abilities.map[AbilityType::Dexterity] += 14;
    abilities.map[AbilityType::Constitution] += 13;
    abilities.map[AbilityType::Intelligence] += 8;
    abilities.map[AbilityType::Wisdom] += 15;
    abilities.map[AbilityType::Charisma] += 12;
  }
};

class TrickeryDomainCleric: public Cleric
{
public:
  TrickeryDomainCleric(Abilities& abilities): Cleric(abilities)
  {
    abilities.map[AbilityType::Strength] += 12;
    abilities.map[AbilityType::Dexterity] += 13;
    abilities.map[AbilityType::Constitution] += 14;
    abilities.map[AbilityType::Intelligence] += 10;
    abilities.map[AbilityType::Wisdom] += 15;
    abilities.map[AbilityType::Charisma] += 8;
  }
};

class Druid: public Class
{
public:
  Druid(Abilities& abilities): Class(abilities, 10, 0)
  {
    abilities.map[AbilityType::Strength] += 10;
    abilities.map[AbilityType::Dexterity] += 14;
    abilities.map[AbilityType::Constitution] += 13;
    abilities.map[AbilityType::Intelligence] += 8;
    abilities.map[AbilityType::Wisdom] += 15;
    abilities.map[AbilityType::Charisma] += 12;
  }
};
class Fighter: public Class
{
public:
  Fighter(Abilities& abilities): Class(abilities, 12, 0)
  {
    abilities.map[AbilityType::Strength] += 15;
    abilities.map[AbilityType::Dexterity] += 13;
    abilities.map[AbilityType::Constitution] += 14;
    abilities.map[AbilityType::Intelligence] += 10;
    abilities.map[AbilityType::Wisdom] += 12;
    abilities.map[AbilityType::Charisma] += 8;
  }
};
class Ranger: public Class
{
public:
  Ranger(Abilities& abilities): Class(abilities, 12, 0)
  {
    abilities.map[AbilityType::Strength] += 12;
    abilities.map[AbilityType::Dexterity] += 15;
    abilities.map[AbilityType::Constitution] += 13;
    abilities.map[AbilityType::Intelligence] += 8;
    abilities.map[AbilityType::Wisdom] += 14;
    abilities.map[AbilityType::Charisma] += 10;
  }
};
class Rogue: public Class
{
public:
  Rogue(Abilities& abilities): Class(abilities, 10, 0)
  {
    abilities.map[AbilityType::Strength] += 8;
    abilities.map[AbilityType::Dexterity] += 15;
    abilities.map[AbilityType::Constitution] += 14;
    abilities.map[AbilityType::Intelligence] += 12;
    abilities.map[AbilityType::Wisdom] += 13;
    abilities.map[AbilityType::Charisma] += 10;
  }
};
class Sorcerer: public Class
{
public:
  enum class Type
  {
    WildMagicSorcerer,
    DraconicBloodlineSorcerer
  };
  struct Visitor
  {
    std::optional<Type> operator()(Type type) const
    {
      return type;
    }
    template<typename T>
    std::optional<Type> operator()(T) const
    {
      return std::nullopt;
    }
  };
  Sorcerer(Abilities& abilities): Class(abilities, 8, 0)
  {
    abilities.map[AbilityType::Strength] += 8;
    abilities.map[AbilityType::Dexterity] += 13;
    abilities.map[AbilityType::Constitution] += 14;
    abilities.map[AbilityType::Intelligence] += 12;
    abilities.map[AbilityType::Wisdom] += 10;
    abilities.map[AbilityType::Charisma] += 15;
  }
};
class WildMagicSorcerer: public Sorcerer
{
public:
  WildMagicSorcerer(Abilities& abilities): Sorcerer(abilities) {}
};
class DraconicBloodlineSorcerer: public Sorcerer
{
public:
  DraconicBloodlineSorcerer(Abilities& abilities): Sorcerer(abilities) {}
};
class Warlock: public Class
{
public:
  enum class Type
  {
    TheFiendWarlock,
    TheGreatOldOneWarlock
  };
  struct Visitor
  {
    std::optional<Type> operator()(Type type) const
    {
      return type;
    }
    template<typename T>
    std::optional<Type> operator()(T) const
    {
      return std::nullopt;
    }
  };
  Warlock(Abilities& abilities): Class(abilities, 10, 0)
  {
    abilities.map[AbilityType::Strength] += 8;
    abilities.map[AbilityType::Dexterity] += 12;
    abilities.map[AbilityType::Constitution] += 14;
    abilities.map[AbilityType::Intelligence] += 13;
    abilities.map[AbilityType::Wisdom] += 10;
    abilities.map[AbilityType::Charisma] += 15;
  }
};

class TheFiendWarlock: public Warlock
{
public:
  TheFiendWarlock(Abilities& abilities): Warlock(abilities) {}
};
class TheGreatOldOneWarlock: public Warlock
{
public:
  TheGreatOldOneWarlock(Abilities& abilities): Warlock(abilities) {}
};
class Wizard: public Class
{
public:
  Wizard(Abilities& abilities): Class(abilities, 14, 0)
  {
    abilities.map[AbilityType::Strength] += 8;
    abilities.map[AbilityType::Dexterity] += 13;
    abilities.map[AbilityType::Constitution] += 14;
    abilities.map[AbilityType::Intelligence] += 15;
    abilities.map[AbilityType::Wisdom] += 10;
    abilities.map[AbilityType::Charisma] += 12;
  }
};

using Subclass = std::variant<std::monostate, Cleric::Type, Sorcerer::Type, Warlock::Type>;

class ClericFactory
{
public:
  static std::unique_ptr<Class> Create(Abilities& abilities, Cleric::Type subclass_type)
  {
    std::unique_ptr<Class> to_return;
    switch (subclass_type)
    {
      case Cleric::Type::LifeDomainCleric:
        return std::make_unique<LifeDomainCleric>(abilities);
      case Cleric::Type::LightDomainCleric:
        return std::make_unique<LightDomainCleric>(abilities);
      case Cleric::Type::TrickeryDomainCleric:
        return std::make_unique<TrickeryDomainCleric>(abilities);
    }
    return to_return;
  }
};

class SorcererFactory
{
public:
  static std::unique_ptr<Class> Create(Abilities& abilities, Sorcerer::Type subclass_type)
  {
    std::unique_ptr<Class> to_return;
    switch (subclass_type)
    {
      case Sorcerer::Type::WildMagicSorcerer:
        return std::make_unique<WildMagicSorcerer>(abilities);
      case Sorcerer::Type::DraconicBloodlineSorcerer:
        return std::make_unique<DraconicBloodlineSorcerer>(abilities);
    }
    return to_return;
  }
};

class WarlockFactory
{
public:
  static std::unique_ptr<Class> Create(Abilities& abilities, Warlock::Type subclass_type)
  {
    std::unique_ptr<Class> to_return;
    switch (subclass_type)
    {
      case Warlock::Type::TheFiendWarlock:
        return std::make_unique<TheFiendWarlock>(abilities);
      case Warlock::Type::TheGreatOldOneWarlock:
        return std::make_unique<TheGreatOldOneWarlock>(abilities);
    }
    return to_return;
  }
};

class ClassFactory
{
public:
  static std::unique_ptr<Class>
    Create(Abilities& abilities, Class::Type class_type, Subclass subclass = std::monostate{})
  {
    std::unique_ptr<Class> to_return;
    switch (class_type)
    {
      case Class::Type::Barbarian:
      {
        to_return = std::make_unique<Barbarian>(abilities);
        break;
      }
      case Class::Type::Bard:
      {
        to_return = std::make_unique<Bard>(abilities);
        break;
      }
      case Class::Type::Cleric:
      {
        auto cleric_type = std::visit(Cleric::Visitor{}, subclass);
        if (cleric_type)
          to_return = ClericFactory::Create(abilities, *cleric_type);
        break;
      }
      case Class::Type::Druid:
      {
        to_return = std::make_unique<Druid>(abilities);
        break;
      }
      case Class::Type::Fighter:
      {
        to_return = std::make_unique<Fighter>(abilities);
        break;
      }
      case Class::Type::Ranger:
      {
        to_return = std::make_unique<Ranger>(abilities);
        break;
      }
      case Class::Type::Rogue:
      {
        to_return = std::make_unique<Rogue>(abilities);
        break;
      }
      case Class::Type::Wizard:
      {
        to_return = std::make_unique<Wizard>(abilities);
        break;
      }
      case Class::Type::Sorcerer:
      {
        auto sorcerer_type = std::visit(Sorcerer::Visitor{}, subclass);
        if (sorcerer_type)
          to_return = SorcererFactory::Create(abilities, *sorcerer_type);
        break;
      }
      case Class::Type::Warlock:
      {
        auto warlock_type = std::visit(Warlock::Visitor{}, subclass);
        if (warlock_type)
          to_return = WarlockFactory::Create(abilities, *warlock_type);
        break;
      }
    }
    return to_return;
  }
};