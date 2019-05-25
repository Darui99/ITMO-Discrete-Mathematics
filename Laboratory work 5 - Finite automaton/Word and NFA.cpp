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

int main() {
    freopen("problem2.in", "r", stdin);
    freopen("problem2.out", "w", stdout);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	string s;
	cin >> s;

	int n, m, k;
	cin >> n >> m >> k;

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

	vector < vector<bool> > dp(2, vector<bool>(n));
	dp[0][0] = true;

	for (int i = 0; i < (int)s.size(); i++) {
		for (int j = 0; j < n; j++)
			dp[1][j] = false;
		for (int j = 0; j < n; j++) {
			for (int z = 0; z < (int)g[j].size(); z++) {
				int to = g[j][z].first;
				if (g[j][z].second == s[i])
					dp[1][to] = dp[1][to] | dp[0][j];
			}
		}
		dp[0].swap(dp[1]);
	}

	for (int i = 0; i < k; i++) {
		if (dp[0][term[i]]) {
			cout << "Accepts";
			return 0;
		}
	}

	cout << "Rejects";

	return 0;
}
