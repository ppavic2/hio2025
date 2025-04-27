#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 2e5 + 2;
const int OFF = 1 << 21;

int n, q, a[N];

struct Node {
	int pref = 0, suf = 0;
	int taken = 0;
	ll ans = 1;
} tour[OFF];

void calculate(int node, int l, int r) {
	if (l == r) {
		tour[node].pref = tour[node].suf = !tour[node].taken;
		tour[node].ans = !tour[node].taken;
		return ;
	}

	int mid = (l + r) >> 1;
	int L = node * 2 + 1, R = node * 2 + 2;
	tour[node].ans = tour[L].ans + tour[R].ans + (ll)tour[L].suf * tour[R].pref;
	tour[node].pref = tour[L].pref;
	if (tour[node].pref == mid - l + 1) {
		tour[node].pref += tour[R].pref;
	}
	tour[node].suf = tour[R].suf;
	if (tour[node].suf == r - mid) {
		tour[node].suf += tour[L].suf;
	}
	
	if (tour[node].taken) {
		tour[node].pref = tour[node].suf = 0;
		tour[node].ans = 0;
	}
}

void con(int x, int l, int r) {
	int mid = (l + r) >> 1;
	if (l != r) {
		con(x * 2 + 1, l, mid);
		con(x * 2 + 2, mid + 1, r);
	}
	calculate(x, l, r);
}

void update(int x, int l, int r, int ql, int qr, int val) {
	if (ql > r || l > qr) return ;
	if (ql <= l && r <= qr) {
		tour[x].taken += val;
		calculate(x, l, r);
		return ;
	}
	int mid = (l + r) >> 1;
	update(x * 2 + 1, l, mid, ql, qr, val);
	update(x * 2 + 2, mid + 1, r, ql, qr, val);
	calculate(x, l, r);
}

void check(int i, int d) {
	if (a[i] != a[n - i - 1]) {
		update(0, 0, a[n / 2] - 1, min(a[i], a[n - i - 1]), max(a[i], a[n - i - 1]) - 1, d);
	}
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	
	cin >> n >> q;
	for (int i = 0; i < n; ++i) {
		cin >> a[i];
	}
	
	con(0, 0, a[n / 2] - 1);
	
	for (int i = 0; i < n / 2; ++i) {
		check(i, 1);
	}
	
	cout << tour[0].ans << '\n';
	
	while (q--) {
		int x, h;
		cin >> x >> h, --x;
		
		check(x, -1);
		a[x] = h;
		check(x, 1);
		
		cout << tour[0].ans << '\n';
	}
	
	return 0;
}
