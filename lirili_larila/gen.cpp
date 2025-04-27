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

/**

TREE TYPES
	- SHALLOW
	- DEEP
	- SQRT
	- CHAIN
	
CACTUS TYPES
	- SMALL_CYCLES
	- LARGE_CYCLES
	- LARGE_CYCLES_WITH_SPACE
	- ONE_LARGE_CYCLE
	- SUN TYPES
	| - SMALL_SUN
	| - LARGE_SUN
	| - SIMPLE_SUN

**/

int pr(int x, vi &par) {
	if(x == par[x]) return x;
	return par[x] = pr(par[x], par);
}

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
	
	bool find_path(int current, int last, int start, int target, vi &save) {
		if(current == target) {
			save.PB(current);
			return true;
		}
		for(int next : v[current]) {
			if(next == last || ((current == start && next == target) || (current == target && next == start))) continue;
			if(find_path(next, current, start, target, save)) {
				save.PB(current);
				return true;
			}
		}
		return false;
	}
	
	vi find_cycle() {
		vi par(n);
		for(int i = 0;i < n;i++) par[i] = i;
		int a = -1, b = -1;
		for(int i = 0;i < n && a == -1;i++) {
			for(int j : v[i]) {
				if(j < i) {
					int ii = pr(i, par), jj = pr(j, par);
					if(ii == jj) {
						a = i, b = j;
						break;
					} else {
						par[ii] = jj;
					}
				}
			}
		}
		vi ret;
		find_path(a, a, a, b, ret);
		return ret;
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

G gen_tree(int n, string T) {
	G ret(n);
	if(T == "SHALLOW") { 
		for(int i = 1;i < n;i++)
			ret.add_edge(i, rint(0, i - 1));
	} else if(T == "DEEP") {
		for(int i = 1;i < n;i++)
			ret.add_edge(i, rint(max(0, i - 20), i - 1));
	} else if(T == "SQRT") {
		vi pruf(n), kol(n);
		set<int> S;
		for(int i = 0;i < n - 2;i++) {
			pruf[i] = rint(0, n - 1);
			kol[pruf[i]]++;
		}
		for(int i = 0;i < n;i++) {
			if(!kol[i]) S.insert(i);
		}
		for(int i = 0;i < n - 2;i++){
			int j = *S.begin();
			S.erase(S.begin());
			kol[pruf[i]]--;
			ret.add_edge(j, pruf[i]);
			if(!kol[pruf[i]])
			    S.insert(pruf[i]);
		}
		int x = *S.begin(), y = *S.rbegin();
		ret.add_edge(x, y);
	} else if(T == "CHAIN") {
		for(int i = 1;i < (2 * n) / 3;i++)
			ret.add_edge(i, i - 1);
		for(int i = (2 * n) / 3;i < n;i++)
			ret.add_edge(rint(0, i - 1), i);
	}
	return ret;
}

G gen_cactus(int n, string C, string T) {
	G ret(n);
	if(C == "TREE" || C == "SMALL_CYCLES" || C == "LARGE_CYCLES" || C == "LARGE_CYCLES_WITH_SPACE" || C == "ONE_LARGE_CYCLE") {
		int n_tree = -1, cutoff = -1;
		if(C == "TREE") 
			n_tree = n, cutoff = 0;
		else if(C == "SMALL_CYCLES") 
			n_tree = rint(n / 4, n / 2), cutoff = n_tree;
		else if(C == "LARGE_CYCLES") 
			n_tree = rint(sqrt(n), 2 * sqrt(n)), cutoff = n_tree;
		else if(C == "LARGE_CYCLES_WITH_SPACE") 
			n_tree = rint(sqrt(n), 2 * sqrt(n)), cutoff = n_tree / 3;
		else if(C == "ONE_LARGE_CYCLE")
			n_tree = rint(n / 4, n / 2), cutoff = n_tree;
		assert(n_tree != -1);
		G base = gen_tree(n_tree, T);
		vector<vi> gdje(n_tree);
		for(int i = 0;i < n_tree;i++) gdje[i].PB(i);
		for(int i = n_tree;i < n;i++) {
			if(C != "ONE_LARGE_CYCLE") {
				gdje[rint(0, cutoff - 1)].PB(i);
			} else if(C == "ONE_LARGE_CYCLE"){
				if(rint(0, 1))
					gdje[0].PB(i);
				else
					gdje[rint(1, cutoff - 1)].PB(i);
			}
		}
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
	} else if(C == "SMALL_SUN" || C == "LARGE_SUN") {
		int n_cyc = 0;
		if(C == "SMALL_SUN") n_cyc = rint(sqrt(n), 2 * sqrt(n));
		else n_cyc = rint(n / 3, n / 2);
		for(int i = 0;i < n_cyc;i++) ret.add_edge(i, (i + 1) % n_cyc);
		for(int i = n_cyc;i < n;i++) ret.add_edge(rint(0, i - 1), i);
	} else if(C == "SIMPLE_SUN" || C == "Y_SIMPLE_SUN") {
		ret = gen_tree(n, T);
		vector<pii> tree_edges = ret.get_edges();
		set<pii> S;
		for(auto tmp : tree_edges) S.insert(tmp);
		while(true) {
			int x = rint(0, n - 1), y = rint(0, n - 1);
			if(x != y && (S.count({x, y}) + S.count({y, x}) == 0)) {
				ret.add_edge(x, y);
				break;
			}
		}
	}
	return ret;
}

void finish_output(G &graph, string C, string T) {
	int n = graph.n, a, b;
	if (T != "Y" && C != "Y_SIMPLE_SUN") {
		a = rint(0, n - 1), b = rint(0, n - 2);
		if(a == b) b++;
	} else {
		vector<int> cik = graph.find_cycle();
		a = rint(0, (int)cik.size() - 1), b = rint(0, (int)cik.size() - 2);
		if(a == b) b++;
		a = cik[a], b = cik[b];
	}
	pii cnts = graph.count_pair(a, b);
	vector<pii> edges = graph.get_edges();
	int m = (int)edges.size();
	cout << n << " " << m << " " << cnts.X << " " << cnts.Y << "\n";
	vi p(n);
	for(int i = 0;i < n;i++) p[i] = i + 1;
	shuffle(p.begin(), p.end(), rng);
	for(auto &[a, b] : edges) cout << p[a] << " " << p[b] << "\n";
}

int to_int(char *s){
    int ret = 0, k = strlen(s);
    for(int i = 0;i < k;i++) {
        ret = 10 * ret + s[i] - '0';
    }
   	return ret;
}

int main(int argc, char** argv){
	ios_base::sync_with_stdio(false); cin.tie(0);
	rng = mt19937(chrono::steady_clock::now().time_since_epoch().count());
	
	int sum_n = to_int(argv[1]);
	int max_n = to_int(argv[2]);
	
	string C(argv[3]), T(argv[4]);
	
	
	int tests = sum_n / max_n;
	cout << tests << endl;
	
	for(int i = 0;i < tests;i++) {
		if (C == "SPECIAL_1") {
			int n = max_n;
			cout << n << " " <<  n - 1 << " " << n - 4 << " " << 1 << endl;
			for(int i = 1;i + 1 <= n - 4;i++) {
				cout << i << " " << i + 1 << endl;
			}
			int k = (2 * n) / 3;
			cout << k << " " << n << endl;
			cout << n << " " << n - 1 << endl; 
			cout << n << " " << n - 2 << endl; 
			cout << n << " " << n - 3 << endl; 
			continue;
		} else if(C == "SPECIAL_2") {
			int n = max_n;
			vi p(n + 1);
			for(int i = 1;i <= n;i++) p[i] = i;
			shuffle(p.begin() + 1, p.end(), rng);
			cout << n << " " <<  n - 1 << " " << n - 4 << " " << 1 << endl;
			for(int i = 1;i + 1 <= n - 4;i++) {
				cout << p[i] << " " << p[i + 1] << endl;
			}
			int k = (2 * n) / 3;
			cout << p[k] << " " << p[n] << endl;
			cout << p[n] << " " << p[n - 1] << endl; 
			cout << p[n] << " " << p[n - 2] << endl; 
			cout << p[n] << " " << p[n - 3] << endl; 
			continue;
		} else if (C == "SPECIAL_3") {
			int n = max_n;
			cout << n << " " <<  n << " " << n - 4 << " " << 1 << endl;
			for(int i = 1;i + 1 <= n - 4;i++) {
				cout << i << " " << i + 1 << endl;
			}
			int k = (2 * n) / 3;
			cout << k << " " << n << endl;
			cout << n << " " << n - 1 << endl; 
			cout << n << " " << n - 2 << endl; 
			cout << n << " " << n - 3 << endl; 
			cout << 1 << " " << 3 << endl;
			continue;
		} else if(C == "SPECIAL_4") {
			int n = max_n;
			vi p(n + 1);
			for(int i = 1;i <= n;i++) p[i] = i;
			shuffle(p.begin() + 1, p.end(), rng);
			cout << n << " " <<  n << " " << n - 4 << " " << 1 << endl;
			for(int i = 1;i + 1 <= n - 4;i++) {
				cout << p[i] << " " << p[i + 1] << endl;
			}
			int k = (2 * n) / 3;
			cout << p[k] << " " << p[n] << endl;
			cout << p[n] << " " << p[n - 1] << endl; 
			cout << p[n] << " " << p[n - 2] << endl; 
			cout << p[n] << " " << p[n - 3] << endl;
			cout << p[1] << " " << p[3] << endl;
			continue;
		} 
		int n = max_n - rint(0, min(50, max_n / 10));
		G graph = gen_cactus(n, C, T);
		finish_output(graph, C, T);
	}
}

