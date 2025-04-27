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

struct M {
	queue<int> Q;
	deque<int> D;
	
	void push(int x) {
		Q.push(x);
		while(!D.empty() && D.back() < x) D.pop_back();
		D.push_back(x);
	}

	int front() { return Q.front(); }
	int size() { return (int)Q.size(); }
	int maax() { return D.empty() ? -1 : D.front(); }
	
	void pop() {
		if(Q.front() == D.front()) D.pop_front();
		Q.pop();
	}

};

int gdje[N], bio[N], par[N], n, m, a, b, novi, siz[N], dep[N];
vi v[N], tko[N];
int escape[N], cut[N];

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
			gdje[y] = novi;
			tko[novi].PB(y);
			reverse(tko[novi].begin(), tko[novi].end());
			novi++;
		} else if(!bio[y]) {
			dfs(y, x);
			siz[x] += siz[y];
		}
	}
}

int down[N], up[N];

void calc_escapes(int x) {
	assert(par[x] == x || gdje[x] == -1 || gdje[par[x]] != gdje[x]);
	if(gdje[x] == -1) {
		down[x] = 0;
		for(int y : v[x]) {
			if(par[y] != x) continue;
			calc_escapes(y);
			down[x] = max(down[y] + 1, down[x]);
		}			
		for(int _ = 0;_ < 2;_++) {
			int dos = 0;
			for(int y : v[x]) {
				if(par[y] != x) continue;
				up[y] = max(up[y], dos + 1);
				dos = max(dos, down[y] + 1);
			}
			reverse(v[x].begin(), v[x].end());
		}
	} else {
		vi &cik = tko[gdje[x]];
		int C = (int)cik.size();
		vi tmp(C);
		for(int zi = 0;zi < C;zi++) {
			int z = cik[zi];
			for(int y : v[z]) {
				if(par[y] != z || gdje[y] == gdje[z]) continue;
				calc_escapes(y);
				tmp[zi] = max(tmp[zi], down[y] + 1);
			}
			down[x] = max(down[x], tmp[zi] + min(zi, C - zi));		
			for(int _ = 0;_ < 2;_++) {
				int dos = 0;
				for(int y : v[z]) {
					if(par[y] != z || gdje[y] == gdje[z]) continue;
					up[y] = max(up[y], dos + 1);
					dos = max(dos, down[y] + 1);
				}
				reverse(v[z].begin(), v[z].end());
			}
		}
		M L, R;
		for(int zi = 0;zi <= C / 2;zi++) {
			L.push(tmp[zi] + zi);
		}
		for(int zi = C / 2 + 1;zi < C;zi++) {
			R.push(tmp[zi] - zi);
		}
		for(int zi = 0;zi < C;zi++) {
			L.pop();
			int sad = max(L.maax() - zi, R.maax() + zi + C);
			int z = cik[zi];
			for(int y : v[z]) {
				if(par[y] != z || gdje[y] == gdje[z]) continue;
				up[y] = max(up[y], sad + 1);
			}
			R.push(tmp[zi] - zi - C);
			R.pop();
			L.push(tmp[(zi + C / 2 + 1) % C] + (zi + C / 2 + 1));
		}
	}
}

void propagate_up(int x) {
	assert(par[x] == x || gdje[x] == -1 || gdje[par[x]] != gdje[x]);
	if(gdje[x] == -1) {
		for(int y : v[x]) {
			if(par[y] != x) continue;
			up[y] = max(up[y], up[x] + 1);
			propagate_up(y);
		}
	} else {
		vi &cik = tko[gdje[x]];
		int C = (int)cik.size();
		vi tmp(C);
		for(int zi = 0;zi < C;zi++) {
			int z = cik[zi];
			for(int y : v[z]) {
				if(par[y] != z || gdje[y] == gdje[z]) continue;
				up[y] = max(up[y], up[x] + 1 + min(zi, C - zi));
				propagate_up(y);
			}
		}
	}
}

int find_escape(int x, int when, int banned = -1) {
	if(gdje[x] == -1 && banned == -1) return 0;
	if(banned == -1) banned = gdje[x];
	vi dist(n + 1, -1);
	dist[x] = 0;
	queue<int> Q; Q.push(x);
	for(;!Q.empty();Q.pop()) {
		int cur = Q.front();
		if(dist[cur] == when) return cur;
		for(int nxt : v[cur]) {
			if(dist[nxt] != -1 || gdje[nxt] == banned) continue;
			dist[nxt] = dist[cur] + 1;
			Q.push(nxt);
		}
	}
	assert(false);
	return -1;
}

int circ_dist(int A, int B, int C) {
	return min(abs(A - B), C - abs(A - B));
}

bool solve_cycle_case1(vi &cik, int A, int B) {
	int C = (int)cik.size();
	int cnt = 0, j = 0;
	M S;
	for(int i = 0;i < C;i++) {
		while(cnt < A) {
			cnt += cut[cik[j]];
			S.push(escape[cik[j]]);
			j = (j + 1) % C;
		}
		if(cnt == A) {
			int len = S.size();
			if(C % 2 == 1
			   && (n - A - B == cut[cik[j]] || n - A - B == cut[cik[(i + C - 1) % C]]) 
			   && len <= C - len - 1
			   && S.maax() >= (C - 1) / 2 - len) {
			   	int t, target = (C - 1) / 2 - len;
			   	if(!target) {
				   	for(t = i; escape[cik[t]] < target; t = (t + 1) % C);
				   	int x = find_escape(cik[t], target), y;
				   	if(n - A - B == cut[cik[j]]) {
				   		y = cik[(j + target + circ_dist(t, j, C)) % C];
				   	} else {
				   		y = cik[(5 * C + i - 1 - (target + circ_dist(t, (i + C - 1) % C, C))) % C];
				   	}
				   	if(A == a) cout << x << " " << y << endl;
				   	else cout << y << " " << x << endl;
					return true;
				}
			}
			if(C % 2 == 0 && A + B == n
			  && len <= C - len && S.maax() >= C / 2 - len) {
			    int t, target = C / 2 - len;
			    if(!target) {
				   	for(t = i; escape[cik[t]] < target; t = (t + 1) % C);
				   	int x = find_escape(cik[t], target);
				   	int y = cik[(j + target + circ_dist(t, j, C) - 1) % C];
				   	if(A == a) cout << x << " " << y << endl;
				   	else cout << y << " " << x << endl;
					return true;
			    }
			}
			if(C % 2 == 0
			  && n - A - B == cut[cik[j]] + cut[cik[(i + C - 1) % C]]
			  && len <= C - len - 2 && S.maax() >= C / 2 - len - 1) {
				int t, target = C / 2 - len - 1;
				if(!target) {
				   	for(t = i; escape[cik[t]] < target; t = (t + 1) % C);
				   	int x = find_escape(cik[t], target);
				   	int y = cik[(j + target + circ_dist(t, j, C)) % C];
				   	if(A == a) cout << x << " " << y << endl;
				   	else cout << y << " " << x << endl;
				  	return true;
			  	}
			}
		}
		cnt -= cut[cik[i]];
		S.pop();
	}
	return false;
}

void solve() {
	cin >> n >> m >> a >> b;
	novi = 0;
	for(int i = 0;i <= n + 10;i++) {
		v[i].clear(); gdje[i] = -1;
		tko[i].clear(); 
		down[i] = up[i] = bio[i] = par[i] = dep[i] = siz[i] = escape[i] = cut[i] = 0;
	}
	for(int i = 0;i < m;i++) {
		int x, y; cin >> x >> y;
		v[x].PB(y), v[y].PB(x);
	}
	dfs(1, 1);
	calc_escapes(1);
	propagate_up(1);
	for(int cik_ind = 0;cik_ind < novi;cik_ind++) {
		vi &cik = tko[cik_ind];
		int C = (int)cik.size();
		cut[cik[0]] = n - siz[cik[1]];
		cut[cik.back()] = siz[cik.back()];
		for(int i = 1;i + 1 < C;i++) {
			cut[cik[i]] = siz[cik[i]] - siz[cik[i + 1]];
		}
		escape[cik[0]] = up[cik[0]];
		for(int xi = 0;xi < C;xi++) {
			int x = cik[xi];
			for(int y : v[x]) {
				if(par[y] != x || gdje[y] == gdje[x]) continue;
				escape[x] = max(escape[x], down[y] + 1);
			}
		}
		if(solve_cycle_case1(cik, a, b)) return;
		if(solve_cycle_case1(cik, b, a)) return;
	}
	return;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	int T; cin >> T;
	for(;T--;) solve();
}
