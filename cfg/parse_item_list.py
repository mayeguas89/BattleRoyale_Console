import json
import re
with open("cfg/items-base.json", "r") as f:
    items_base = json.load(f)["baseitem"]
with open("cfg/items.json", "r") as f:
    items = json.load(f)["item"]

final_armor = []
for item in items_base:
    if("armor" in item.keys() and item["source"] == "PHB"):
        final_armor.append(item)

potions = []
for item in items:
    match = re.match("(Potion).*", item["name"])
    if("resist" in item.keys() and match):
        potions.append(item)

with open("cfg/final_armor.json", "w") as f:
    f.write(json.dumps(final_armor, indent=4))

with open("cfg/final_postions.json", "w") as f:
    f.write(json.dumps(potions, indent=4))