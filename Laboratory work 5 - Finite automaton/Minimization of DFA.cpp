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

vector < vector<int> > g;
vector < vector < vector<int> > > trans;
vector <int> color;

void dfs(int v) {
	color[v] = 1;
	for (int i = 0; i < (int)g[v].size(); i++) {
		int to = g[v][i];
		if (to == -1)
			continue;
		if (color[to] == 0)
			dfs(to);
	}
	color[v] = 2;
}

int main() {
    freopen("minimization.in", "r", stdin);
    freopen("minimization.out", "w", stdout);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	int n, m, k, x, a, b;

	cin >> n >> m >> k;
	n++;

	vector <int> term(k);
	vector <bool> is_term(n);

	for (int i = 0; i < k; i++) {
		cin >> x;
		term[i] = x - 1;
		is_term[x - 1] = true;
	}

	g.resize(n);
	trans.resize(n);

	for (int i = 0; i < n; i++) {
		g[i].resize(alph, -1);
		trans[i].resize(alph);
	}
	color.resize(n);

	char c;
	for (int i = 0; i < m; i++) {
		cin >> a >> b >> c;
		a--; b--;
		g[a][(int)(c - 'a')] = b;
		trans[b][(int)(c - 'a')].push_back(a);
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < alph; j++) {
			if (g[i][j] == -1) {
				g[i][j] = n - 1;
				trans[n - 1][j].push_back(i);
			}
		}
	}

	dfs(0);

	vector < vector<bool> > equal(n, vector<bool>(n, true));

	queue <int> q;
	vector <int> d(n * n, (int)1e+9);

	for (int i = 0; i < n; i++) {
		if (color[i] == 0)
			continue;
		for (int j = 0; j < n; j++) {
			if (color[j] == 0 || i == j)
				continue;
			if (is_term[i] != is_term[j]) {
				q.push(i * n + j);
				d[i * n + j] = 0;
				equal[i][j] = equal[j][i] = false;
			}
		}
	}

	while (!q.empty()) {
		int v = q.front();
		q.pop();

		int x = v / n, y = v % n, tox, toy, to;

		for (int i = 0; i < alph; i++) {
			for (int zx = 0; zx < (int)trans[x][i].size(); zx++) {
				for (int zy = 0; zy < (int)trans[y][i].size(); zy++) {
					tox = trans[x][i][zx], toy = trans[y][i][zy];
					if (color[tox] == 0 || color[toy] == 0)
						continue;
					to = tox * n + toy;
					if (d[to] > d[v] + 1) {
						d[to] = d[v] + 1;
						q.push(to);
						equal[tox][toy] = equal[toy][tox] = false;
					}
				}
			}
		}
	}

	vector <int> comp(n);
	int cur_comp = 0;

	for (int i = 0; i < n; i++) {
		if (comp[i] != 0 || color[i] == 0)
			continue;
		cur_comp++;
		comp[i] = cur_comp;
		for (int j = 0; j < n; j++) {
			if (equal[i][j] && color[j] != 0)
				comp[j] = cur_comp;
		}
	}

	vector <int> ansterm;
	for (int i = 0; i < k; i++) {
		if (color[term[i]] == 0)
			continue;
		ansterm.push_back(comp[term[i]]);
	}

	sort(ansterm.begin(), ansterm.end());
	ansterm.resize(unique(ansterm.begin(), ansterm.end()) - ansterm.begin());

	vector < pair< pair<int, int>, char> > ans, normans;
	for (int i = 0; i < n; i++) {
		if (color[i] == 0)
			continue;
		for (int j = 0; j < alph; j++) {
			if (g[i][j] == -1 || color[g[i][j]] == 0)
				continue;
			ans.push_back(make_pair(make_pair(comp[i], comp[g[i][j]]), (char)(j + 'a')));
		}
	}

	sort(ans.begin(), ans.end());
	ans.resize(unique(ans.begin(), ans.end()) - ans.begin());

	g.clear();
	color.clear();

	n = cur_comp;

	g.resize(n);
	color.resize(n);

	for (int i = 0; i < (int)ans.size(); i++) {
		g[ans[i].first.second - 1].push_back(ans[i].first.first - 1);
	}

	for (int i = 0; i < (int)ansterm.size(); i++) {
		if (color[ansterm[i] - 1] == 0)
			dfs(ansterm[i] - 1);
	}

	for (int i = 0; i < (int)ans.size(); i++) {
		if (color[ans[i].first.first - 1] == 0 || color[ans[i].first.second - 1] == 0)
			continue;
		normans.push_back(ans[i]);
	}

	ans.swap(normans);

	vector <int> numbers;
	for (int i = 0; i < (int)ans.size(); i++) {
		numbers.push_back(ans[i].first.first);
		numbers.push_back(ans[i].first.second);
	}

	for (int i = 0; i < (int)ansterm.size(); i++)
		numbers.push_back(ansterm[i]);

	sort(numbers.begin(), numbers.end());
	numbers.resize(unique(numbers.begin(), numbers.end()) - numbers.begin());

	for (int i = 0; i < (int)ans.size(); i++) {
		ans[i].first.first = (lower_bound(numbers.begin(), numbers.end(), ans[i].first.first) - numbers.begin()) + 1;
		ans[i].first.second = (lower_bound(numbers.begin(), numbers.end(), ans[i].first.second) - numbers.begin()) + 1;
	}

	for (int i = 0; i < (int)ansterm.size(); i++)
		ansterm[i] = (lower_bound(numbers.begin(), numbers.end(), ansterm[i]) - numbers.begin()) + 1;

	n = (int)numbers.size();

	cout << max(n, 1) << " " << ans.size() << " " << ansterm.size() << '\n';
	for (int i = 0; i < (int)ansterm.size(); i++) {
		cout << ansterm[i] << " ";
	}
	cout << '\n';

	for (int i = 0; i < (int)ans.size(); i++) {
		cout << ans[i].first.first << " " << ans[i].first.second << " " << ans[i].second << '\n';
	}

	return 0;
}
