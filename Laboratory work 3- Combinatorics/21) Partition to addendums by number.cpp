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
 
const int MAXN = 105;
ll dp[MAXN][MAXN], cnt;
vector <int> ans;

void rec(int n, int prev, ll k) {
	if (n == 0) {
		for (int i = 0; i < (int)ans.size() - 1; i++)
			cout << ans[i] << "+";
		cout << ans.back();
		exit(0);
	}

	for (int i = prev; i <= n; i++) {
		cnt = dp[n][i] - dp[n][i + 1];
		if (cnt > k) {
			ans.push_back(i);
			rec(n - i, i, k);
		} else {
			k -= cnt;
		}
	}
}
 
int main() {
    freopen("num2part.in", "r", stdin);
    freopen("num2part.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
 
    for (int i = 0; i < MAXN; i++)
		dp[0][i] = 1ll;

	int n;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		for (int j = i; j >= 1; j--) {
			dp[i][j] += dp[i][j + 1];
			dp[i][j] += dp[i - j][j];
		}
	}

	ll k;
	cin >> k;

	rec(n, 1, k);
 
    return 0;
}
