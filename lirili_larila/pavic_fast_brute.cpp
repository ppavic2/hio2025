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

const int N = 5050;

int dist[N][N], n;
vi v[N];

void bfs(int start) {
	for(int i = 0;i < n;i++) 
		dist[start][i] = -1;
	dist[start][start] = 0;
	queue<int> Q; Q.push(start);
	for(;!Q.empty();Q.pop()) {
		int cur = Q.front();
		for(int nxt : v[cur]) {
			if(dist[start][nxt] == -1) {
				dist[start][nxt] = dist[start][cur] + 1;
				Q.push(nxt);
			}
		}
	}
}

void solve() {
	int m, a, b; cin >> n >> m >> a >> b;
	for(int i = 0;i < n;i++) v[i].clear();
	for(int i = 0;i < m;i++) {
		int x, y; cin >> x >> y;
		x--, y--;
		v[y].PB(x), v[x].PB(y);
	}
	for(int i = 0;i < n;i++) bfs(i);
	for(int i = 0;i < n;i++) {
		for(int j = i + 1;j < n;j++) {
			pii cnts = {0, 0};
			for(int k = 0;k < n;k++) {
				if(dist[i][k] < dist[j][k]) cnts.first++;
				if(dist[j][k] < dist[i][k]) cnts.second++;
			}
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
