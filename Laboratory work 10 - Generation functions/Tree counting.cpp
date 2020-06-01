#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll mod = (ll)1e+9 + 7ll;
const int MAXN = 2005;

ll dp[MAXN], res[MAXN];

int main() {
    ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int n, m;
	cin >> n >> m;

	vector <int> arr(n);
	for (int i = 0; i < n; i++)
		cin >> arr[i];
	sort(arr.begin(), arr.end());

	dp[0] = 1ll;
	for (int i = 0; i < n; i++)
		dp[arr[i]] = 1ll;

	res[1] = dp[1] * 2ll;
	for (int i = 2; i <= m; i++) {
		for (int j = 0; j < n; j++) {
			int w = i - arr[j];
			if (w <= 0)
				break;
			dp[i] = (dp[i] + res[w]) % mod;
		}
		for (int z = 0; z <= i; z++) {
			int k = i - z;
			res[i] = (res[i] + dp[z] * dp[k] % mod) % mod;
		}
	}

	for (int i = 1; i <= m; i++)
		cout << dp[i] << ' ';

	return 0;
}
