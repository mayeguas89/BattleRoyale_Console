import json

with open("cfg/final_spells.json", "r") as f:
    final_spells = json.load(f)

dam = []
for spell in final_spells:
    # try:
    #     if(spell["data"]["Damage"]):
    #         pass
    # except KeyError:
    #     print(spell["name"], spell["data"])
    if (len(spell["damageInflict"]) > 0):
        dam.append(spell["damageInflict"][0])
print(set(dam))
