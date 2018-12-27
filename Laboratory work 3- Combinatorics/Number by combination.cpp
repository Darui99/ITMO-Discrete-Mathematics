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

ll n, m, k = 0ll;
vector <int> arr;

void rec(int pos, int prev) {
	if (pos == m) {
		cout << k;
		exit(0);
	}

	for (int i = prev + 1; i < n; i++) {
		ll cnt = C[n - i - 1][m - pos - 1];
		if (arr[pos] == i)
			rec(pos + 1, i);
		else
			k += cnt;
	}
}

int main() {
    freopen("choose2num.in", "r", stdin);
    freopen("choose2num.out", "w", stdout);
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

	cin >> n >> m;
	arr.resize(m);

	for (int i = 0; i < m; i++) {
		cin >> arr[i];
		arr[i]--;
	}

	rec(0, -1);
		
	return 0;
}
