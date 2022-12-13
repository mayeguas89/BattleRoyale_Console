#pragma once

class Class
{
public:
  Class(int hit_die, int hit_die_per_level): hit_die_{hit_die}, hit_die_per_level_{hit_die_per_level} {}
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
  Barbarian(): Class(12, 0) {}
};
class Bard: public Class
{
public:
  Bard(): Class(8,0) {}
};
class Cleric: public Class
{
public:
  Cleric(): Class(8, 5) {}
};
class Druid: public Class
{
public:
  Druid(): Class(8, 5) {}
};
class Fighter: public Class
{
public:
  Fighter(): Class(10, 6) {}
};
class Monk: public Class
{
public:
  Monk(): Class(8,0) {}
};
class Paladin: public Class
{
public:
  Paladin(): Class(10, 0) {}
};
class Ranger: public Class
{
public:
  Ranger(): Class(10, 6) {}
};
class Rogue: public Class
{
public:
  Rogue(): Class(8, 5) {}
};
class Sorcerer: public Class
{
public:
  Sorcerer(): Class(6, 4) {}
};
class Warlock: public Class
{
public:
  Warlock(): Class(8, 5) {}
};
class Wizard: public Class
{
public:
  Wizard(): Class(6, 4) {}
};