#include <bits/stdc++.h>
using namespace std;

const int N = 16;

int type, n, k, t;
bool a[N], invert;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);

	cin >> type >> n >> k;
	for (int i = 0; i < k; ++i) {
		int x; cin >> x, --x;
		a[x] = 1;
	}

	if (2 * k > n) {
		invert = 1;
		k = n - k;
		for (int i = 0; i < n; ++i) a[i] ^= 1;
	}
	
	cin >> t;

	while (t--) {
		string s; cin >> s;

		if (type == 1) {
			if (k == 0) {
				cout << "! " << n << "\n";
				continue;
			}
			bool found = 0;
			for (int i = 0; i < n; ++i) {
				if (s[i] != '.') continue;
				int j = (i + 1) % n;
				while (s[j] != '.') j = (j + 1) % n;
				if (a[i] && !a[j]) {
					cout << "+ " << i + 1 << '\n';
					found = 1;
					break;
				}
			}
			if (!found) cout << "! 0\n";
		} else {
			int cnt = 0, idx = 0;
			for (int i = 0; i < n; ++i) {
				cnt += s[i] == 'P';
				if (s[i] != '.') continue;
				int cur = 0, j = (i + 1) % n;
				while (s[j] != '.') {
					j = (j + 1) % n;
					++cur;
				}
				if (cur & 1) idx = j;
			}

			if (cnt >= k) {
				int ans = 0;
				for (int i = 0; i < n; ++i) {
					if (!invert && a[i] && s[i] == 'P') ++ans;
					if (invert && !a[i] && s[i] != 'P') ++ans;
				}
				cout << "! " << ans << '\n';
			} else {
				cout << "+ " << idx + 1 << '\n';
			}
		}
	}

	return 0;
}
