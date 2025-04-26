#include <bits/stdc++.h>
using namespace std;

const int N = 16;

int a[N];
bool contains[N];

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);

	int type, n, k, t;
	cin >> type >> n >> k;
	for (int i = 0; i < k; ++i) {
		cin >> a[i], --a[i];
		contains[a[i]] = 1;
	}
	cin >> t;
	while (t--) {
		string s; cin >> s;
		if (s[n - 1] == '.') {
			for (int i = 0; i < k; ++i) {
				if (s[a[i]] == '.') {
					cout << "+ " << a[i] + 1 << '\n';
					break;
				}
				if (i == k - 1) {
					cout << "+ " << n << '\n';
				}
			}
		} else {
			int ans = 0, cnt = 0;
			for (int i = 0; i < n - 1; ++i) {
				if (type == 1 && s[i] == 'C') {
					++cnt;
					if (contains[i]) ++ans;
				}
				if (type == 2 && s[i] == 'P') {
					++cnt;
					if (contains[i]) ++ans;
				}
			}
			ans += k - cnt;
			if (ans < 0) ans = 0;
			if (ans > n) ans = n;
			cout << "! " << ans << '\n';
		}
	}
	
	return 0;
}
