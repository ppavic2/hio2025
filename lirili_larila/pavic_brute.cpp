#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>

#define X first
#define Y second
#define PB push_back

using namespace std;

typedef pair < int, int > pii;
typedef vector<int> vi;
typedef long long ll;

struct G {
	int n;
	vector<vi> v;
	G() {}
	G(int n) : n(n), v(n) {}
	
	void add_edge(int a, int b) {
		v[a].PB(b), v[b].PB(a);
	}
	
	void bfs(int start, vi &dist) {
		dist = vi(n, -1);
		dist[start] = 0;
		queue<int> Q; Q.push(start);
		for(;!Q.empty();Q.pop()) {
			int cur = Q.front();
			for(int nxt : v[cur]) {
				if(dist[nxt] == -1) {
					dist[nxt] = dist[cur] + 1;
					Q.push(nxt);
				}
			}
		}
	}

	pii count_pair(int a, int b) {
		vi dist_a, dist_b;
		bfs(a, dist_a);
		bfs(b, dist_b);
		int cnt_a = 0, cnt_b = 0;
		for(int i = 0;i < n;i++) {
			if(dist_a[i] < dist_b[i]) cnt_a++;
			if(dist_b[i] < dist_a[i]) cnt_b++;
		}
		return {cnt_a, cnt_b};
	}
};

void solve() {
	int n, m, a, b; cin >> n >> m >> a >> b;
	G graf(n);
	for(int i = 0;i < m;i++) {
		int u, v; cin >> u >> v;
		graf.add_edge(u - 1, v - 1);
	}
	for(int i = 0;i < n;i++) {
		for(int j = i + 1;j < n;j++) {
			pii cnts = graf.count_pair(i, j);
			if(cnts == (pii){a, b}) {
				cout << i + 1 << " " << j + 1 << endl;
				return;
			} else if(cnts == (pii){b, a}) {
				cout << j + 1 << " " << i + 1 << endl;
				return;
			}
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	int T; cin >> T;
	for(;T--;) solve();
}
