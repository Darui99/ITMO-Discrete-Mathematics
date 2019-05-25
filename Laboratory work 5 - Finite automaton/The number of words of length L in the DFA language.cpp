/*─────────▄──────────────▄
────────▌▒█───────────▄▀▒▌
────────▌▒▒▀▄───────▄▀▒▒▒▐
───────▐▄▀▒▒▀▀▀▀▄▄▄▀▒▒▒▒▒▐
─────▄▄▀▒▒▒▒▒▒▒▒▒▒▒█▒▒▄█▒▐
───▄▀▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▀██▀▒▌
──▐▒▒▒▄▄▄▒▒▒▒▒▒▒▒▒▒▒▒▒▀▄▒▒▌
──▌▒▒▐▄█▀▒▒▒▒▄▀█▄▒▒▒▒▒▒▒█▒▐
─▐▒▒▒▒▒▒▒▒▒▒▒▌██▀▒▒▒▒▒▒▒▒▀▄▌
─▌▒▀▄██▄▒▒▒▒▒▒▒▒▒▒▒░░░░▒▒▒▒▌
─▌▀▐▄█▄█▌▄▒▀▒▒▒▒▒▒░░░░░░▒▒▒▐
▐▒▀▐▀▐▀▒▒▄▄▒▄▒▒▒▒▒░░░░░░▒▒▒▒▌
▐▒▒▒▀▀▄▄▒▒▒▄▒▒▒▒▒▒░░░░░░▒▒▒▐
─▌▒▒▒▒▒▒▀▀▀▒▒▒▒▒▒▒▒░░░░▒▒▒▒▌
─▐▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▐
──▀▄▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▄▒▒▒▒▌
────▀▄▒▒▒▒▒▒▒▒▒▒▄▄▄▀▒▒▒▒▄▀
───▐▀▒▀▄▄▄▄▄▄▀▀▀▒▒▒▒▒▄▄▀*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll mod = (ll)1e+9 + 7ll;

int main() {
    freopen("problem4.in", "r", stdin);
    freopen("problem4.out", "w", stdout);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	int n, m, k, l;
	cin >> n >> m >> k >> l;

	vector <int> term(k);
	for (int i = 0; i < k; i++) {
		cin >> term[i];
		term[i]--;
	}

	vector < vector < pair<int, char> > > g(n);

	int a, b; char c;
	for (int i = 0; i < m; i++) {
		cin >> a >> b >> c;
		g[a - 1].push_back(make_pair(b - 1, c));
	}

	vector < vector<ll> > dp(2, vector<ll>(n));
	dp[0][0] = 1ll;

	for (int i = 0; i < l; i++) {
		for (int j = 0; j < n; j++)
			dp[1][j] = 0ll;
		for (int j = 0; j < n; j++) {
			for (int z = 0; z < (int)g[j].size(); z++) {
				int to = g[j][z].first;
				dp[1][to] = (dp[1][to] + dp[0][j]) % mod;
			}
		}
		dp[0].swap(dp[1]);
	}

	ll ans = 0ll;
	for (int i = 0; i < k; i++) {
		ans = (ans + dp[0][term[i]]) % mod;
	}

	cout << ans;

	return 0;
}
