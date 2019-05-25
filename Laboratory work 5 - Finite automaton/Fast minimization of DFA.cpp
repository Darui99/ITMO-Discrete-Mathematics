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
    freopen("fastminimization.in", "r", stdin);
    freopen("fastminimization.out", "w", stdout);
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

	vector < unordered_set<int> > comps(3);
	queue < pair<unordered_set<int>, int> > q;
	map<int, vector<int> > compvers;

	int cur_comp = 3;
	vector <int> comp(n);

	for (int i = 0; i < n; i++) {
		if (color[i] == 0) {
			comps[0].insert(i);
			continue;
		}
		comp[i] = !is_term[i] + 1;
		comps[comp[i]].insert(i);
	}

	for (int i = 0; i < alph; i++) {
		q.push(make_pair(comps[1], i));
		q.push(make_pair(comps[2], i));
	}

	unordered_set<int> cc;

	while (!q.empty()) {
		cc = q.front().first;
		int sym = q.front().second;
		q.pop();

		compvers.clear();
		for (auto it = cc.begin(); it != cc.end(); it++) {
			int v = *it;
			for (int i = 0; i < (int)trans[v][sym].size(); i++) {
				int to = trans[v][sym][i];
				int toc = comp[to];
				compvers[toc].push_back(to);
			}
		}
		for (auto it = compvers.begin(); it != compvers.end(); it++) {
			if ((int)it->second.size() < (int)comps[it->first].size()) {
				cur_comp = (int)comps.size();
				while ((int)comps.size() <= cur_comp)
					comps.push_back(unordered_set<int>());
				for (int j = 0; j < (int)it->second.size(); j++) {
					comps[it->first].erase(it->second[j]);
					comps[cur_comp].insert(it->second[j]);
				}
				if ((int)comps[cur_comp].size() >(int)comps[it->first].size())
					comps[cur_comp].swap(comps[it->first]);
				for (auto jt = comps[cur_comp].begin(); jt != comps[cur_comp].end(); jt++)
					comp[*jt] = cur_comp;
				for (int j = 0; j < alph; j++)
					q.push(make_pair(comps[cur_comp], j));
			}
		}
	}

	if (comp[0] != 1) {
		int lol = comp[0];
		for (int i = 0; i < n; i++) {
			if (comp[i] == 1)
				comp[i] = lol;
			else if (comp[i] == lol)
				comp[i] = 1;
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
