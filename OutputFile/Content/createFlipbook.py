# make every sprite file

import json
import re
from pprint import pprint
import os

atlas_path = 'Texture/rogue.png'
atlas_key = 'rogue'
texture_json_path = 'Texture/rogue.json'

folder_name = 'SpaceRogue'
key_pattern = r'SpaceRogue/((rogue_\S+)_(\d{3})).png'

with open(texture_json_path, 'r') as json_file:
    data = json.load(json_file)

    data = data['frames']
    flipbook_key_before = ''
    flipbook = {
        'sprites': []
    }

    for key, value in data.items():
        match = re.match(key_pattern, key)
        if match:
            sprite_key = match.group(1)
            flipbook_key_now = match.group(2)
            frame_number = match.group(3)

            sprite_filename = f'{sprite_key}.sprite'
            sprite_folder = f'Sprite/{folder_name}/{flipbook_key_now}'
            sprite_path = f'{sprite_folder}/{sprite_filename}'

            # create sprite json
            if not os.path.exists(sprite_folder):
                os.makedirs(sprite_folder)
                print(f'directory {sprite_folder} has been created.')

            # add new file
            with open(sprite_path, 'w') as newfile:
                output = [
                    '[KEY]',
                    sprite_key,
                    '[PATH]',
                    sprite_path,
                    '[ATLAS_KEY]',
                    atlas_key,
                    '[ATLAS_PATH]',
                    atlas_path,
                    '[LEFT_TOP]',
                    f"{value['frame']['x']}, {value['frame']['y']}",
                    '[SLICE]',
                    f"{value['frame']['w']}, {value['frame']['h']}",
                    '[OFFSET]',
                    '0, 0'
                ]
                newfile.write('\n'.join(output) + '\n')
                print(f'filename \'{sprite_filename}\' has been written')
                print('\n'.join(output) + '\n')

            if flipbook_key_now != flipbook_key_before != '':
                flipbook_key = flipbook_key_before
                flipbook_folder = f'Flipbook/{folder_name}'
                flipbook_filename = f'{flipbook_key_before}.flip'
                flipbook_path = f'{flipbook_folder}/{flipbook_filename}'
                if not os.path.exists(flipbook_folder):
                    os.makedirs(f'{flipbook_folder}')
                    print(f'directory {flipbook_folder}has been created.')

                with open(flipbook_path, 'w') as newfile:
                    output = [
                        '[KEY]',
                        flipbook_key,
                        '[PATH]',
                        flipbook_path,
                        '[SPRITE_COUNT]',
                        str(len(flipbook['sprites'])),
                    ]
                    for idx, item in enumerate(flipbook['sprites']):
                        output.extend([
                            '[INDEX]',
                            str(idx),
                            '[KEY]',
                            item['key'],
                            '[PATH]',
                            item['path'],
                            '\n'
                        ])

                    print('\n'.join(output) + '\n', file=newfile)
                    print(f'filename {flipbook_key}.json has been written')

                # then empty the flipbook
                flipbook['sprites'] = []

            # add frame
            flipbook['sprites'].append({'key': sprite_key, 'path': f'{sprite_folder}/{sprite_filename}'})
            flipbook_key_before = flipbook_key_now
