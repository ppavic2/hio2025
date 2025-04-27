#!/usr/bin/python3
"""Upotreba ./validate3.py test/*.in*"""

import string
import sys

sys.setrecursionlimit(200000)

from collections import defaultdict

def classify_graph(nodes : int, edges : list[tuple[int,int]]) -> str:
    """
    Classify a connected undirected simple graph with given nodes and edges as one of:
    - 0: connected, no cycles (edges = nodes - 1)
    - 1: connected, at most one cycle (edges = nodes)
    - 2: connected, multiple cycles allowed, but each vertex participates in at most one cycle

    Returns:
    One of the strings: 0, 1, 2.
    If the graph doesn't fit any of these classes, raises ValueError.
    """
    # Build adjacency list
    graph: dict[int,list[int]] = defaultdict(list)
    for u, v in edges:
        if u == v:
            # Ignore self-loops in simple graph assumption
            continue
        graph[u].append(v)
        graph[v].append(u)

    # Special case: no nodes
    if nodes <= 0:
        return 0

    # Check connectivity
    visited = [False] * nodes
    # Start from a node with at least one edge, or 0 otherwise
    start = next((i for i in range(nodes) if graph[i]), 0)
    stack = [start]
    visited[start] = True
    while stack:
        u = stack.pop()
        for w in graph[u]:
            if not visited[w]:
                visited[w] = True
                stack.append(w)
    # Ensure all nodes with edges are visited, and isolated nodes (if any) count as disconnected
    if not all(visited[i] or not graph[i] for i in range(nodes)):
        raise ValueError("Graph is not connected")

    # Count edges excluding self-loops
    m = len([e for e in edges if e[0] != e[1]])
    cyclomatic = m - nodes + 1
    # Tree: no cycles
    if cyclomatic == 0:
        return 0
    # Function graph: at most one cycle
    if cyclomatic == 1:
        return 1

    # Potential vertex cactus: detect per-vertex cycle membership via DFS back-edges
    visited = [False] * nodes
    disc = [0] * nodes
    parent = [-1] * nodes
    time_counter = [0]
    membership = [0] * nodes

    def dfs(u: int) -> None:
        visited[u] = True
        disc[u] = time_counter[0]
        time_counter[0] += 1
        for w in graph[u]:
            if not visited[w]:
                parent[w] = u
                dfs(w)
            elif w != parent[u] and disc[w] < disc[u]:
                # Found a back edge u->w, record the cycle nodes from u up to w
                curr = u
                membership[curr] += 1
                while curr != w:
                    curr = parent[curr]
                    membership[curr] += 1

    dfs(start)
    # If each vertex is in at most one cycle, it's a vertex cactus
    if all(count <= 1 for count in membership):
        return 2

    # Falls outside all defined classes
    raise ValueError("Graph does not fit tree, function graph, or vertex cactus")

def check(lines):
    nl = []   # ispravno formatirane linije
    E = "\n"  # line ending
   
    T = int(lines[0].strip())
    nl.append("{}{}".format(T, E))
    
    start = 1
    
    suma = 0
    counts = [0, 0, 0]
    
    for _ in range(T): 
        n, m, a, b = map(int, lines[start].strip().split())    
        nl.append('{} {} {} {}{}'.format(n, m, a, b, E))  
        
        assert 1 <= n <= 200000, "krivi n"
        assert 1 <= m <= 300000, "krivi m"
        
        suma += n
    
        bio = set()

        for i in range(m):
            u, v = map(int, lines[start + i + 1].split())
            assert 1 <= u <= n, "krivi u"
            assert 1 <= v <= n, "krivi v"
            nl.append('{} {}{}'.format(u, v, E))
            u -= 1
            v -= 1
            assert u != v, "self loop"            
            assert(u, v) not in bio, "ponavljanje brida"
            bio.add((u, v))
        
        counts[classify_graph(n, list(bio))] += 1
        
        start += m + 1
    
    types = []
    
    if counts[0] > 0: types += [0]
    if counts[1] > 0: types += [1]
    if counts[2] > 0: types += [2]
    
    assert lines == nl, "Krivi format (%s vs %s)" % (lines, nl)
    assert lines[-1][-1] == "\n", "Zadnji red ne zavrsava sa \\n"
    return {'n' : suma,  'tip' : types} 

# Ocekivani clusteri! Ovo vjerojatno zelis promijeniti!
expected_clusters = {'s1': 1, 's2' : 1, 's3' : 1, 's4' : 1, 's5' : 1}


def what_cluster(data):
    # na temelju povratne informacije iz check(lines)
    # zakljucuje za TP u kojoj je bodovnoj sekciji
    where = ['s8']
    if data['n'] <= 300: where += ['s1']
    if data['n'] <= 5000 and data['tip'] == [0]: where += ['s2']
    if data['tip'] == [0]: where += ['s3']
    if data['n'] <= 5000 and data['tip'] == [1]: where += ['s4']
    if data['tip'] == [1]: where += ['s5', 's6']
    if data['n'] <= 5000: where += ['s7']
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
