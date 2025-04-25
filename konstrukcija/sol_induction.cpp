#include<bits/stdc++.h>

#define pb push_back
#define x first
#define y second
#define all(a) (a).begin(), (a).end()

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;

const int maxn = (1 << 20);

int n;
int a[25];
int p[25];
int pos[maxn];

vector<ii> exeptions(vector<int> a) {
	if(a.size() == 4) {
		return {{0, 1}, {8, 9}, {4, 6}, {12, 14},
				{3, 7}, {11, 15}, {2, 10}, {5, 13}};
	}
	if(a.size() == 6) {
		return {{0, 1}, {32, 33}, {16, 18}, {48, 50},
				{8, 10}, {40, 42}, {24, 26}, {56, 58},
				{2, 6}, {34, 38}, {17, 21}, {49, 53}, 
				{9, 13}, {41, 45}, {4, 12}, {36, 44},
				{20, 28}, {52, 60}, {22, 30}, {54, 62},
				{3, 19}, {35, 51}, {11, 27}, {43, 59},
				{7, 23}, {39, 55}, {14, 46}, {25, 57},
				{5, 37}, {29, 61}, {15, 47}, {31, 63}};
	}
	return {};
}

vector<ii> solve(vector<int> a) {
	if(a.size() == 1)
		return {{0, 1}};

	auto b = a;
	int n = a.size();
	for(int i = 0;i < n - 1;i++)
		if(a[i] & 2) b[i] += 2, b[n - 1] -= 2;
	
	if(b[n - 1] < 0)
		return exeptions(a);
	else b[n - 2] += b[n - 1];

	b.pop_back();
	for(int i = 0;i < n - 1;i++) b[i] >>= 1;
	auto M = solve(b);

	vector<ii> ret;
	for(auto [x, y] : M)
		if(a[pos[x ^ y]])
			ret.pb({x, y}), a[pos[x ^ y]] -= 2;

	int m = ret.size();
	for(int i = 0;i < m;i++)
		ret.pb({ret[i].x ^ (1 << (n - 1)), ret[i].y ^ (1 << (n - 1))});

	vector<int> vis((1 << n), 0);
	for(auto [x, y] : ret) vis[x] = vis[y] = 1;
	for(int i = 0;i < (1 << n);i++) {
		if(vis[i] == 0 && a[n - 1]) {
			a[n - 1]--;
			vis[i] = 1, vis[i ^ (1 << (n - 1))] = 1;
			ret.pb({i, i ^ (1 << (n - 1))});
		}
	}
	return ret;
}

int f(int x) {
	int ret = 0;
	for(int i = 0;i < n;i++)
		if(x & (1 << i)) ret += (1 << p[i]);
	return ret;
}

int main() {
	scanf("%d", &n);
	for(int i = 0;i < n;i++)
		scanf("%d", a + i), pos[(1 << i)] = i;

	vector<ii> v;
	for(int i = 0;i < n;i++) {
		v.pb({a[i], i});
		if((a[i] & 1) && n > 1) {
			printf("-1\n");
			return 0;
		}
	}
	sort(all(v));
	for(int i = 0;i < n;i++)
		p[i] = v[i].y;
	vector<int> a;
	for(int i = 0;i < n;i++)
		a.pb(v[i].x), p[i] = v[i].y;

	auto ans = solve(a);
	for(auto [x, y] : ans)
		printf("%d %d\n", f(x), f(y));
	return 0;
}