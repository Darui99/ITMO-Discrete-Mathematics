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

ll dp[MAXN][MAXN], cnt;

int n;
string ans = "";
stack <char> q;

void rec(int pos, int d, ll k) {
	if (pos == 2 * n + 1) {
		return;
	}
	cnt = dp[2 * n - pos][d + 1] * (1ll << ((2 * n - pos - d - 1) / 2ll));
	if (cnt > k) {
		ans.push_back('(');
		q.push('(');
		rec(pos + 1, d + 1, k);
		return;
	}
	k -= cnt;
	if (d > 0 && q.top() == '(') {
		cnt = dp[2 * n - pos][d - 1] * (1ll << ((2 * n - pos - d + 1) / 2ll));
		if (cnt > k) {
			ans.push_back(')');
			q.pop();
			rec(pos + 1, d - 1, k);
			return;
		}
		k -= cnt;
	}
	//---
	cnt = dp[2 * n - pos][d + 1] * (1ll << ((2 * n - pos - d - 1) / 2ll));
	if (cnt > k) {
		ans.push_back('[');
		q.push('[');
		rec(pos + 1, d + 1, k);
		return;
	}
	k -= cnt;
	if (d > 0 && q.top() == '[') {
		cnt = dp[2 * n - pos][d - 1] * (1ll << ((2 * n - pos - d + 1) / 2ll));
		if (cnt > k) {
			ans.push_back(']');
			q.pop();
			rec(pos + 1, d - 1, k);
			return;
		}
		k -= cnt;
	}
}

int main() {
    freopen("num2brackets2.in", "r", stdin);
    freopen("num2brackets2.out", "w", stdout);
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

	ll k;
	cin >> n >> k;
	rec(1, 0, k);
	cout << ans;
		
	return 0;
}
