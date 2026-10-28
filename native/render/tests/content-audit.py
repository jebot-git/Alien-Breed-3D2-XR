#!/usr/bin/env python3
"""Audit all retail placements/mechanisms against original binary tables.

content-audit.py ASSETS ORIGINAL_LEVELS [REPORT.json]
Original levels are local, uncompressed medias/original/levels/LEVEL_A..P.
No data is changed. This checks content preservation, not a campaign playthrough.
"""
from collections import Counter
import hashlib
import json
from pathlib import Path
import struct
import sys

assets, original = map(Path, sys.argv[1:3])
word = lambda b, p: struct.unpack_from('>h', b, p)[0]
long = lambda b, p: struct.unpack_from('>i', b, p)[0]
glf = json.loads((assets / 'glf.json').read_text())
report, totals = [], Counter()

def mechanisms(graph, offset, expected):
    records, patch_count = [], 0
    while word(graph, offset) != 999:
        assert len(records) < 500
        fields = {'bottom': 0, 'top': 2, 'openingSpeed': 4, 'closingSpeed': 6,
                  'openDuration': 8, 'x': 18, 'z': 20, 'zone': 30}
        value = {key: word(graph, offset+at) for key, at in fields.items()}
        value.update(openBits=graph[offset+34], closeBits=graph[offset+35])
        patches, at = [], offset+36
        while word(graph, at) >= 0:
            patches.append({'edge': word(graph, at), 'gfxOfs': long(graph, at+2),
                            'yBase': long(graph, at+6)})
            at += 10
        exported = expected[len(records)]
        for key, v in value.items():
            assert exported[key] == v, (key, exported[key], v)
        assert exported['wallPatches'] == patches
        patch_count += len(patches)
        records.append(value)
        offset = at+2
    assert len(records) == len(expected)
    return records, patch_count

for index in range(16):
    letter = chr(65+index)
    folder = original / f'LEVEL_{letter}'
    binary = (folder / 'twolev.bin').read_bytes()
    graph = (folder / 'twolev.graph.bin').read_bytes()
    scene = json.loads((assets / 'levels' / f'{letter.lower()}.json').read_text())
    ram = (assets / 'native' / f'level-{index}.ram').read_bytes()
    reference = assets.parent / 'artifacts/native-oracle' / f'level-{index}.ram'
    points, object_points = long(binary, 1622), long(binary, 1642)
    last_point, last_object_point = word(binary, 1614), word(binary, 1620)
    assert len(scene['points']) == last_point
    for i, p in enumerate(scene['points']):
        assert (p['x'], p['z']) == (word(binary, points+i*4), word(binary, points+i*4+2))
    tail = [word(binary, points+last_point*4), word(binary, points+last_point*4+2)]
    assert points+(last_point+1)*4 == long(ram, 105236)-long(ram, 49984)
    walls = [(w['leftPt'], w['rightPt']) for w in scene['walls']]
    assert all(0 <= a <= last_point and 0 <= b <= last_point for a, b in walls)
    count, offset, counts = 0, long(binary, 1630), Counter()
    placed, boot_changes, lock_holders, messages = [], [], 0, 0
    boot_records, boot_points = long(ram, 50012), long(ram, 50008)
    while word(binary, offset) >= 0:
        assert count < 2000
        cid, kind, definition = word(binary, offset), binary[offset+16], binary[offset+54]
        assert 0 <= cid <= last_object_point
        value = {'x': word(binary, object_points+cid*8), 'z': word(binary, object_points+cid*8+4),
                 'zone': word(binary, offset+12), 'typeId': kind, 'def': definition,
                 'doorsHeld': long(binary, offset+50), 'bright': word(binary, offset+2),
                 'upperZone': binary[offset+63] != 0, 'displayText': word(binary, offset+24)}
        expected = scene['objects'][count]
        assert all(expected[key] == v for key, v in value.items()), (letter, count, value, expected)
        if 'angle' in expected:
            assert expected['angle'] == word(binary, offset+30) & 65535
        if kind == 0:
            counts['enemies'] += 1
        elif kind == 1:
            category = {0: 'collectables', 1: 'activatables', 2: 'destructibles', 3: 'decorations'}[glf['objects'][definition]['type']]
            counts[category] += 1
            lock_holders += value['doorsHeld'] != 0
            messages += value['displayText'] >= 0
        elif kind == 2:
            counts['reserved_projectiles'] += 1
        elif kind == 3:
            counts['auxiliary'] += 1
        else:
            counts['player_weapon_slots'] += 1
        # The renderer reads the authoritative original runtime record, not
        # exported static x/z. Record all original startup/AI changes explicitly.
        at = boot_records+count*64
        boot_cid = word(ram, at)
        if (value['x'], value['z'], value['zone'], kind, definition) != (
                word(ram, boot_points+boot_cid*8), word(ram, boot_points+boot_cid*8+4),
                word(ram, at+12), ram[at+16], ram[at+54]):
            boot_changes.append(count)
        if reference.exists():
            ref = reference.read_bytes() if count == 0 else ref
            assert ram[at:at+64] == ref[at:at+64]
            assert ram[boot_points+boot_cid*8:boot_points+boot_cid*8+8] == ref[boot_points+boot_cid*8:boot_points+boot_cid*8+8]
        placed.append(value)
        offset += 64
        count += 1
    assert count == len(scene['objects'])
    doors, door_patches = mechanisms(graph, long(graph, 0), scene['doors'])
    lifts, lift_patches = mechanisms(graph, long(graph, 4), scene['lifts'])
    switches = long(graph, 8)
    active_switches = [i for i in range(8) if word(graph, switches+i*14) >= 0]
    exit_zone = word(binary, long(binary, 1626)-2)
    assert exit_zone == scene['exitZone'] and 0 <= exit_zone < scene['numZones']
    teleports = [z['id'] for z in scene['zones'] if z['telZone'] >= 0]
    assert all(z['telZone'] < scene['numZones'] for z in scene['zones'] if z['telZone'] >= 0)
    counts.update(records=count, doors=len(doors), lifts=len(lifts), wall_patches=door_patches+lift_patches,
                  exits=1, lock_holders=lock_holders, message_items=messages,
                  legacy_switches=len(active_switches), teleport_zones=len(teleports))
    totals.update(counts)
    report.append({'level': index+1, 'counts': dict(counts), 'point_highest_index': last_point,
                   'reserved_point_tail': tail, 'reserved_point_references': sum(last_point in pair for pair in walls),
                   'object_point_highest_index': last_object_point, 'original_startup_changed_record_indices': boot_changes,
                   'original_sha256': hashlib.sha256(binary+graph).hexdigest(),
                   'placements_sha256': hashlib.sha256(json.dumps(placed, sort_keys=True).encode()).hexdigest(),
                   'mechanisms': {'doors': doors, 'lifts': lifts, 'legacy_switch_slots': active_switches,
                                  'exit_zone': exit_zone, 'teleport_zones': teleports}})
    print(f'{index+1:2}: {count:3} records, {counts["enemies"]:2} enemies, {counts["collectables"]:3} collectables, '
          f'{counts["activatables"]:2} activatables, {len(doors):2} doors, {len(lifts):2} lifts; original tables exact')
result = {'source': 'mheyer32/alienbreed3d2@86abb5c; local original retail binaries',
          'totals': dict(totals), 'levels': report,
          'limits': 'Content preservation only; no complete campaign/secret-route playthrough. Reserved invisible frames and source startup/AI changes are retained.'}
if len(sys.argv) > 3:
    Path(sys.argv[3]).write_text(json.dumps(result, indent=2)+'\n')
print('TOTAL', json.dumps(dict(totals), sort_keys=True))
