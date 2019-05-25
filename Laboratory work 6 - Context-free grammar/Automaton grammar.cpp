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

const int alph = 26;

int main() {
    freopen("automaton.in", "r", stdin);
    freopen("automaton.out", "w", stdout);
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
		if (num[(int)(arr[i][0] - 'A')] == -1)
			num[(int)(arr[i][0] - 'A')] = numeric++;
		if ((int)arr[i].size() == 7 && num[(int)(arr[i][6] - 'A')] == -1)
			num[(int)(arr[i][6] - 'A')] = numeric++;
	}

	n = numeric + 1;

	vector < vector < pair<int, char> > > g(n);

	for (int i = 0; i < (int)arr.size(); i++) {
		if ((int)arr[i].size() == 7) {
			g[num[(int)(arr[i][0] - 'A')]].push_back(make_pair(num[(int)(arr[i][6] - 'A')], arr[i][5]));
		} else {
			g[num[(int)(arr[i][0] - 'A')]].push_back(make_pair(n - 1, arr[i][5]));
		}
	}

	int q;
	cin >> q;

	while (q--) {
		cin >> s;

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

		if (dp[0][n - 1]) {
			cout << "yes\n";
		} else {
			cout << "no\n";
		}
	}

	return 0;
}
