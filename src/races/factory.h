#pragma once

#include "drow.h"
#include "dwarf.h"
#include "elf.h"
#include "githyanki.h"
#include "gnome.h"
#include "halfelf.h"
#include "halfling.h"
#include "human.h"
#include "race.h"
#include "tiefling.h"

#include <memory>
#include <optional>
#include <variant>

using Subrace = std::variant<std::monostate,
                             Dwarf::Type,
                             Elf::Type,
                             Halfling::Type,
                             HalfElf::Type,
                             Tiefling::Type,
                             Drow::Type,
                             Gnome::Type>;

struct PrintSubraceVisitor
{
  std::string operator()(std::monostate) const
  {
    return "";
  }
  template<typename T>
  std::string operator()(T val) const
  {
    return TypeToString(val);
  }
};

inline std::string TypeToString(const Subrace& subrace)
{
  return std::visit(PrintSubraceVisitor{}, subrace);
}

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
