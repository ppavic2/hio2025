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

void solve_cycle_case1(vi &cik, int A, int B) {
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
			   	for(t = i; escape[cik[t]] < target; t = (t + 1) % C);
			   	int x = find_escape(cik[t], target), y;
			   	if(n - A - B == cut[cik[j]]) {
			   		y = cik[(j + target + circ_dist(t, j, C)) % C];
			   	} else {
			   		y = cik[(5 * C + i - 1 - (target + circ_dist(t, (i + C - 1) % C, C))) % C];
			   	}
			   	if(A == a) cout << x << " " << y << endl;
			   	else cout << y << " " << x << endl;
				exit(0);
			}
			if(C % 2 == 0 && A + B == n
			  && len <= C - len && S.maax() >= C / 2 - len) {
			    int t, target = C / 2 - len;
			   	for(t = i; escape[cik[t]] < target; t = (t + 1) % C);
			   	int x = find_escape(cik[t], target);
			   	int y = cik[(j + target + circ_dist(t, j, C) - 1) % C];
			   	if(A == a) cout << x << " " << y << endl;
			   	else cout << y << " " << x << endl;
			   exit(0);
			}
			if(C % 2 == 0
			  && n - A - B == cut[cik[j]] + cut[cik[(i + C - 1) % C]]
			  && len <= C - len - 2 && S.maax() >= C / 2 - len - 1) {
				int t, target = C / 2 - len - 1;
			   	for(t = i; escape[cik[t]] < target; t = (t + 1) % C);
			   	int x = find_escape(cik[t], target);
			   	int y = cik[(j + target + circ_dist(t, j, C)) % C];
			   	if(A == a) cout << x << " " << y << endl;
			   	else cout << y << " " << x << endl;
			  	exit(0);
			}
		}
		cnt -= cut[cik[i]];
		S.pop();
	}
}

int win[N], tko_win[N];

void solve_cycle_case2(vi &cik, int A, int B) {
	int C = (int)cik.size();
	for(int x : cik) win[x] = tko_win[x] = -1;
	for(int x : cik) {
		if(gdje[par[x]] != gdje[x] && n - siz[x] == B) {
			win[x] = up[x];
			tko_win[x] = par[x];
		}
		for(int y : v[x]) {
			if(par[y] != x || gdje[y] == gdje[x]) continue;
			if (siz[y] == B && down[y] + 1 > win[x]) {
				win[x] = down[y] + 1;
				tko_win[x] = y;
			}
		}
	}
	int cnt = 0, j = 0, len = 0;
	for(int i = 0;i < C;i++) {
		while(cnt < n - A) {
			cnt += cut[cik[j]];
			j = (j + 1) % C;
			len++;
		}
		if(cnt == n - A && C / 2 - (len - 1) > 0) {
			int target = C / 2 - (len - 1);
			if(win[cik[i]] >= target) {
				int x = cik[(i + C - target) % C];
				int y = find_escape(tko_win[cik[i]], target - 1, gdje[cik[i]]);
				if(A == a) cout << x << " " << y << endl;
			   	else cout << y << " " << x << endl;
			  	exit(0);
			} else if(win[cik[(j + C - 1) % C]] >= target) {
				int x = cik[(j + target - 1 + C) % C];
				int y = find_escape(tko_win[cik[(j + C - 1) % C]], target - 1, gdje[cik[i]]);
				if(A == a) cout << x << " " << y << endl;
			   	else cout << y << " " << x << endl;
			  	exit(0);
			}
		}
		cnt -= cut[cik[i]];
		len--;
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
	if(1) {
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
				if(gdje[j] == gdje[i] && gdje[i] != -1) continue;
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
	}
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
		solve_cycle_case1(cik, a, b);
		solve_cycle_case1(cik, b, a);
		solve_cycle_case2(cik, a, b);
		solve_cycle_case2(cik, b, a);
	}
	cout << -1 << endl;
	return 0;
}
