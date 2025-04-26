#include <bits/stdc++.h>
using namespace std;

const int N = 16;

int n, k, a[N], b[N];

vector<string> states;
string current_state;

void gen_all_valid_states(int p, int c) {
	if ((int)current_state.length() == n) {
		if (p == c) states.push_back(current_state);
		return ;
	}
	if (p + n - (int)current_state.length() < c) return ;
	if (c + n - (int)current_state.length() < p) return ;
	current_state += '.';
	gen_all_valid_states(p, c);
	current_state.back() = 'P';
	gen_all_valid_states(p + 1, c);
	current_state.back() = 'C';
	gen_all_valid_states(p, c + 1);
	current_state.pop_back();
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);

	cin >> n >> k;
	for (int i = 0; i < k; ++i) cin >> a[i];
	for (int i = 0; i < k; ++i) cin >> b[i];
	
	cout << "1\n" << n << " " << k << "\n";
	for (int i = 0; i < k; ++i) {
		if (i) cout << " ";
		cout << a[i];
	}
	cout << "\n";
	
	gen_all_valid_states(0, 0);
	cout << (int)states.size() << '\n';
	for (const string& state : states) {
		cout << state << '\n';
	}
	
	return 0;
}
