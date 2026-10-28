#!/usr/bin/env python3
"""Execute actual original .sum_brights_loop instructions, including CCR V.

Usage: lighting-asm-check.py ab3d2_source/objdrawhires.s assembly-pairs
lighting-check.cpp emits pre-combine/result pairs with its optional last arg.
This is a small test-only interpreter, not an application/runtime dependency.
"""
from pathlib import Path
import re
import sys

source = Path(sys.argv[1]).read_text()
block = source[source.index('.sum_brights_loop:'):]
block = block[:block.index('\n\t\t\t\trts')]
instructions, labels = [], {}
for line in block.splitlines():
    line = line.split(';')[0].strip().lower()
    if not line:
        continue
    if line.endswith(':'):
        labels[line[:-1]] = len(instructions)
    else:
        operation, _, operands = line.partition('\t')
        if not operands:
            operation, operands = line.split(None, 1)
        instructions.append((operation, [x.strip() for x in operands.split(',')]))

def signed(value, bits):
    value &= (1 << bits) - 1
    return value - (1 << bits) if value & (1 << (bits - 1)) else value

def execute(raw):
    memory, registers, address = bytearray(raw), [15, 0, 0, 0, 0, 0, 0, 0], 0
    n = z = v = False
    def read(operand, bits):
        if operand.startswith('#'):
            return int(operand[1:])
        if operand.startswith('d'):
            return registers[int(operand[1:])] & ((1 << bits) - 1)
        offset = operand.split('(a0)')[0]
        return memory[address + (int(offset) if offset else 0)]
    def write(operand, value, bits):
        nonlocal address
        mask = (1 << bits) - 1
        if operand.startswith('d'):
            index = int(operand[1:])
            registers[index] = (registers[index] & ~mask) | (value & mask)
        else:
            offset = operand.split('(a0)')[0]
            memory[address + (int(offset) if offset else 0)] = value & 255
            if operand.endswith('+'):
                address += 1
    pc = steps = 0
    while pc < len(instructions):
        steps += 1
        if steps > 1000:
            raise RuntimeError('Assembly loop failed to terminate')
        op, args = instructions[pc]
        pc += 1
        if op == 'ble.s':
            if z or n != v:
                pc = labels[args[0]]
            continue
        if op == 'dbra':
            value = (read(args[0], 16) - 1) & 65535
            write(args[0], value, 16)
            if value != 65535:
                pc = labels[args[1]]
            continue
        bits = 32 if op == 'moveq' else {'b': 8, 'w': 16}[op.split('.')[-1]]
        operation = op.split('.')[0]
        mask, sign = (1 << bits) - 1, 1 << (bits - 1)
        if operation in ('moveq', 'move'):
            result = read(args[0], bits)
            write(args[1], result, bits)
            v = False
        elif operation == 'neg':
            value = read(args[0], bits)
            result = -value
            write(args[0], result, bits)
            v = value == sign
        elif operation in ('add', 'sub'):
            a, b = read(args[1], bits), read(args[0], bits)
            result = a + b if operation == 'add' else a - b
            write(args[1], result, bits)
            v = bool((~(a ^ b) if operation == 'add' else a ^ b) & (a ^ result) & sign)
        elif operation == 'asr':
            result = signed(read(args[1], bits), bits) >> read(args[0], bits)
            write(args[1], result, bits)
            v = False
        else:
            raise RuntimeError(f'Unimplemented assembly instruction {op}')
        n, z = bool(result & sign), (result & mask) == 0
    return memory

data = Path(sys.argv[2]).read_bytes()
assert len(data) % 128 == 0
changed, cases = 0, len(data) // 128
for i in range(cases):
    raw, actual = data[i*128:i*128+64], data[i*128+64:(i+1)*128]
    expected = execute(raw)
    assert expected == actual, f'Assembly mismatch at original position {i}'
    legacy = bytearray(raw)
    for sector in range(16):
        for height in (0, 16):
            limit = (48 - signed(raw[32+height+sector], 8)) >> 1
            difference = signed(limit - signed(raw[height+sector], 8), 8)
            legacy[height+sector] = -min(0, difference) & 255
    changed += legacy != actual

# Exhaust every possible byte pair, including overflow/empty marker cases
# absent from ordinary starting scenes. One sector suffices; the ASM runs all.
for neighbor in range(256):
    for center in range(256):
        raw = bytes([center]*32 + [neighbor]*32)
        actual = execute(raw)
        limit = (48-neighbor) >> 1
        expected = ((signed(center, 8)-limit) & 255) if signed(center, 8) >= limit else 0
        assert actual[:32] == bytes([expected]*32), (neighbor, center)
print(f'PASS actual original assembly: {cases} retail positions, 65,536 exhaustive byte pairs; {changed} positions differ from signed intermediary')
