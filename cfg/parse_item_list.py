import json

with open("cfg/items-base.json", "r") as f:
    items_base = json.load(f)["baseitem"]
# with open("cfg/spells.json", "r") as f:
#     spells = json.load(f)["spell"]

final_armor = []
for item in items_base:
    if("armor" in item.keys() and item["source"] == "PHB"):
        final_armor.append(item)

with open("cfg/final_armor.json", "w") as f:
    f.write(json.dumps(final_armor, indent=4))