#include<bits/stdc++.h>

#define pb push_back
#define x first
#define y second
#define all(a) (a).begin(), (a).end()

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;

int rand(int x, int y, mt19937& rng) {
	int r = rng();
	if(r < 0) r += INT_MAX;
	return x + r % (y - x + 1);
}

int n, seed;
int a[25];

void print() {
	printf("%d\n", n);
	for(int i = 0;i < n - 1;i++)
		printf("%d ", a[i]);
	printf("%d\n", a[n - 1]);
}

vector<int> p;
vector<vector<int>> partitions;
void rek(int sum, int x, int rem) {
	if(x == 0) {
		if(sum == 0) partitions.pb(p);
		return;
	}

	for(int i = 0;i * x <= sum;i++) {
		p.pb(rem + i);
		rek(sum - i * x, x - 1, rem + i);
		p.pop_back();
	}
}

int main(int argc, char** argv) {
	int type = atoi(argv[1]);

	if(type == 1) {
		//dummy tests
		int x = atoi(argv[2]);

		if(x == 1) printf("2\n2 0\n");
		if(x == 2) printf("2\n1 1\n");
		if(x == 3) printf("3\n2 0 2\n");
	}
	if(type == 2) {
		//random (large n)
		n = atoi(argv[2]);
		seed = atoi(argv[3]);
		mt19937 rng(seed);
		
		int sum = (1 << (n - 2)), rem = 0;
		for(int i = n;i > 1;i--) {
			int x = rand(0, sum / i, rng);
			rem += x;
			a[i - 1] = rem << 1;
			sum -= x * i;
		}
		rem += sum;
		a[0] = rem << 1;
		shuffle(a, a + n, rng);
		print();
	}
	if(type == 3) {
		//random2 (large n)
		n = atoi(argv[2]);
		seed = atoi(argv[3]);
		mt19937 rng(seed);
		
		int sum = (1 << (n - 2));
		for(int i = n;i > 1;i--) {
			int x = rand(0, sum, rng);
			a[i - 1] = x << 1;
			sum -= x;
		}
		a[0] = sum << 1;
		shuffle(a, a + n, rng);
		print();
	}
	if(type == 4) {
		//all (almost) equal
		n = atoi(argv[2]);
		
		int x = (1 << (n - 2)) / n;
		int o = (1 << (n - 2)) % n;
		for(int i = 0;i < o;i++)
			a[i] = (x + 1) << 1;
		for(int i = o;i < n;i++) {
			a[i] = x << 1;
		}
		print();
	}
	if(type == 5) {
		//k non-zero bits (-1 if flag is 2, shuffle if flag is 3)
		n = atoi(argv[2]);
		assert(n >= 2);
		int k = atoi(argv[3]);
		seed = atoi(argv[4]);
		int flag = atoi(argv[5]);
		assert(!(k == 1 && flag == 2));
		mt19937 rng(seed);

		vector<int> b, p;
		for(int i = 0;i < n;i++) p.pb(i);
		if(flag == 3) shuffle(all(p), rng);
		int sum = (1 << (n - 2)), rem = 0;
		for(int i = k;i > 1;i--) {
			int x = rand(0, sum / i, rng);
			rem += x;
			b.pb(rem << 1);
			sum -= x * i;
		}
		rem += sum;
		b.pb(rem << 1);
		for(int i = 0;i < k;i++)
			a[p[i]] = b[i];
		if(flag == 2) {
			int pos = -1;
			for(int i = 0;i < k;i++)
				if(a[p[i]]) pos = i;
			if(pos) a[p[pos]]--, a[p[0]]++;
			else a[p[0]]--, a[p[1]]++;
		}
		print();
	}
	if(type == 6) {
		//answer is -1 (general test)
		n = atoi(argv[2]);
		assert(n >= 2);
		seed = atoi(argv[3]);
		mt19937 rng(seed);
		
		int sum = (1 << (n - 2));
		for(int i = n;i > 1;i--) {
			int x = rand(0, sum, rng);
			a[i - 1] = x << 1;
			sum -= x;
		}
		a[0] = sum << 1;
		int p = -1;
		for(int i = 0;i < n;i++)
			if(a[i]) p = i;
		if(p) a[p]--, a[0]++;
		else a[0]--, a[1]++;
		shuffle(a, a + n, rng);
		print();
	}
	if(type == 7) {
		//exceptions for induction
		int x = atoi(argv[2]);
		if(x == 1) printf("4\n2 2 2 2\n");
		if(x == 2) printf("6\n2 6 6 6 6 6\n");
	}
	if(type == 8) {
		//random (small n)
		n = atoi(argv[2]);
		seed = atoi(argv[3]);
		mt19937 rng(seed);

		assert(n <= 8);
		rek((1 << (n - 2)), n, 0);
		int p = rand(0, (int)partitions.size() - 1, rng);
		vector<int> b = partitions[p];
		shuffle(all(b), rng);
		for(int i = 0;i < n;i++) a[i] = b[i] << 1;
		print();
	}
	if(type == 9) {
		//counter-tests for wrong solutions
		int x = atoi(argv[2]);

		//permute bits so that (highest bit - highest frequency)
		if(x == 1) printf("4\n0 4 2 2\n");
		if(x == 2) printf("6\n16 2 4 4 4 2\n");
		if(x == 3) printf("20\n0 513256 24 0 414 0 5168 0 376 4 1996 0 0 0 0 0 3032 0 2 16\n");

		//match highest bits first
		if(x == 4) printf("4\n0 6 0 2\n");
		if(x == 5) printf("6\n2 2 22 2 2 2\n");
		if(x == 6) printf("20\n0 0 0 20 0 46 2356 0 214398 0 12490 2 0 0 0 292410 34 0 0 2532\n");

		//match lowest bits first
		if(x == 7) printf("4\n2 2 2 2\n");
		if(x == 8) printf("6\n22 0 6 0 4 0\n");
		if(x == 9) printf("20\n2 49690 34 75688 28 104 397080 0 0 6 0 0 16 120 326 2 776 4 376 36\n");

		//take edge that blocks minimum number of others
		if(x == 10) printf("4\n2 4 0 2\n");
		if(x == 11) printf("6\n0 0 16 0 0 16\n");
		if(x == 12) printf("6\n2 0 2 0 0 28\n");
	}
	if(type == 10) {
		//n <= 4
		n = atoi(argv[2]);
		int x = atoi(argv[3]);
		
		if(n == 2) {
			a[x - 1] = 2;
		}
		if(n == 3) {
			if(x <= 3) a[x - 1] = 4; //4 0 0 in all orders
			if(x >= 4) { //2 2 0 in all orders
				a[0] = a[1] = a[2] = 2; 
				a[x - 4] = 0;
			}
		}
		if(n == 4) {
			if(x <= 4) a[x - 1] = 8; //4 0 0 0 in all orders
			if(4 < x && x <= 16) {//6 2 0 0 in all orders
				x -= 5;
				for(int i = 0;i < 4;i++) {
					for(int j = 0;j < 4;j++) {
						if(i == j) continue;
						if(x == 0) a[i] = 2, a[j] = 6;
						x--;
					}
				}
			}
			if(16 < x && x <= 22) {//4 4 0 0 in all orders
				x -= 17;
				for(int i = 0;i < 4;i++) {
					for(int j = i + 1;j < 4;j++) {
						if(x == 0) a[i] = 4, a[j] = 4;
						x--;
					}
				}
			}
			if(22 < x && x <= 34) {//4 2 2 0 in all orders
				x -= 23;
				a[0] = a[1] = a[2] = a[3] = 2;
				for(int i = 0;i < 4;i++) {
					for(int j = 0;j < 4;j++) {
						if(i == j) continue;
						if(x == 0) a[i] = 0, a[j] = 4;
						x--;
					}
				}
			}
			if(x == 35) a[0] = a[1] = a[2] = a[3] = 2;//2 2 2 2
		}
		print();
	}
	if(type == 11) {
		//more of -1 cases
		n = atoi(argv[2]);
		seed = atoi(argv[3]);
		mt19937 rng(seed);

		int flag = 1;
		while(flag) {
			int sum = (1 << (n - 1));
			vector<int> b;
			for(int i = 1;i < n;i++) {
				int r = rand(0, sum, rng);
				a[i] = r, sum -= r;
				if(r & 1) flag = 0;
			}
			a[0] = sum;
			if(sum & 1) flag = 0;
		}
		print();
	}
	return 0;
}
