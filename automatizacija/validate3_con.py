#!/usr/bin/python3
"""Upotreba ./validate3_con.py test/*.con*"""

import string


def check(lines):
	nl = []   # ispravno formatirane linije
	E = "\n"  # line ending
	
	n, k = map(int, lines[0].split())
	A = list(map(int, lines[1].split()))
	B = list(map(int, lines[2].split()))
	
	nl.append('{} {}{}'.format(n, k, E))
	nl.append(' '.join(map(str, A)) + '\n')
	nl.append(' '.join(map(str, B)) + '\n')
	consecutive = 1
	for i in range(k - 1):
		assert A[i] < A[i + 1], "a nije rastuci"
		assert B[i] < B[i + 1], "b nije rastuci"
		
		if A[i] + 1 != A[i + 1] or B[i] + 1 != B[i + 1]:
			consecutive = 0
	for i in range(k):
		assert 1 <= A[i] <= n
		assert 1 <= B[i] <= n
	
	assert lines == nl, "Krivi format (%s vs %s)" % (lines, nl)
	assert lines[-1][-1] == "\n", "Zadnji red ne zavrsava sa \\n"
	return {'n': n, 'k': k, 'max': max(max(A), max(B)), 'consecutive': consecutive}

# Ocekivani clusteri! Ovo vjerojatno zelis promijeniti!
expected_clusters = {'s1': 1, 's2': 1, 's3' : 1, 's4' : 1, 's5' : 1, 's6' : 1}

def what_cluster(data):
	# na temelju povratne informacije iz check(lines)
	# zakljucuje za TP u kojoj je bodovnoj sekciji
	where = []
	
	if data['consecutive']:
		where += ['s1']
	if data['n'] % 2 == 0 and data['max'] <= data['n'] // 2:
		where += ['s2']
	if data['n'] <= 4:
		where += ['s3']
	if data['n'] == 14 and data['k'] == 2:
		where += ['s4']
	if data['max'] < data['n']:
		where += ['s5']
	where += ['s6']
	
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
            print("{} (con): ".format(filename), end="")
            try:
                lines = open(filename).readlines()
                summary = check(lines)
                c = what_cluster(summary)
                if not 'dummy' in filename:
                    s = int(filename[-3])
                    assert ("s" + str(s)) in c, "primjer ne pripada subtasku"
                    
                if 'dummy' not in batch[0]:
                    bc[-1].append(c)
            except Exception as e:
                print("Greska!", e)
                raise
            else:
                print("Sve ok! (cluster {}, summary = {})".format(c, summary))

