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

const int MAXN = 32;
ll C[MAXN][MAXN];

ll n, m;
vector <int> ans;

void rec(int pos, int prev, ll k) {
	if (pos == m) {
		return;
	}
	
	for (int i = prev + 1; i < n; i++) {
		ll cnt = C[n - i - 1][m - pos - 1];
		if (k < cnt) {
			ans.push_back(i);
			rec(pos + 1, i, k);
		} else {
			k -= cnt;
		}
	}
}

int main() {
    freopen("num2choose.in", "r", stdin);
    freopen("num2choose.out", "w", stdout);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	for (int i = 0; i < MAXN; i++)
		C[i][0] = 1ll;
	for (int i = 1; i < MAXN; i++) {
		for (int j = 1; j < MAXN; j++) {
			C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
		}
	}

	ll k;
	cin >> n >> m >> k;

	rec(0, -1, k);
	for (int i = 0; i < m; i++)
		cout << ans[i] + 1 << " ";
		
	return 0;
}
