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

const ll mod = (ll)1e+9 + 7ll;

vector < vector<int> > g, trans;
vector <int> loop, color, ord, comp, sz, num, term;

void dfs(int v) {
	color[v] = 1;
	for (int i = 0; i < (int)g[v].size(); i++) {
		int to = g[v][i];
		if (color[to] == 0)
			dfs(to);
	}
	color[v] = 2;
	ord.push_back(v);
}

int cur_comp = 0;

void dfs0(int v) {
	color[v] = 1;

	comp[v] = cur_comp;
	sz[cur_comp]++;
	num[cur_comp] = v;

	for (int i = 0; i < (int)trans[v].size(); i++) {
		int to = trans[v][i];
		if (color[to] == 0)
			dfs0(to);
	}
	color[v] = 2;
}

int main() {
    freopen("problem3.in", "r", stdin);
    freopen("problem3.out", "w", stdout);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	int n, m, k;
	cin >> n >> m >> k;

	term.resize(k);
	for (int i = 0; i < k; i++) {
		cin >> term[i];
		term[i]--;
	}

	g.resize(n);
	trans.resize(n);
	loop.resize(n);
	color.resize(n);
	sz.resize(n);
	num.resize(n);
	comp.resize(n);

	int a, b; char c;
	for (int i = 0; i < m; i++) {
		cin >> a >> b >> c;
		g[a - 1].push_back(b - 1);
		trans[b - 1].push_back(a - 1);
		if (a == b)
			loop[a - 1] = true;
	}

	for (int i = 0; i < n; i++) {
		if (color[i] == 0)
			dfs(i);
	}

	for (int i = 0; i < n; i++)
		color[i] = 0;

	for (int i = n - 1; i >= 0; i--) {
		int now = ord[i];
		if (color[now] == 0) {
			dfs0(now);
			cur_comp++;
		}
	}

	vector <bool> can(cur_comp);
	can[comp[0]] = true;

	for (int i = n - 1; i >= 0; i--) {
		int now = ord[i];
		for (int j = 0; j < (int)g[now].size(); j++) {
			int to = comp[g[now][j]];
			can[to] = can[to] | can[comp[now]];
		}
	}

	vector <bool> cycle(cur_comp);
	for (int i = 0; i < cur_comp; i++) {
		cycle[i] = ((sz[i] > 1 || loop[num[i]]) && can[i]);
	}

	for (int i = n - 1; i >= 0; i--) {
		int now = ord[i];
		for (int j = 0; j < (int)g[now].size(); j++) {
			int to = comp[g[now][j]];
			cycle[to] = cycle[to] | cycle[comp[now]];
		}
	}

	for (int i = 0; i < k; i++) {
		if (cycle[comp[term[i]]]) {
			cout << -1;
			return 0;
		}
	}

	vector <ll> dp(cur_comp);
	dp[comp[0]] = 1ll;

	for (int i = n - 1; i >= 0; i--) {
		int now = ord[i];
		for (int j = 0; j < (int)g[now].size(); j++) {
			int to = comp[g[now][j]];
			if (to == comp[now])
				continue;
			dp[to] = (dp[to] + dp[comp[now]]) % mod;
		}
	}

	ll ans = 0ll;
	for (int i = 0; i < k; i++)
		ans = (ans + dp[comp[term[i]]]) % mod;
	cout << ans;

	return 0;
}
