import json
import re
from pprint import pprint
import os

atlas_path = 'Texture/rogue.png'
atlas_key = 'rogue'
texture_json_path = 'Texture/rogue.json'

folder_name = 'SpaceRogue'
key_pattern = r'SpaceRogue/((rogue_\S+)_(\d{3})).png'

states = set()


with open(texture_json_path, 'r') as json_file:
    data = json.load(json_file)
    data = data['frames']

    for key, value in data.items():
        match = re.match(key_pattern, key)
        if match:
            states.add(match.group(2).upper())

    pprint(states)