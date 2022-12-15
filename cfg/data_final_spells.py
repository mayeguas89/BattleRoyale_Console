import json

with open("cfg/final_spells.json", "r") as f:
    final_spells = json.load(f)

for spell in final_spells:
    try:
        if(spell["data"]["Damage"]):
            pass
    except KeyError:
        print(spell["name"], spell["data"])
