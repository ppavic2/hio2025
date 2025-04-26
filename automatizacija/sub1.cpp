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
			if (s[a[0]] == '.') cout << "+ " << a[0] + 1 << "\n";
			else cout << "! 0\n";
		} else {
			int i = 0;
			while (s[i] == '.') ++i;
			
			int l = max(a[0], i), r = min(a[0], i) + k - 1;
			cout << "! " << max(0, r - l + 1) << "\n";
		}
	}
	
	return 0;
}
