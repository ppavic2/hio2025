#include <bits/stdc++.h>
using namespace std;

const int N = 14;

int a[N], num;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);

	int type, n, k, t;
	cin >> type >> n >> k;
	for (int i = 0; i < k; ++i) {
		cin >> a[i], --a[i];
	}
	
	if (type == 1) {
		bool found = 0;
		for (int i = 0; i < N && !found; ++i) {
			for (int j = i + 1; j < N; ++j) {
				if (i == a[0] && j == a[1]) {
					found = 1; break;
				}
				++num;
			}
		}
	}

	assert(num < (1 << N/2));
	
	cin >> t;
	while (t--) {
		string s; cin >> s;
		
		int M = -1;
		for (int i = 0; i < n; ++i) {
			if (s[i] != '.') M = i;
		}
		
		if (type == 1) {
			if (M >= 12) {
				cout << "! 0\n";
				continue;
			}
			int bit = (M + 1) / 2;
			if (num & 1 << bit) {
				cout << "+ " << M + 3 << '\n';
			} else {
				cout << "+ " << M + 2 << '\n';
			}
		} else {
			if (M == n - 1 || M == n - 2) {
				num = 0;
				for (int i = 1; i <= M; i += 2) {
					if (s[i] == 'P') num += 1 << i / 2;
				}
				int x = 0, y = 0;
				bool found = 0;
				for (int i = 0; i < N && !found; ++i) {
					for (int j = i + 1; j < N; ++j) {
						if (!num) {
							x = i; y = j;
							found = 1;
							break;
						}
						--num;
					}
				}
				int ans = 0;
				ans += (x == a[0]) + (x == a[1]);
				ans += (y == a[0]) + (y == a[1]);
				cout << "! " << ans << '\n';
			} else {
				int i = 0;
				while (s[i] != '.') ++i;
				cout << "+ " << i + 1 << '\n';
			}
		}
	}
	
	return 0;
}
