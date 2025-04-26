#!/usr/bin/python3

import sys
import glob
import os
import random
import subprocess
import math

PROBLEM = "automatizacija"
sys.setrecursionlimit(1000010)

N = 16

class Test(object):
	def __init__(self, n, a, b):
		self.n = n
		self.k = len(a)
		self.a = a
		self.b = b

	def validate(self):
		assert 2 <= self.n <= N, "neispravan n"
		assert 1 <= self.k <= self.n, "neispravan k"
		assert len(self.a) == self.k, "neispravna duljina a"
		assert len(self.b) == self.k, "neispravna duljina b"
		for i in range(self.k):
			assert 1 <= self.a[i] <= self.n, "neispravan a"
			assert 1 <= self.b[i] <= self.n, "neispravan b"
			if i:
				assert self.a[i - 1] < self.a[i], "a nije rastuci"
				assert self.b[i - 1] < self.b[i], "b nije rastuci"

	def write(self, fd=sys.stdout):
		print(self.n, self.k, file=fd)
		for i in range(self.k):
			print(self.a[i], end = " \n"[i == self.k - 1], file=fd)
		for i in range(self.k):
			print(self.b[i], end = " \n"[i == self.k - 1], file=fd)
		

def remove_cases():
	cases = glob.glob('test/%s.dummy.in.*' % PROBLEM)
	cases += glob.glob('test/%s.dummy.out.*' % PROBLEM)
	cases += glob.glob('test/%s.con.*' % PROBLEM)
	cases += glob.glob('test/%s.in.*' % PROBLEM)
	cases += glob.glob('test/%s.out.*' % PROBLEM)
	for c in cases:
		print('Removing ' + c, file=sys.stderr)
		os.remove(c)

def _sequence(l, r, c):
	ret = random.sample(range(l, r + 1), c)
	return sorted(ret)

def gen_consecutive(n, k, x, y):
	a = [i for i in range(x, x + k)]
	b = [i for i in range(y, y + k)]
	assert len(b) == k
	return Test(n, a, b)

def gen_first_half(n, k):
	a = _sequence(1, n//2, k)
	b = _sequence(1, n//2, k)
	return Test(n, a, b)

def gen_less_n(n, k):
	a = _sequence(1, n - 1, k)
	b = _sequence(1, n - 1, k)
	return Test(n, a, b)

def gen_exclude(n, l, r):
	k = (r - l + 1) // 2
	assert k <= r - l + 1
	a = _sequence(l, r, k)
	b = []
	for i in range(l, r + 1):
		if i not in a:
			b.append(i)
	return Test(n, a, b)

def gen(n, k):
	a = _sequence(1, n, k)
	b = _sequence(1, n, k)
	return Test(n, a, b)

def gen_cases():
	remove_cases()
	
	dummy = [] # Nista
	
	subtask1 = [] # uzastopni skupovi
	subtask2 = [] # N paran, a_i, b_i <= N/2
	subtask3 = [] # N <= 4
	subtask4 = [] # K = 2, N = 14
	subtask5 = [] # svi brojevi < N
	subtask6 = [] # NDO
	
	for n, k, x, y in [
		[2, 2, 1, 1],
		[3, 2, 1, 2],
		[6, 1, 6, 2],
		[6, 4, 3, 2],
		[11, 7, 2, 4],
		[12, 4, 7, 7],
		[13, 3, 3, 5],
		[13, 12, 1, 2],
		[13, 1, 13, 1],
		[14, 7, 1, 8],
		[14, 7, 2, 8],
		[14, 10, 5, 3],
		[16, 16, 1, 1],
		[16, 1, 16, 16]
	]:
		subtask1.append(gen_consecutive(n, k, x, y))
	
	for n, k in [
		[2, 1],
		[4, 1],
		[6, 2],
		[8, 2], [8, 2], [8, 2], [8, 2], [8, 3],
		[10, 1], [10, 2], [10, 2], [10, 3], [10, 3], [10, 5],
		[14, 2], [14, 3], [14, 4], [14, 4], [14, 4], [14, 4], [14, 5], [14, 5], [14, 6], [14, 6], [14, 7],
		[16, 1], [16, 8]
	]:
		subtask2.append(gen_first_half(n, k))
	subtask2.append(gen_consecutive(12, 3, 1, 4))

	subtask3.append(Test(3, [1, 2], [2, 3]))
	subtask3.append(Test(3, [2, 3], [1, 2]))
	subtask3.append(Test(3, [1, 3], [1, 3]))
	subtask3.append(Test(2, [1], [2]))
	subtask3.append(Test(2, [2], [2]))
	
	for a, b in [
		[[1], [2]], [[4], [4]],
		[[1, 2, 4], [1, 3, 4]], [[2, 3, 4], [2, 3, 4]], [[2, 3, 4], [1, 2, 3]], [[1, 2, 3], [2, 3, 4]],
		[[1, 2, 3, 4], [1, 2, 3, 4]],
		[[1, 2], [1, 3]], [[1, 3], [1, 2]], [[1, 3], [2, 4]], [[1, 3], [3, 4]],
		[[1, 4], [2, 3]], [[1, 4], [1, 3]], [[1, 4], [2, 4]], [[1, 4], [1, 4]],
		[[2, 3], [1, 4]], [[2, 4], [1, 3]], [[2, 4], [3, 4]], [[2, 4], [2, 4]],
		[[3, 4], [3, 4]], [[3, 4], [1, 4]], [[3, 4], [2, 3]]
	]:
		subtask3.append(Test(4, a, b))
	
	
	S = set()
	for x, y in [
		[[1, 2], [1, 2]], [[5, 9], [8, 14]], [[4, 11], [3, 4]], [[9, 14], [9, 13]], [[10, 12], [11, 13]],
		[[11, 13], [10, 12]], [[10, 11], [12, 13]], [[12, 13], [10, 11]], [[6, 14], [6, 14]], [[5, 7], [1, 5]],
		[[5, 7], [4, 7]], [[6, 13], [7, 13]], [[1, 14], [1, 14]], [[13, 14], [13, 14]]
	]:
		S.add((tuple(x), tuple(y)))
		subtask4.append(Test(14, x, y))
	
	S = set()
	while len(S) < 30:
		x = [random.randint(1, 14), random.randint(1, 14)]
		y = [random.randint(1, 14), random.randint(1, 14)]
		if x[0] == x[1] or y[0] == y[1]:
			continue
		x.sort()
		y.sort()
		pair = (tuple(x), tuple(y))
		if pair not in S:
			S.add(pair)
			subtask4.append(Test(14, x, y))
	
	for i in range(2):
		subtask5.append(gen_less_n(3, i + 1))
	for i in range(12):
		subtask5.append(gen_less_n(11, random.randint(3, 8)))
		subtask5.append(gen_less_n(12, random.randint(4, 8)))
	for i in range(7):
		subtask5.append(gen_less_n(12, i // 3 + 1))
		subtask5.append(gen_less_n(12, 12 - i // 3 - 1))
	for i in range(3):
		subtask5.append(gen_exclude(11, 1, 10))
	subtask5.append(gen_exclude(11, 5, 8))
	subtask5.append(Test(11, [9, 10], [1, 10]))
	subtask5.append(gen_consecutive(11, 5, 1, 6))
	subtask5.append(gen_consecutive(11, 5, 6, 1))
	subtask5.append(gen_consecutive(16, 14, 1, 2))
	subtask5.append(Test(16, [15], [15]))
	subtask5.append(Test(11, [1, 3, 5, 7, 9], [2, 4, 6, 8, 10]))
	subtask5.append(Test(11, [2, 4, 6, 8, 10], [1, 3, 5, 7, 9]))
	
	for i in range(3):
		subtask6.append(gen(3, i + 1))
	for i in range(10):
		subtask6.append(gen(11, random.randint(3, 8)))
		subtask6.append(gen(12, random.randint(4, 8)))
	for i in range(5):
		subtask6.append(gen(11, i // 2 + 1))
		subtask6.append(gen(11, 11 - i // 2 - 1))
		subtask6.append(gen(12, i // 2 + 1))
		subtask6.append(gen(12, 12 - i // 2 - 1))
	for i in range(3):
		subtask6.append(gen_exclude(11, 1, 10))
	for i in range(6):
		subtask6.append(gen_exclude(12, 1, 12))
	subtask6.append(gen_consecutive(12, 6, 1, 7))
	subtask6.append(gen_consecutive(12, 6, 6, 1))
	subtask6.append(gen_consecutive(13, 12, 1, 2))
	subtask6.append(Test(16, [16], [16]))
	subtask6.append(gen_consecutive(16, 16, 1, 1))
	subtask6.append(Test(16, [1], [16]))
	subtask6.append(Test(16, [1, 3, 5, 7, 9, 11, 13, 15], [2, 4, 6, 8, 10, 12, 14, 16]))
	subtask6.append(Test(16, [2, 4, 6, 8, 10, 12, 14, 16], [1, 3, 5, 7, 9, 11, 13, 15]))

	real = [
		subtask1,
		subtask2,
		subtask3,
		subtask4,
		subtask5,
		subtask6
	]

#	for i, test in enumerate(dummy):
#		test.validate()
#		filename = f"test/{PROBLEM}.dummy.in.{i+1}"
#		print(f'Generating {filename}', file=sys.stderr)
#		with open(filename, 'wt+') as fp:
#			test.write(fp)

	for i, batch in enumerate(real):
		for j, test in enumerate(batch):
			test.validate()
			filename = f"test/{PROBLEM}.con.{i+1}{chr(ord('a')+j//26)}{chr(ord('a')+j%26)}"
			print(f'Generating {filename}', file=sys.stderr)
			with open(filename, 'wt+') as fp:
				test.write(fp)

	for con_file in glob.glob("test/*.con.*"):
		in_file = con_file.replace(".con.", ".in.")
		
		print(f"Processing {con_file} -> {in_file}")

		with open(con_file, 'r') as fin, open(in_file, 'w') as fout:
			subprocess.run(["./create_input"], stdin=fin, stdout=fout, check=True)
	
	print("Subtask 1: ", len(subtask1), " tests")
	print("Subtask 2: ", len(subtask2), " tests")
	print("Subtask 3: ", len(subtask3), " tests")
	print("Subtask 4: ", len(subtask4), " tests")
	print("Subtask 5: ", len(subtask5), " tests")
	print("Subtask 6: ", len(subtask6), " tests")

def main():
	random.seed(8737497)
	gen_cases()

if __name__ == "__main__":
	main()

