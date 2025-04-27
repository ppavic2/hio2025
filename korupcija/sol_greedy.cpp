#include<bits/stdc++.h>

#define pb push_back
#define x first
#define y second
#define all(a) (a).begin(), (a).end()

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;

const int maxn = (1 << 20);

int n;
int a[25];
int p[25];
int match[maxn];

int f(int x) {
	int ret = 0;
	for(int i = 0;i < n;i++)
		if(x & (1 << i))
			ret += (1 << p[i]);
	return ret;
}

int main() {
	scanf("%d", &n);
	for(int i = 0;i < n;i++)
		scanf("%d", a + i);

	int flag = 1;
	for(int i = 0;i < n;i++)
		if(a[i] & 1) flag = 0;

	if(!flag && n > 1) {
		printf("-1\n");
		return 0;
	}

	vector<ii> v;
	for(int i = 0;i < n;i++)
		v.pb({a[i], i});
	sort(all(v));
	reverse(all(v));
	vector<ii> ans;
	memset(match, -1, sizeof match);
	for(int i = n - 1;i >= 0;i--) {
		p[i] = v[i].y;
		for(int j = 0;j < (1 << n);j++) {
			if(v[i].x && match[j] == -1 && match[j ^ (1 << i)] == -1) {
				v[i].x--;
				match[j] = j ^ (1 << i);
				match[j ^ (1 << i)] = j;
				ans.pb({j, j ^ (1 << i)});
			}
		}
	}

	for(auto [x, y] : ans)
		printf("%d %d\n", f(x), f(y));
	return 0;
}