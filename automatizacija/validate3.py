#!/usr/bin/python3
"""Usage:
  ./validate3.py [--actor2] test/*.in*
  When --actor2 is specified, the script validates actor2 input files (*.a2in*)
  and removes them after successful validation. Without --actor2, it validates
  actor1 test files (*.in*) and checks subtask membership.
"""

import os
import sys
import glob
import argparse
import string
import math

# ############## Task-specific validation logic ##############

def check(lines, mode):
    nl = []   # correctly formatted lines
    E = "\n"  # line ending
    
    p = int(lines[0])
    
    if mode == 'actor1':
    	assert p == 1, "krivi p"
    if mode == 'actor2':
    	assert p == 2, "krivi p"
    
    n, k = map(int, lines[1].split())
    A = list(map(int, lines[2].split()))
    
    nl.append(f"{p}{E}")
    nl.append(f"{n} {k}{E}")
    nl.append(' '.join(map(str, A)) + E)
    
    consecutive = 1
    for i in range(k - 1):
        assert A[i] < A[i + 1], "a nije rastuci"
        if A[i] + 1 != A[i + 1]:
            consecutive = 0
    for ai in A:
        assert 1 <= ai <= n, "element out of range"
    
    T = int(lines[3])
    assert len(lines) == T + 4, "krivi broj linija"
    nl.append(f"{T}{E}")
    
    S = set()
    for i in range(4, len(lines)):
        state = lines[i].rstrip(E)
        assert len(state) == n, "kriva duljina"
        balance = 0
        for c in state:
            assert c in ".PC", "krivi state"
            if c == 'P': balance += 1
            if c == 'C': balance -= 1
        assert balance == p - 1, "nije tocan broj crvenih i plavih"
        S.add(state)
        nl.append(f"{state}{E}")
    
    total = 0
    for i in range(0, n + 1):
        if i % 2 == 0 and mode == 'actor1':
            current = math.comb(n, i) * math.comb(i, i // 2)
            total += current
        if i % 2 == 1 and mode == 'actor2':
        	current = math.comb(n, i) * math.comb(i, i // 2)
        	total += current
    assert len(S) == total, "u inputu nisu svi stateovi"
    
    assert lines == nl, f"Krivi format ({lines} vs {nl})"
    assert lines[-1].endswith("\n"), "Zadnji red ne zavrsava sa \\n"
    return {'n': n, 'k': k, 'max': max(A), 'consecutive': consecutive}

# Expected clusters by subtask
expected_clusters = {'s1': 1, 's2': 1, 's3': 1, 's4': 1, 's5': 1, 's6': 1}

def what_cluster(data):
    where = []
    if data['consecutive']:
        where.append('s1')
    if data['n'] % 2 == 0 and data['max'] <= data['n'] // 2:
        where.append('s2')
    if data['n'] <= 4:
        where.append('s3')
    if data['n'] == 14 and data['k'] == 2:
        where.append('s4')
    if data['max'] < data['n']:
        where.append('s5')
    where.append('s6')
    return where


# ############## Batch grouping ##############

def group_in_batches(files):
    files.sort()
    B = []
    for f in files:
        if not B or 'dummy' in f:
            B.append([f])
            continue
        prev = B[-1][-1]
        # compare last alpha char grouping
        i = -1
        while i >= -len(f) and f[i].isalpha(): i -= 1
        j = -1
        while j >= -len(prev) and prev[j].isalpha(): j -= 1
        if i < -len(f) or j < -len(prev) or prev[j] != f[i]:
            B.append([f])
        else:
            B[-1].append(f)
    return B


def main():
    parser = argparse.ArgumentParser(description="Validate test data for actor1 or actor2 input files")
    parser.add_argument('--actor2', action='store_true', help='Validate actor2 input files (*.a2in*) and remove them after validation')
    parser.add_argument('patterns', nargs='+', help='File patterns to validate, e.g. test/*.in* or test/*.a2in*')
    args = parser.parse_args()

    # Collect matching files
    files = []
    for pattern in args.patterns:
        files.extend(glob.glob(pattern))
    if not files:
        print(f"No files found for patterns: {args.patterns}")
        sys.exit(1)

    # Process in batches
    batches = group_in_batches(files)
    logs = []
    for batch in batches:
        is_dummy = 'dummy' in batch[0]
        if not is_dummy and not args.actor2:
            logs.append([])
        for filename in batch:
            mode = 'actor2' if args.actor2 or filename.endswith('.a2in') else 'actor1'
            print(f"{filename} ({mode}): ", end='')
            try:
                lines = open(filename).readlines()
                summary = check(lines, mode)
                clusters = what_cluster(summary)
                # For actor1, ensure file-named subtask membership
                if mode == 'actor1' and not is_dummy:
                    sub = f"s{filename[-3]}"
                    assert sub in clusters, f"Example {filename} not in expected subtask {sub}"
                # Record cluster info for actor1 batches
                if mode == 'actor1' and not is_dummy:
                    logs[-1].append(clusters)
            except Exception as e:
                print("Error!", e)
                raise
            else:
                print(f"All ok! (clusters={clusters}, summary={summary})")
                # Remove actor2 files after validation
                if mode == 'actor2':
                    os.remove(filename)
    
if __name__ == "__main__":
    main()

