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

const int MAXN = 45;

ll dp[MAXN][MAXN], cnt, k = 0ll;

int n;
string s = "";
stack <char> q;

void rec(int pos, int d) {
	if (pos == 2 * n + 1) {
		cout << k;
		exit(0);
	}
	if (s[pos] == '(') {
		q.push(s[pos]);
		rec(pos + 1, d + 1);
	}
	k += dp[2 * n - pos][d + 1] * (1ll << ((2 * n - pos - d - 1) / 2ll));
	if (s[pos] == ')') {
		q.pop();
		rec(pos + 1, d - 1);
	} else {
		if (!q.empty() && q.top() == '(')
			k += dp[2 * n - pos][d - 1] * (1ll << ((2 * n - pos - d + 1) / 2ll));
	}
	if (s[pos] == '[') {
		q.push(s[pos]);
		rec(pos + 1, d + 1);
	}
	k += dp[2 * n - pos][d + 1] * (1ll << ((2 * n - pos - d - 1) / 2ll));
	if (s[pos] == ']') {
		q.pop();
		rec(pos + 1, d - 1);
	} else {
		if (!q.empty() && q.top() == '[')
			k += dp[2 * n - pos][d - 1] * (1ll << ((2 * n - pos - d + 1) / 2ll));
	}
}

int main() {
    freopen("brackets2num2.in", "r", stdin);
    freopen("brackets2num2.out", "w", stdout);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	dp[0][0] = 1ll;
	for (int i = 0; i < MAXN - 1; i++) {
		for (int j = 0; j < MAXN; j++) {
			if (j < MAXN - 1)
				dp[i + 1][j + 1] += dp[i][j];
			if (j > 0)
				dp[i + 1][j - 1] += dp[i][j];
		}
	}

	cin >> s;
	n = (int)s.size() / 2;
	s = "$" + s;

	rec(1, 0);
		
	return 0;
}
