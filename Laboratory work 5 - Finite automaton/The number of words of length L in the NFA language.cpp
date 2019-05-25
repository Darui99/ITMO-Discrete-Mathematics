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

#include <iostream>
#include <stdio.h>
#include <cmath>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <queue>
#include <deque>
#include <stack>
#include <string>
#include <bitset>
#include <ctime>
#include <random>
#include <unordered_map>
using namespace std;

typedef long long ll;

const int MAXN = 305;
const ll mod = (ll)1e+9 + 7ll;

bool operator<(const bitset<MAXN> &a, const bitset<MAXN> &b) {
	for (int i = 0; i < MAXN; i++) {
		if (a[i] == b[i])
			continue;
		if (a[i] < b[i])
			return true;
		if (a[i] > b[i])
			return false;
	}
	return false;
}

struct cmp {
	bool operator()(const bitset<MAXN> &a, const bitset<MAXN> &b) const {
		return a < b;
	}
};

int main() {
    freopen("problem5.in", "r", stdin);
    freopen("problem5.out", "w", stdout);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	int n, m, k, l, x, a, b;
	cin >> n >> m >> k >> l;

	vector <bool> oldterm(n);
	for (int i = 0; i < k; i++) {
		cin >> x;
		oldterm[x - 1] = true;
	}

	vector < vector < bitset<MAXN> > > p(MAXN, vector < bitset<MAXN> >(26));

	char c;
	for (int i = 0; i < m; i++) {
		cin >> a >> b >> c;
		a--; b--; x = (int)(c - 'a');
		p[a][x][b] = true;
	}

	int numeric = n;
	map <bitset<MAXN>, int, cmp> num;
	map <int, bitset<MAXN> > mask;

	bitset<MAXN> cur, ss;
	for (int i = 0; i < n; i++) {
		if (i > 0)
			cur[i - 1] = false;
		cur[i] = true;
		num[cur] = i;
		mask[i] = cur;
	}

	queue <int> q;
	vector <int> dist(MAXN, (int)1e+9);

	dist[0] = 0;
	q.push(0);

	vector < vector<int> > g(MAXN);

	while (!q.empty()) {
		int v = q.front();
		ss = mask[v];
		q.pop();


		for (int i = 0; i < 26; i++) {
			cur.reset();
			for (int j = 0; j < numeric; j++) {
				if (ss[j] == 0)
					continue;
				cur |= p[j][i];
			}
			if (cur.count() == 0)
				continue;
			if (num.count(cur) == 0) {
				num[cur] = numeric;
				mask[numeric] = cur;
				numeric++;
			}
			int to = num[cur];
			g[v].push_back(to);
			if (dist[to] > dist[v] + 1) {
				dist[to] = dist[v] + 1;
				q.push(to);
			}
		}
	}

	vector <int> term;
	for (int i = 0; i < numeric; i++) {
		cur = mask[i];
		for (int j = 0; j < n; j++) {
			if (cur[j] == 0)
				continue;
			if (oldterm[j]) {
				term.push_back(i);
				break;
			}
		}
	}

	n = numeric; k = (int)term.size();

	vector < vector<ll> > dp(2, vector<ll>(n));
	dp[0][0] = 1ll;

	for (int i = 0; i < l; i++) {
		for (int j = 0; j < n; j++)
			dp[1][j] = 0ll;
		for (int j = 0; j < n; j++) {
			for (int z = 0; z < (int)g[j].size(); z++) {
				int to = g[j][z];
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
