#include <cassert>
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

int gdje[N], bio[N], par[N], n, m, a, b, novi, dep[N];
vi v[N], tko[N];

void dfs(int x, int lst) {
	par[x] = lst; bio[x] = 1;
	dep[x] = dep[lst] + 1;
	for(int y : v[x]) {
		if(y == lst) continue;
		if(bio[y] && dep[y] < dep[x]) {
			int c = x;
			while(c != y) {
				gdje[c] = novi;
				c = par[c];
			}
			gdje[y] = novi;
			novi++;
		} else if(!bio[y]) {
			dfs(y, x);
		}
	}
}

int bfs(int x) {
	if(gdje[x] == -1) return 0;
	vi dist(n + 1, -1);
	dist[x] = 0;
	queue<int> Q; Q.push(x);
	int ans = 0;
	for(;!Q.empty();Q.pop()) {
		int cur = Q.front();
		ans = max(ans, dist[cur]);
		for(int nxt : v[cur]) {
			if(dist[nxt] != -1 || gdje[nxt] == gdje[x]) continue;
			dist[nxt] = dist[cur] + 1;
			Q.push(nxt);
		}
	}
	return ans;
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
	for(int i = 1;i <= n;i++) cout << bfs(i) << " ";
	cout << endl;
	//cout << -1 << endl;
	return 0;
}
