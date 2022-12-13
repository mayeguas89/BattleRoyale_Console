#pragma once

#include <memory>
#include <unordered_map>
#include <variant>

using AbilityMap = std::unordered_map<Ability::Type, Ability>;
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

  Race(AbilityMap& ability_map): ability_map_{ability_map} {}
  virtual ~Race() = default;

protected:
  AbilityMap& ability_map_;
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

  Dwarf(AbilityMap& ability_map): Race(ability_map)
  {
    ability_map_[AbilityType::Constitution] += 2;
  }
};

class GoldDwarf: public Dwarf
{
public:
  GoldDwarf(AbilityMap& ability_map): Dwarf(ability_map)
  {
    ability_map_[AbilityType::Wisdom] += 1;
  }
};

class ShieldDwarf: public Dwarf
{
public:
  ShieldDwarf(AbilityMap& ability_map): Dwarf(ability_map)
  {
    ability_map_[AbilityType::Strength] += 2;
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
  Elf(AbilityMap& ability_map): Race(ability_map)
  {
    ability_map_[AbilityType::Dexterity] += 2;
  }
};

class HighElf: public Elf
{
public:
  HighElf(AbilityMap& ability_map): Elf(ability_map)
  {
    ability_map_[AbilityType::Intelligence] += 1;
  }
};

class WoodElf: public Elf
{
public:
  WoodElf(AbilityMap& ability_map): Elf(ability_map)
  {
    ability_map_[AbilityType::Wisdom] += 1;
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
  Halfling(AbilityMap& ability_map): Race(ability_map)
  {
    ability_map_[AbilityType::Dexterity] += 2;
  }
};

class LightfootHalfling: public Halfling
{
public:
  LightfootHalfling(AbilityMap& ability_map): Halfling(ability_map)
  {
    ability_map_[AbilityType::Charisma] += 1;
  }
};

class StrongheartHalfling: public Halfling
{
public:
  StrongheartHalfling(AbilityMap& ability_map): Halfling(ability_map)
  {
    ability_map_[AbilityType::Constitution] += 1;
  }
};

class Human: public Race
{
public:
  Human(AbilityMap& ability_map): Race(ability_map)
  {
    for (auto& ability: ability_map_)
    {
      ability.second += 1;
    }
  }
};

class Githyanki: public Race
{
public:
  Githyanki(AbilityMap& ability_map): Race(ability_map)
  {
    ability_map_[AbilityType::Intelligence] += 1;
    ability_map_[AbilityType::Strength] += 2;
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
  HalfElf(AbilityMap& ability_map): Race(ability_map)
  {
    ability_map_[AbilityType::Charisma] += 2;
    // TODO: Add +2 points in other habilities
  }
};

class HighHalfElf: public HalfElf
{
public:
  HighHalfElf(AbilityMap& ability_map): HalfElf(ability_map) {}
};

class WoodHalfElf: public HalfElf
{
public:
  WoodHalfElf(AbilityMap& ability_map): HalfElf(ability_map) {}
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
  Tiefling(AbilityMap& ability_map): Race(ability_map) {}
};

class AsmodeusTiefling: public Tiefling
{
public:
  AsmodeusTiefling(AbilityMap& ability_map): Tiefling(ability_map)
  {
    ability_map_[AbilityType::Charisma] += 2;
    ability_map_[AbilityType::Intelligence] += 2;
  }
};

class MephistophelesTiefling: public Tiefling
{
public:
  MephistophelesTiefling(AbilityMap& ability_map): Tiefling(ability_map)
  {
    ability_map_[AbilityType::Charisma] += 2;
    ability_map_[AbilityType::Intelligence] += 1;
  }
};

class ZarielTiefling: public Tiefling
{
public:
  ZarielTiefling(AbilityMap& ability_map): Tiefling(ability_map)
  {
    ability_map_[AbilityType::Charisma] += 2;
    ability_map_[AbilityType::Strength] += 1;
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
  Drow(AbilityMap& ability_map): Race(ability_map)
  {
    ability_map_[AbilityType::Charisma] += 1;
    ability_map_[AbilityType::Dexterity] += 1;
  }
};

class LolthSwornDrow: public Drow
{
public:
  LolthSwornDrow(AbilityMap& ability_map): Drow(ability_map) {}
};

class SeldarineDrow: public Drow
{
public:
  SeldarineDrow(AbilityMap& ability_map): Drow(ability_map) {}
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
  Gnome(AbilityMap& ability_map): Race(ability_map)
  {
    ability_map_[AbilityType::Intelligence] += 1;
  }
};

class DeepGnome: public Gnome
{
public:
  DeepGnome(AbilityMap& ability_map): Gnome(ability_map)
  {
    ability_map_[AbilityType::Dexterity] += 1;
  }
};

class ForestGnome: public Gnome
{
public:
  ForestGnome(AbilityMap& ability_map): Gnome(ability_map)
  {
    ability_map_[AbilityType::Dexterity] += 1;
  }
};

class RockGnome: public Gnome
{
public:
  RockGnome(AbilityMap& ability_map): Gnome(ability_map)
  {
    ability_map_[AbilityType::Constitution] += 1;
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
  static std::unique_ptr<Race> CreateDwarf(AbilityMap& ability_map, Dwarf::Type subrace_type)
  {
    switch (subrace_type)
    {
      case Dwarf::Type::GoldDwarf:
        return std::make_unique<GoldDwarf>(ability_map);
      case Dwarf::Type::ShieldDwarf:
        return std::make_unique<ShieldDwarf>(ability_map);
    }
  }
};

class ElfFactory
{
public:
  static std::unique_ptr<Race> CreateElf(AbilityMap& ability_map, Elf::Type subrace_type)
  {
    switch (subrace_type)
    {
      case Elf::Type::HighElf:
        return std::make_unique<HighElf>(ability_map);
      case Elf::Type::WoodElf:
        return std::make_unique<WoodElf>(ability_map);
    }
  }
};

class HalflingFactory
{
public:
  static std::unique_ptr<Race> CreateHalfling(AbilityMap& ability_map, Halfling::Type subrace_type)
  {
    switch (subrace_type)
    {
      case Halfling::Type::LightfootHalfling:
        return std::make_unique<LightfootHalfling>(ability_map);
      case Halfling::Type::StrongheartHalfling:
        return std::make_unique<StrongheartHalfling>(ability_map);
    }
  }
};

class HalfElfFactory
{
public:
  static std::unique_ptr<Race> CreateHalfElf(AbilityMap& ability_map, HalfElf::Type subrace_type)
  {
    switch (subrace_type)
    {
      case HalfElf::Type::HighHalfElf:
        return std::make_unique<HighHalfElf>(ability_map);
      case HalfElf::Type::WoodHalfElf:
        return std::make_unique<WoodHalfElf>(ability_map);
    }
  }
};

class DrowFactory
{
public:
  static std::unique_ptr<Race> CreateDrow(AbilityMap& ability_map, Drow::Type subrace_type)
  {
    switch (subrace_type)
    {
      case Drow::Type::LolthSwornDrow:
        return std::make_unique<LolthSwornDrow>(ability_map);
      case Drow::Type::SeldarineDrow:
        return std::make_unique<SeldarineDrow>(ability_map);
    }
  }
};

class TieflingFactory
{
public:
  static std::unique_ptr<Race> CreateTiefling(AbilityMap& ability_map, Tiefling::Type subrace_type)
  {
    switch (subrace_type)
    {
      case Tiefling::Type::AsmodeusTiefling:
        return std::make_unique<AsmodeusTiefling>(ability_map);
      case Tiefling::Type::MephistophelesTiefling:
        return std::make_unique<MephistophelesTiefling>(ability_map);
      case Tiefling::Type::ZarielTiefling:
        return std::make_unique<ZarielTiefling>(ability_map);
    }
  }
};

class GnomeFactory
{
public:
  static std::unique_ptr<Race> CreateGnome(AbilityMap& ability_map, Gnome::Type subrace_type)
  {
    switch (subrace_type)
    {
      case Gnome::Type::DeepGnome:
        return std::make_unique<DeepGnome>(ability_map);
      case Gnome::Type::ForestGnome:
        return std::make_unique<ForestGnome>(ability_map);
      case Gnome::Type::RockGnome:
        return std::make_unique<RockGnome>(ability_map);
    }
  }
};

class RaceFactory
{
public:
  static std::optional<std::unique_ptr<Race>>
    CreateRace(AbilityMap& ability_map, Race::Type race_type, Subrace subrace)
  {
    std::optional<std::unique_ptr<Race>> to_return;
    switch (race_type)
    {
      case Race::Type::Dwarf:
      {
        auto dwarf_type = std::visit(Dwarf::Visitor{}, subrace);
        if (dwarf_type)
          to_return = DwarfFactory::CreateDwarf(ability_map, *dwarf_type);
        break;
      }
      case Race::Type::Elf:
      {
        auto elf_type = std::visit(Elf::Visitor{}, subrace);
        if (elf_type)
          to_return = ElfFactory::CreateElf(ability_map, *elf_type);
        break;
      }
      case Race::Type::Halfling:
      {
        auto halfling_type = std::visit(Halfling::Visitor{}, subrace);
        if (halfling_type)
          to_return = HalflingFactory::CreateHalfling(ability_map, *halfling_type);
        break;
      }
      case Race::Type::Human:
      {
        to_return = std::make_unique<Human>(ability_map);
        break;
      }
      case Race::Type::Githyanki:
      {
        to_return = std::make_unique<Githyanki>(ability_map);
        break;
      }
      case Race::Type::HalfElf:
      {
        auto halfelf_type = std::visit(HalfElf::Visitor{}, subrace);
        if (halfelf_type)
          to_return = HalfElfFactory::CreateHalfElf(ability_map, *halfelf_type);
        break;
      }
      case Race::Type::Tiefling:
      {
        auto tiefling_type = std::visit(Tiefling::Visitor{}, subrace);
        if (tiefling_type)
          to_return = TieflingFactory::CreateTiefling(ability_map, *tiefling_type);
        break;
      }
      case Race::Type::Drow:
      {
        auto drow_type = std::visit(Drow::Visitor{}, subrace);
        if (drow_type)
          to_return = DrowFactory::CreateDrow(ability_map, *drow_type);
        break;
      }
      case Race::Type::Gnome:
      {
        auto gnome_type = std::visit(Gnome::Visitor{}, subrace);
        if (gnome_type)
          to_return = GnomeFactory::CreateGnome(ability_map, *gnome_type);
        break;
      }
    }
    return to_return;
  }
};