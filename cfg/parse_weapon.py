import json
import re

with open("cfg/martialMeleeWeapons.json", "r", encoding='unicode') as f:
    melee = json.load(f)
with open("cfg/simpleMeleeWeapons.json", "r") as f:
    simple_melee = json.load(f)


with open("cfg/martialRangedWeapons.json", "r") as f:
    ranged = json.load(f)
with open("cfg/simpleRangedWeapons.json", "r") as f:
    simple_ranged = json.load(f)

final_melee = []
for weapon in melee:
    match = re.match("([0-9]d[0-9]*) (.*)", weapon["Damage"])
    if (match):
        s = dict.copy(weapon)
        s["Damage"] = match[1]
        s["Damagetype"] = match[2].capitalize()
        final_melee.append(s)
final_melee += simple_melee
final_ranged = []
for weapon in ranged:
    match = re.match("([0-9]d[0-9]*) (.*)", weapon["Damage"])
    if (match):
        s = dict.copy(weapon)
        s["Damage"] = match[1]
        s["Damagetype"] = match[2].capitalize()
        final_ranged.append(s)
final_ranged += simple_ranged

with open("cfg/final_melee_weapons.json", "w") as f:
    f.write(json.dumps(final_melee, indent=4))
with open("cfg/final_ranged_weapons.json", "w") as f:
    f.write(json.dumps(final_ranged, indent=4))
