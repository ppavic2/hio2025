#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 2e5 + 2;
const int OFF = 1 << 20;

int n, q, a[N], val[OFF];

void update(int l, int r, int d) {
	val[l] += 1;
	val[r + 1] -= 1;
}
ll answer() {
	ll ret = 0;
	int cnt = 0;
	for (int i = 0; i < a[n / 2]; ++i) {
		if (!val[i]) ++cnt;
		else {
			ret += (ll)cnt * (cnt + 1) / 2LL;
			cnt = 0;
		}
	}
	ret += (ll)cnt * (cnt + 1) / 2LL;
	cnt = 0;
	return ret;
}

void check(int i, int d) {
	if (a[i] != a[n - i - 1]) {
		update(min(a[i], a[n - i - 1]), max(a[i], a[n - i - 1]) - 1, d);
	}
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	
	cin >> n >> q;
	for (int i = 0; i < n; ++i) {
		cin >> a[i];
	}
	for (int i = 0; i < n / 2; ++i) {
		check(i, 1);
	}
	
	for (int i = 1; i < a[n / 2]; ++i) val[i] += val[i - 1];
	
	cout << answer() << '\n';
	
	return 0;
}
