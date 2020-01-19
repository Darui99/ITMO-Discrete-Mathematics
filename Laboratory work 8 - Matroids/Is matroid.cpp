#include <bits/stdc++.h>
using namespace std;

int popcnt(int x) {
	int res = 0;
	while (x) {
		x &= (x - 1);
		res++;
	}
	return res;
}

int main() {
    freopen("check.in", "r", stdin);
    freopen("check.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n, m;
	cin >> n >> m;

	vector <bool> arr((1 << n));
	for (int i = 0; i < m; i++) {
		int sz, cur = 0, x;
		cin >> sz;
		while (sz--) {
			cin >> x;
			x--;
			cur |= (1 << x);
		}
		arr[cur] = true;
	}

	if (!arr[0]) {
		cout << "NO";
		return 0;
	}

	for (int i = 0; i < (1 << n); i++) {
		for (int j = 0; j < (1 << n); j++) {
			if ((i & j) == i && !arr[i] && arr[j]) {
				cout << "NO";
				return 0;
			}
		}
	}

	for (int i = 0; i < (1 << n); i++) {
		if (!arr[i])
			continue;
		for (int j = 0; j < (1 << n); j++) {
			if (!arr[j] || popcnt(i) >= popcnt(j))
				continue;
			int dif = (j & (~i));
			bool any = false;
			for (int k = 0; k < n; k++) {
				if ((1 << k) & dif)
					any |= arr[i + (1 << k)];
			}
			if (!any) {
				cout << "NO";
				return 0;
			}
		}
	}
	cout << "YES";
	
	return 0;
}
