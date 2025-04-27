#!/usr/bin/python3
"""Upotreba ./validate3.py test/*.in*"""

import string


def check(lines):
    nl = []   # ispravno formatirane linije
    E = "\n"  # line ending
    
    n, q = map(int, lines[0].strip().split())
    nl.append('{} {}{}'.format(n, q, E))  
    
    assert 3 <= n <= 200000, "krivi n"
    assert 0 <= q <= 200000, "krivi q"
    
    assert len(lines) == 2 + q, "krivi broj linija"
    
    A = list(map(int, lines[1].strip().split()))
    nl.append(" ".join([str(x) for x in A]) + E)
    
    assert(len(A) == n)
 
    for i in range(n):
    	assert 0 <= A[i] <= 654200
    
    delta = 0
    
    for i in range(q):
    	pos, val = map(int, lines[2 + i].strip().split())
    	assert 1 <= pos <= n, "kriva pozicija"
    	assert 0 <= val <= 654200, "kriva visina"
    	nl.append("{} {}{}".format(pos, val, E))
    	delta = max(delta, abs(A[pos - 1] - val));
    	A[pos - 1] = val
    
    assert lines == nl, "Krivi format (%s vs %s)" % (lines, nl)
    assert lines[-1][-1] == "\n", "Zadnji red ne zavrsava sa \\n"
    return {'n' : n, 'q' : q, 'max_value' : max(A), "delta" : delta} 

# Ocekivani clusteri! Ovo vjerojatno zelis promijeniti!
expected_clusters = {'s1': 1, 's2' : 1, 's3' : 1, 's4' : 1, 's5' : 1}


def what_cluster(data):
    # na temelju povratne informacije iz check(lines)
    # zakljucuje za TP u kojoj je bodovnoj sekciji
    where = ['s4']
    if data['q'] == 0 and data['n'] <= 300 and data['max_value'] <= 300: where += ['s1']
    if data['q'] == 0: where += ['s2']
    if data['delta'] <= 1: where += ['s3']
    return where;


################### Zadatak-specifican kod iznad ove linije #########################

import sys
import glob
import hashlib


def group_in_batches(files):
    # mnozenje.in.1a, mnozenje.in.1b sprema u isti batch

    files.sort()
    B = []
    for f in files:
        if len(B) == 0:
            B.append([f])            
            continue
        if "dummy" in f:
            B.append([f])
            continue
        s = f
        i = -1
        while s[i].isalpha():
            i -= 1
        ss = B[-1][-1]
        j = -1
        while ss[j].isalpha():
            j -= 1
        if ss[j] == s[i]:
            B[-1].append(f)
        else:
            B.append([f])
    return B


if __name__ == "__main__":
    f = []
    for pattern in sys.argv[1:]:
        for filename in glob.glob(pattern):
            f.append(filename)

    bc = []
    for batch in group_in_batches(f):
        if 'dummy' not in batch[0]:
            bc.append([])
        for filename in batch:
            print("{}: ".format(filename), end="")
            try:
                lines = open(filename).readlines()
                summary = check(lines)
                c = what_cluster(summary)
                if not 'dummy' in filename:
                    i = -1
                    while filename[i].isalpha(): i -= 1
                    s = int(filename[i])
                    assert ("s" + str(s)) in c, "primjer ne pripada subtasku"
                    
                if 'dummy' not in batch[0]:
                    bc[-1].append(c)
            except Exception as e:
                print("Greska! (summary = {})".format(summary), e)
                raise
            else:
                print("Sve ok! (cluster {}, summary = {})".format(c, summary))


# Bolji validator! - ppavic, 2023
