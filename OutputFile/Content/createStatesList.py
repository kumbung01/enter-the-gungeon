import json
import re
from pprint import pprint
import os

atlas_key = 'BulletMan'
flipbook_path = f'Flipbook\\\\{atlas_key}'

file_list = os.listdir(flipbook_path)

for filename in file_list:
    key = filename.removesuffix('.flip')
    state = key.upper()
    filepath = f"{flipbook_path}\\\\{filename}"

    print(f'm_flipbookPlayer->AddFlipbook({state}, CAssetMgr::GetInst()->LoadFlipbook(L\"{key}\", L\"{filepath}\"));')

print("\n\n")

for filename in file_list:
    key = filename.removesuffix('.flip')
    state = key.upper()

    print(f"{state},")