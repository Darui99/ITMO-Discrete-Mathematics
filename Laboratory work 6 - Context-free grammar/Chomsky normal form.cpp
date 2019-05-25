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

const int alph = 26;
const int MAXN = 105;

const ll mod = (ll)1e+9 + 7ll;

ll dp[MAXN][MAXN][MAXN];

int main() {
    freopen("nfc.in", "r", stdin);
    freopen("nfc.out", "w", stdout);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	int n;
	char start;

	cin >> n >> start;

	string s;
	getline(cin, s);
	vector <string> arr(n);
	for (int i = 0; i < n; i++)
		getline(cin, arr[i]);

	vector <int> num(alph, -1);
	int numeric = 0;
	num[(int)(start - 'A')] = numeric++;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < (int)arr[i].size(); j++) {
			if ('A' <= arr[i][j] && arr[i][j] <= 'Z') {
				if (num[(int)(arr[i][j] - 'A')] == -1)
					num[(int)(arr[i][j] - 'A')] = numeric++;
			}
		}
	}

	n = numeric + 1;

	cin >> s;

	int m = (int)s.size();

	vector < vector < pair <int, int> > > g(n);

	for (int i = 0; i < (int)arr.size(); i++) {
		if ((int)arr[i].size() == 6) {
			for (int j = 0; j < m; j++) {
				if (s[j] == arr[i].back())
					dp[num[(int)(arr[i][0] - 'A')]][0][j] = 1ll;
			}
		}
		else {
			g[num[(int)(arr[i][0] - 'A')]].push_back(make_pair(num[(int)(arr[i][5] - 'A')], num[(int)(arr[i][6] - 'A')]));
		}
	}

	for (int len = 1; len < m; len++) {
		for (int l = 0; l + len < m; l++) {
			int r = l + len;
			for (int k = l; k < r; k++) {
				for (int i = 0; i < n; i++) {
					for (int j = 0; j < (int)g[i].size(); j++) {
						dp[i][len][l] = (dp[i][len][l] + dp[g[i][j].first][k - l][l] * dp[g[i][j].second][r - k - 1][k + 1] % mod) % mod;
					}
				}
			}
		}
	}

	cout << dp[0][m - 1][0];

	return 0;
}
