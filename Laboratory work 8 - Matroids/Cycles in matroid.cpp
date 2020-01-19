#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    freopen("cycles.in", "r", stdin);
    freopen("cycles.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n, m;
	cin >> n >> m;

	vector <ll> w(n);
	for (int i = 0; i < n; i++)
		cin >> w[i];

	vector <bool> arr((1 << n));
	for (int i = 0; i < m; i++) {
		ll cw = 0ll;
		int sz, cur = 0, x;
		cin >> sz;
		while (sz--) {
			cin >> x;
			x--;
			cw += w[x];
			cur |= (1 << x);
		}
		arr[cur] = true;
	}

	for (int i = 0; i < (1 << n); i++) {
		for (int j = 0; j < n; j++) {
			if ((1 << j) & i)
				arr[i] = arr[i] | arr[i - (1 << j)];
		}
	}

	ll ans = 0ll;
	for (int i = 0; i < (1 << n); i++) {
		if (arr[i])
			continue;
		ll cur = 0ll;
		for (int j = 0; j < n; j++) {
			if ((1 << j) & i)
				cur += w[j];
		}
		ans = max(ans, cur);
	}
	cout << ans;
	
	return 0;
}
