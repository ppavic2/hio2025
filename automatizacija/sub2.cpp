#include <bits/stdc++.h>
using namespace std;

const int N = 16;

int a[N];

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);

	int type, n, k, t;
	cin >> type >> n >> k;
	for (int i = 0; i < k; ++i) {
		cin >> a[i], --a[i];
	}
	cin >> t;
	while (t--) {
		string s; cin >> s;
		if (type == 1) {
			for (int i = 0; i < k; ++i) {
				if (s[a[i]] == '.') {
					cout << "+ " << a[i] + 1 << "\n";
					break;
				}
				if (i == k - 1) cout << "! 0\n";
			}
		} else {
			int cnt = 0, ans = 0;
			for (int i = 0; i < n; ++i) cnt += s[i] == 'P';
			if (cnt == k) {
				for (int i = 0; i < k; ++i) {
					ans += s[a[i]] == 'P';
				}
				cout << "! " << ans << '\n';
			} else {
				int i = n - 1;
				while (i >= 0 && s[i] != '.') --i;
				
				if (i == -1) cout << "! 0\n";
				else cout << "+ " << i + 1 << '\n';
			}
		}
	}
	
	return 0;
}
