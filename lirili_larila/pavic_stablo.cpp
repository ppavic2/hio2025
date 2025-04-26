#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>

#define X first
#define Y second
#define PB push_back

using namespace std;

typedef pair<int,int> pii;
typedef vector<int> vi;

const int N = 1e6 + 500;

struct M {
	queue<int> Q;
	deque<int> D;
	
	void push(int x) {
		Q.push(x);
		while(!D.empty() && D.back() < x) D.pop_back();
		D.push_back(x);
	}
	
	void pop() {
		if(Q.front() == D.front()) D.pop_front();
		Q.pop();
	}
	
	int maax() {
		return D.empty() ? -1 : D.front();
	}

};

int gdje[N], bio[N], par[N], n, m, a, b, novi = 1, siz[N], dep[N];
vi v[N], tko[N];

void dfs(int x, int lst) {
	par[x] = lst; bio[x] = 1;
	siz[x] = 1; dep[x] = dep[lst] + 1;
	for(int y : v[x]) {
		if(y == lst) continue;
		if(bio[y] && dep[y] < dep[x]) {
			int c = x;
			while(c != y) {
				tko[novi].PB(c);
				gdje[c] = novi;
				c = par[c];
			}
			tko[novi].PB(y);
			novi++;
		} else if(!bio[y]) {
			dfs(y, x);
			siz[x] += siz[y];
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	memset(gdje, -1, sizeof(gdje));
	cin >> n >> m >> a >> b;
	for(int i = 0;i < m;i++) {
		int x, y; cin >> x >> y;
		v[x].PB(y), v[y].PB(x);
	}
	dfs(1, 1);
	if(a + b == n) {
		for(int i = 1;i <= n;i++) {
			for(int j : v[i]){
				if(j == par[i] || (gdje[i] != -1 && gdje[j] == gdje[i])) continue;
				if(siz[j] == a) {
					cout << j << " " << i << endl;
					return 0;
				}
				if(siz[j] == b) {
					cout << i << " " << j << endl;
					return 0;
				}
			}
		}
	}
	for(int i = 1;i <= n;i++) {
		vector<pii> sus;
		for(int j : v[i]) {
			if(j == par[i]) sus.PB({j, n - siz[i]});
			else sus.PB({j, siz[j]});
		}
		int A = -1, B = -1;
		for(auto &[u, siz] : sus) {
			if(siz == a) A = u;
		}
		for(auto &[u, siz] : sus) {
			if(siz == b && u != A) B = u;
		}
		if(A > 0 && B > 0) {
			cout << A << " " << B << endl;
			return 0;
		}
	}
	cout << -1 << endl;
	return 0;
}
