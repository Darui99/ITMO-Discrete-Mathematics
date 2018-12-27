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
ll dp[MAXN][MAXN];
int n, m;
vector <int> arr;
ll k = 0ll;

void rec(int pos, int sum) {
	if (pos == m) {
		cout << k;
		exit(0);
	}
	int prev = 1;
	if (pos > 0)
		prev = arr[pos - 1];
	for (int i = prev; i <= n - sum; i++) {
		if (arr[pos] == i) {
			rec(pos + 1, sum + i);
		} else {
			k += dp[n - sum][i] - dp[n - sum][i + 1];
		}
	}
}

int convert(const string &s) {
	int res = 0;
	for (int i = (int)s.size() - 1, r = 1; i >= 0; i--, r *= 10)
		res += (int)(s[i] - '0') * r;
	return res;
}
 
int main() {
    freopen("part2num.in", "r", stdin);
    freopen("part2num.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
 
    string s;
	cin >> s;

	string now = "";

	for (int i = 0; i < (int)s.size(); i++) {
		if (s[i] < '0' || s[i] > '9') {
			arr.push_back(convert(now));
			now = "";
			continue;
		}
		now.push_back(s[i]);
	}
	if (!now.empty())
		arr.push_back(convert(now));
	m = (int)arr.size();
	
	for (int i = 0; i < MAXN; i++)
		dp[0][i] = 1ll;

	n = 0;
	for (int i = 0; i < m; i++)
		n += arr[i];

	for (int i = 1; i <= n; i++) {
		for (int j = i; j >= 1; j--) {
			dp[i][j] += dp[i][j + 1];
			dp[i][j] += dp[i - j][j];
		}
	}

	rec(0, 0);
 
    return 0;
}
