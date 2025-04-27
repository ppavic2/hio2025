#!/usr/bin/python3
"""Upotreba ./validate3.py test/*.in*"""

import string


def check(lines):
    nl = []   # ispravno formatirane linije
    E = "\n"  # line ending
    
    n, m = map(int, lines[0].strip().split())    
    nl.append('{} {}{}'.format(n, m, E))  
    print(n, m)
    assert 1 <= n <= 100000, "krivi n"
    assert 1 <= m <= 100000, "krivi m"
    
    assert len(lines) == n + m + 1, "krivi broj linija"
    
    bio = set()

    for i in range(n):
        pos, power = map(int, lines[i + 1].strip().split())
        assert 1 <= pos <= 10 ** 9, "pozicija zeca van granica " + str(pos)
        assert 1 <= power <= 10 ** 9, "power zeca van granica " + str(power)
        bio.add(pos)
        nl.append('{} {}{}'.format(pos, power, E))
    
    for i in range(m):
        pos, power = map(int, lines[n + i + 1].strip().split())
        assert 1 <= pos <= 10 ** 9, "pozicija mrkve van granica " + str(pos)
        assert 0 <= power <= 10 ** 9, "power mrkve van granica " + str(power)
        bio.add(pos)
        nl.append('{} {}{}'.format(pos, power, E))

    assert len(bio) == n + m, "nisu svi razliciti"
    
    assert lines == nl, "Krivi format (%s vs %s)" % (lines, nl)
    assert lines[-1][-1] == "\n", "Zadnji red ne zavrsava sa \\n"
    return {'n' : n, 'm' : m} 

# Ocekivani clusteri! Ovo vjerojatno zelis promijeniti!
expected_clusters = {'s1': 1, 's2' : 1, 's3' : 1, 's4' : 1, 's5' : 1}


def what_cluster(data):
    # na temelju povratne informacije iz check(lines)
    # zakljucuje za TP u kojoj je bodovnoj sekciji
    where = ['s5']
    if data['n'] == 1: where += ['s1']
    if data['m'] == 1: where += ['s2']
    if data['n'] <= 1000 and data['m'] <= 1000: where += ['s3']
    if data['n'] <= 50000 and data['m'] <= 50000: where += ['s4']
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
