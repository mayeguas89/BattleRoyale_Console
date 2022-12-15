import json

with open("cfg/spells-phb.json", "r") as f:
    spells_phb = json.load(f)["spell"]
with open("cfg/spells.json", "r") as f:
    spells = json.load(f)["spell"]

final_spells = []
for spell in spells:
    if("Healing" in spell["data"].keys() or "Damage" in spell["data"].keys()):
        data = [spell_phb for spell_phb in spells_phb if spell["name"] == spell_phb["name"] and spell_phb["duration"][0]["type"] == "instant"]
        if(data):
            s = dict.copy(spell)
            s["level"] = data[0]["level"]
            s["classes"] = [class_data["name"] for class_data in data[0]["classes"]["fromClassList"]]
            try:
                s["damageInflict"] = [damage for damage in data[0]["damageInflict"]]
            except KeyError:
                 s["damageInflict"] = []
            final_spells.append(s)



with open("cfg/final_spells.json", "w") as f:
    f.write(json.dumps(final_spells, indent=4))