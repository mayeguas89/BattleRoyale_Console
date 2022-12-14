#pragma once

#include "barbarian.h"
#include "bard.h"
#include "class.h"
#include "cleric.h"
#include "druid.h"
#include "fighter.h"
#include "ranger.h"
#include "rogue.h"
#include "sorcerer.h"
#include "warlock.h"
#include "wizard.h"

#include <memory>
#include <optional>
#include <variant>

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