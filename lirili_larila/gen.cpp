#include <cstdio>
#include <chrono>
#include <iostream>
#include <random>
#include <cassert>
#include <cstring>
#include <algorithm>
#include <set>
#include <map>
#include <queue>

#define sz(x) (int)x.size()
#define X first
#define Y second
#define PB push_back

using namespace std;

typedef pair < int, int > pii;
typedef vector<int> vi;
typedef long long ll;

mt19937 rng;

int rint(int l, int r) {
	return uniform_int_distribution<int>(l, r)(rng);
}

int relement(vector<int> &v) {
	return v[rint(0, (int)v.size() - 1)];
}

enum tree_type {
	SHALLOW,
	DEEP,
	SQRT,
	CHAIN
};

enum cactus_type {
	NO_CYCLES,
	ONE_CYCLE,
	SUN,
	SMALL_CYCLES,
	LARGE_CYCLES,
	LARGE_CYCLES_WITH_SPACE
};

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
			assert(dist_a[i] >= 0 && dist_b[i] >= 0);
			if(dist_a[i] < dist_b[i]) cnt_a++;
			if(dist_b[i] < dist_a[i]) cnt_b++;
		}
		return {cnt_a, cnt_b};
	}

	vector<pii> get_edges() {
		vector<pii> edges;
		for(int i = 0;i < n;i++) {
			for(int j : v[i]) {
				if(i < j) edges.PB({i, j});
			}
		}
		shuffle(edges.begin(), edges.end(), rng);
		for (auto &[a, b] : edges) if(rint(0, 1)) swap(a, b);
		return edges;
	}
};

G gen_tree(int n, tree_type type) {
	G ret(n);
	for(int i = 1;i < n;i++)
		ret.add_edge(i, rint(0, i - 1));
	return ret;
}

G gen_cactus(int n, cactus_type type) {
	int n_tree = rint(n / 4, n / 2);
	G base = gen_tree(n_tree, SHALLOW);
	G ret(n);
	vector<vi> gdje(n_tree);
	for(int i = 0;i < n_tree;i++) gdje[i].PB(i);
	for(int i = n_tree;i < n;i++) gdje[rint(0, n_tree - 1)].PB(i);
	for(int i = 0;i < n_tree;i++) {
		if(gdje[i].size() > 1) {
			shuffle(gdje[i].begin(), gdje[i].end(), rng);
			if((int)gdje[i].size() > 2) 
				ret.add_edge(gdje[i][0], gdje[i].back());
			for(int j = 0;j + 1 < (int)gdje[i].size();j++)
				ret.add_edge(gdje[i][j], gdje[i][j + 1]);
		}
	}
	vector<pii> tree_edges = base.get_edges();
	for(auto &[a, b] : tree_edges) {
		ret.add_edge(relement(gdje[a]), relement(gdje[b]));
	}
	return ret;
}

void finish_output(G &graph) {
	int n = graph.n;
	int a = rint(0, n - 1), b = rint(0, n - 2);
	if(a == b) b++;
	pii cnts = graph.count_pair(a, b);
	vector<pii> edges = graph.get_edges();
	int m = (int)edges.size();
	cout << n << " " << m << " " << cnts.X << " " << cnts.Y << "\n";
	vi p(n);
	for(int i = 0;i < n;i++) p[i] = i + 1;
	shuffle(p.begin(), p.end(), rng);
	for(auto &[a, b] : edges) cout << p[a] << " " << p[b] << "\n";
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	rng = mt19937(chrono::steady_clock::now().time_since_epoch().count());
	//G final = gen_cactus(rint(5000, 10000), SHALLOW_SMALL);
	//G final = gen_cactus(1000, SHALLOW_SMALL);
	//G final = gen_tree(10, SHALLOW);
	
	int T = 1000;
	
	cout << T << endl;
	
	for(int i = 0;i < T;i++) {
		G final = gen_cactus(rint(100, 3000), SHALLOW_SMALL);
		finish_output(final);
	}
}

