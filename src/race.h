#pragma once
#include "ability.h"

#include <memory>
#include <optional>
#include <unordered_map>
#include <variant>

using AbilityType = Ability::Type;

class Race
{
public:
  enum class Type
  {
    Dwarf,
    Elf,
    Halfling,
    Human,
    Githyanki,
    HalfElf,
    Tiefling,
    Drow,
    Gnome
  };

  Race(Abilities& abilities) {}
  virtual ~Race() = default;

protected:
};

class Dwarf: public Race
{
public:
  enum class Type
  {
    GoldDwarf,
    ShieldDwarf
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

  Dwarf(Abilities& abilities): Race(abilities)
  {
    abilities.map[AbilityType::Constitution] += 2;
  }
};

class GoldDwarf: public Dwarf
{
public:
  GoldDwarf(Abilities& abilities): Dwarf(abilities)
  {
    abilities.map[AbilityType::Wisdom] += 1;
  }
};

class ShieldDwarf: public Dwarf
{
public:
  ShieldDwarf(Abilities& abilities): Dwarf(abilities)
  {
    abilities.map[AbilityType::Strength] += 2;
  }
};

class Elf: public Race
{
public:
  enum class Type
  {
    HighElf,
    WoodElf
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
  Elf(Abilities& abilities): Race(abilities)
  {
    abilities.map[AbilityType::Dexterity] += 2;
  }
};

class HighElf: public Elf
{
public:
  HighElf(Abilities& abilities): Elf(abilities)
  {
    abilities.map[AbilityType::Intelligence] += 1;
  }
};

class WoodElf: public Elf
{
public:
  WoodElf(Abilities& abilities): Elf(abilities)
  {
    abilities.map[AbilityType::Wisdom] += 1;
  }
};

class Halfling: public Race
{
public:
  enum class Type
  {
    LightfootHalfling,
    StrongheartHalfling
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
  Halfling(Abilities& abilities): Race(abilities)
  {
    abilities.map[AbilityType::Dexterity] += 2;
  }
};

class LightfootHalfling: public Halfling
{
public:
  LightfootHalfling(Abilities& abilities): Halfling(abilities)
  {
    abilities.map[AbilityType::Charisma] += 1;
  }
};

class StrongheartHalfling: public Halfling
{
public:
  StrongheartHalfling(Abilities& abilities): Halfling(abilities)
  {
    abilities.map[AbilityType::Constitution] += 1;
  }
};

class Human: public Race
{
public:
  Human(Abilities& abilities): Race(abilities)
  {
    for (auto& ability: abilities.map)
    {
      ability.second += 1;
    }
  }
};

class Githyanki: public Race
{
public:
  Githyanki(Abilities& abilities): Race(abilities)
  {
    abilities.map[AbilityType::Intelligence] += 1;
    abilities.map[AbilityType::Strength] += 2;
  }
};

class HalfElf: public Race
{
public:
  enum class Type
  {
    HighHalfElf,
    WoodHalfElf
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
  HalfElf(Abilities& abilities): Race(abilities)
  {
    abilities.map[AbilityType::Charisma] += 2;
    // TODO: Add +2 points in other habilities
  }
};

class HighHalfElf: public HalfElf
{
public:
  HighHalfElf(Abilities& abilities): HalfElf(abilities) {}
};

class WoodHalfElf: public HalfElf
{
public:
  WoodHalfElf(Abilities& abilities): HalfElf(abilities) {}
};

class Tiefling: public Race
{
public:
  enum class Type
  {
    AsmodeusTiefling,
    MephistophelesTiefling,
    ZarielTiefling
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
  Tiefling(Abilities& abilities): Race(abilities) {}
};

class AsmodeusTiefling: public Tiefling
{
public:
  AsmodeusTiefling(Abilities& abilities): Tiefling(abilities)
  {
    abilities.map[AbilityType::Charisma] += 2;
    abilities.map[AbilityType::Intelligence] += 2;
  }
};

class MephistophelesTiefling: public Tiefling
{
public:
  MephistophelesTiefling(Abilities& abilities): Tiefling(abilities)
  {
    abilities.map[AbilityType::Charisma] += 2;
    abilities.map[AbilityType::Intelligence] += 1;
  }
};

class ZarielTiefling: public Tiefling
{
public:
  ZarielTiefling(Abilities& abilities): Tiefling(abilities)
  {
    abilities.map[AbilityType::Charisma] += 2;
    abilities.map[AbilityType::Strength] += 1;
  }
};

class Drow: public Race
{
public:
  enum class Type
  {
    LolthSwornDrow,
    SeldarineDrow
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
  Drow(Abilities& abilities): Race(abilities)
  {
    abilities.map[AbilityType::Charisma] += 1;
    abilities.map[AbilityType::Dexterity] += 1;
  }
};

class LolthSwornDrow: public Drow
{
public:
  LolthSwornDrow(Abilities& abilities): Drow(abilities) {}
};

class SeldarineDrow: public Drow
{
public:
  SeldarineDrow(Abilities& abilities): Drow(abilities) {}
};

class Gnome: public Race
{
public:
  enum class Type
  {
    DeepGnome,
    ForestGnome,
    RockGnome
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
  Gnome(Abilities& abilities): Race(abilities)
  {
    abilities.map[AbilityType::Intelligence] += 1;
  }
};

class DeepGnome: public Gnome
{
public:
  DeepGnome(Abilities& abilities): Gnome(abilities)
  {
    abilities.map[AbilityType::Dexterity] += 1;
  }
};

class ForestGnome: public Gnome
{
public:
  ForestGnome(Abilities& abilities): Gnome(abilities)
  {
    abilities.map[AbilityType::Dexterity] += 1;
  }
};

class RockGnome: public Gnome
{
public:
  RockGnome(Abilities& abilities): Gnome(abilities)
  {
    abilities.map[AbilityType::Constitution] += 1;
  }
};

using Subrace = std::variant<std::monostate,
                             Dwarf::Type,
                             Elf::Type,
                             Halfling::Type,
                             HalfElf::Type,
                             Tiefling::Type,
                             Drow::Type,
                             Gnome::Type>;

class DwarfFactory
{
public:
  static std::unique_ptr<Race> Create(Abilities& abilities, Dwarf::Type subrace_type)
  {
    std::unique_ptr<Race> to_return;
    switch (subrace_type)
    {
      case Dwarf::Type::GoldDwarf:
        return std::make_unique<GoldDwarf>(abilities);
      case Dwarf::Type::ShieldDwarf:
        return std::make_unique<ShieldDwarf>(abilities);
    }
    return to_return;
  }
};

class ElfFactory
{
public:
  static std::unique_ptr<Race> Create(Abilities& abilities, Elf::Type subrace_type)
  {
    std::unique_ptr<Race> to_return;
    switch (subrace_type)
    {
      case Elf::Type::HighElf:
        return std::make_unique<HighElf>(abilities);
      case Elf::Type::WoodElf:
        return std::make_unique<WoodElf>(abilities);
    }
    return to_return;
  }
};

class HalflingFactory
{
public:
  static std::unique_ptr<Race> Create(Abilities& abilities, Halfling::Type subrace_type)
  {
    std::unique_ptr<Race> to_return;
    switch (subrace_type)
    {
      case Halfling::Type::LightfootHalfling:
        return std::make_unique<LightfootHalfling>(abilities);
      case Halfling::Type::StrongheartHalfling:
        return std::make_unique<StrongheartHalfling>(abilities);
    }
    return to_return;
  }
};

class HalfElfFactory
{
public:
  static std::unique_ptr<Race> Create(Abilities& abilities, HalfElf::Type subrace_type)
  {
    std::unique_ptr<Race> to_return;
    switch (subrace_type)
    {
      case HalfElf::Type::HighHalfElf:
        return std::make_unique<HighHalfElf>(abilities);
      case HalfElf::Type::WoodHalfElf:
        return std::make_unique<WoodHalfElf>(abilities);
    }
    return to_return;
  }
};

class DrowFactory
{
public:
  static std::unique_ptr<Race> Create(Abilities& abilities, Drow::Type subrace_type)
  {
    std::unique_ptr<Race> to_return;
    switch (subrace_type)
    {
      case Drow::Type::LolthSwornDrow:
        return std::make_unique<LolthSwornDrow>(abilities);
      case Drow::Type::SeldarineDrow:
        return std::make_unique<SeldarineDrow>(abilities);
    }
    return to_return;
  }
};

class TieflingFactory
{
public:
  static std::unique_ptr<Race> Create(Abilities& abilities, Tiefling::Type subrace_type)
  {
    std::unique_ptr<Race> to_return;
    switch (subrace_type)
    {
      case Tiefling::Type::AsmodeusTiefling:
        return std::make_unique<AsmodeusTiefling>(abilities);
      case Tiefling::Type::MephistophelesTiefling:
        return std::make_unique<MephistophelesTiefling>(abilities);
      case Tiefling::Type::ZarielTiefling:
        return std::make_unique<ZarielTiefling>(abilities);
    }
    return to_return;
  }
};

class GnomeFactory
{
public:
  static std::unique_ptr<Race> Create(Abilities& abilities, Gnome::Type subrace_type)
  {
    std::unique_ptr<Race> to_return;
    switch (subrace_type)
    {
      case Gnome::Type::DeepGnome:
        return std::make_unique<DeepGnome>(abilities);
      case Gnome::Type::ForestGnome:
        return std::make_unique<ForestGnome>(abilities);
      case Gnome::Type::RockGnome:
        return std::make_unique<RockGnome>(abilities);
    }
    return to_return;
  }
};

class RaceFactory
{
public:
  static std::unique_ptr<Race>
    Create(Abilities& abilities, Race::Type race_type, Subrace subrace = std::monostate{})
  {
    std::unique_ptr<Race> to_return;
    switch (race_type)
    {
      case Race::Type::Dwarf:
      {
        auto dwarf_type = std::visit(Dwarf::Visitor{}, subrace);
        if (dwarf_type)
          to_return = DwarfFactory::Create(abilities, *dwarf_type);
        break;
      }
      case Race::Type::Elf:
      {
        auto elf_type = std::visit(Elf::Visitor{}, subrace);
        if (elf_type)
          to_return = ElfFactory::Create(abilities, *elf_type);
        break;
      }
      case Race::Type::Halfling:
      {
        auto halfling_type = std::visit(Halfling::Visitor{}, subrace);
        if (halfling_type)
          to_return = HalflingFactory::Create(abilities, *halfling_type);
        break;
      }
      case Race::Type::Human:
      {
        to_return = std::make_unique<Human>(abilities);
        break;
      }
      case Race::Type::Githyanki:
      {
        to_return = std::make_unique<Githyanki>(abilities);
        break;
      }
      case Race::Type::HalfElf:
      {
        auto halfelf_type = std::visit(HalfElf::Visitor{}, subrace);
        if (halfelf_type)
          to_return = HalfElfFactory::Create(abilities, *halfelf_type);
        break;
      }
      case Race::Type::Tiefling:
      {
        auto tiefling_type = std::visit(Tiefling::Visitor{}, subrace);
        if (tiefling_type)
          to_return = TieflingFactory::Create(abilities, *tiefling_type);
        break;
      }
      case Race::Type::Drow:
      {
        auto drow_type = std::visit(Drow::Visitor{}, subrace);
        if (drow_type)
          to_return = DrowFactory::Create(abilities, *drow_type);
        break;
      }
      case Race::Type::Gnome:
      {
        auto gnome_type = std::visit(Gnome::Visitor{}, subrace);
        if (gnome_type)
          to_return = GnomeFactory::Create(abilities, *gnome_type);
        break;
      }
    }
    return to_return;
  }
};