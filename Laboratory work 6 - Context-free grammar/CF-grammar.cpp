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

const int alph = 55;

vector < vector < vector<int> > > g;
vector < vector<bool> > bad;
vector <bool> eps, usefull;
vector <int> color;

bool any;

void dfs_eps(int v) {
	color[v] = 1;
	for (int i = 0; i < (int)g[v].size(); i++) {
		bool flag = true;
		vector <int> tos = g[v][i];
		for (int j = 0; j < (int)tos.size(); j++) {
			int to = tos[j];
			if (color[to] == 0)
				dfs_eps(to);
			flag &= eps[to];
		}
		if (!eps[v] && flag)
			any = true;
		eps[v] = eps[v] | flag;
	}
	color[v] = 2;
}

void dfs_usefull(int v) {
	color[v] = 1;
	for (int i = 0; i < (int)g[v].size(); i++) {
		if (bad[v][i])
			continue;
		bool flag = true;
		vector <int> tos = g[v][i];
		for (int j = 0; j < (int)tos.size(); j++) {
			int to = tos[j];
			if (color[to] == 0)
				dfs_usefull(to);
			flag &= usefull[to];
		}
		if (!usefull[v] && flag)
			any = true;
		usefull[v] = usefull[v] | flag;
	}
	color[v] = 2;
}

void dfs_st(int v) {
	color[v] = 1;
	for (int i = 0; i < (int)g[v].size(); i++) {
		if (bad[v][i])
			continue;
		vector <int> tos = g[v][i];
		for (int j = 0; j < (int)tos.size(); j++) {
			int to = tos[j];
			if (color[to] == 0)
				dfs_usefull(to);
		}
	}
	color[v] = 2;
}

int main() {
    freopen("cf.in", "r", stdin);
    freopen("cf.out", "w", stdout);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	int n;
	char start;

	cin >> n >> start;

	string s;
	getline(cin, s);
	vector <string> arr(n);
	for (int i = 0; i < n; i++)
		getline(cin, arr[i]);

	vector <int> num(alph, -1);
	vector <char> reversi;
	int numeric = 0;
	num[(int)(start - 'A')] = numeric++;
	reversi.push_back(start);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < (int)arr[i].size(); j++) {
			if (1 <= j && j <= 4)
				continue;
			if ('a' <= arr[i][j] && arr[i][j] <= 'z')
				arr[i][j] = (char)('A' + (int)(arr[i][j] - 'a') + 26);
			if (num[(int)(arr[i][j] - 'A')] == -1) {
				num[(int)(arr[i][j] - 'A')] = numeric++;
				reversi.push_back(arr[i][j]);
			}
		}
	}
	reversi.push_back(0);
	n = numeric + 1;

	g.resize(n);

	for (int i = 0; i < (int)arr.size(); i++) {
		if ((int)arr[i].size() == 4) {
			g[num[(int)(arr[i][0] - 'A')]].push_back(vector<int>(1, numeric));
			continue;
		}
		vector <int> edges;
		for (int j = 5; j < (int)arr[i].size(); j++) {
			edges.push_back(num[(int)(arr[i][j] - 'A')]);
		}
		g[num[(int)(arr[i][0] - 'A')]].push_back(edges);
	}

	//---------------------------------------------------------------------------------------------------------------------------
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < (int)g[i].size(); j++) {
			if ((int)g[i][j].size() <= 2)
				continue;
			int pf = (int)g.size();
			for (int k = 1; k < (int)g[i][j].size() - 2; k++) {
				g.push_back(vector < vector<int> >(1, {g[i][j][k], (int)g.size() + 1}));
			}
			g.push_back(vector < vector<int> >(1, { g[i][j][(int)g[i][j].size() - 2], g[i][j][(int)g[i][j].size() - 1] }));
			while ((int)g[i][j].size() > 1)
				g[i][j].pop_back();
			g[i][j].push_back(pf);
		}
	}
	//---------------------------------------------------------------------------------------------------------------------------

	n = (int)g.size();

	eps.resize(n);
	color.resize(n);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < (int)g[i].size(); j++) {
			if ((int)g[i][j].size() == 1 && g[i][j][0] == numeric)
				eps[i] = true;
		}
	}

	while (true) {
		any = false;
		for (int i = 0; i < n; i++)
			color[i] = 0;
		for (int i = 0; i < n; i++) {
			if (color[i] == 0)
				dfs_eps(i);
		}
		if (!any)
			break;
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < (int)g[i].size(); j++) {
			if ((int)g[i][j].size() < 2)
				continue;
			if (eps[g[i][j][0]])
				g[i].push_back(vector<int>(1, g[i][j][1]));
			if (eps[g[i][j][1]])
				g[i].push_back(vector<int>(1, g[i][j][0]));
		}
	}

	bad.resize(n);

	for (int i = 0; i < n; i++) {
		bad[i].resize((int)g[i].size());
		for (int j = 0; j < (int)g[i].size(); j++) {
			if ((int)g[i][j].size() == 1 && g[i][j][0] == numeric)
				bad[i][j] = true;
		}
	}
	//---------------------------------------------------------------------------------------------------------------------------

	vector < vector<bool> > mat(n, vector<bool>(n));

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < (int)g[i].size(); j++) {
			if (bad[i][j])
				continue;
			if ((int)g[i][j].size() == 1)
				mat[i][g[i][j][0]] = true;
		}
	}

	for (int k = 0; k < n; k++) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				mat[i][j] = mat[i][j] | (mat[i][k] & mat[k][j]);
			}
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < (int)g[i].size(); j++) {
			if (bad[i][j])
				continue;
			if ((int)g[i][j].size() == 1)
				bad[i][j] = true;
		}
	}

	//---------------------------------------------------------------------------------------------------------------------------

	usefull.resize(n);

	vector < vector <char> > cansym(n);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (mat[i][j] && j < (int)reversi.size() && reversi[j] > 'Z') {
				cansym[i].push_back(reversi[j]);
				usefull[i] = true;
			}
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (mat[i][j] && i != j) {
				for (int k = 0; k < (int)g[j].size(); k++) {
					g[i].push_back(g[j][k]);
					bad[i].push_back(bad[j][k]);
				}
			}
		}
	}

	for (int i = 0; i < n; i++) {
		if (i < (int)reversi.size() && reversi[i] > 'Z') {
			cansym[i].push_back(reversi[i]);
			usefull[i] = true;
		}
	}

	while (true) {
		any = false;
		for (int i = 0; i < n; i++)
			color[i] = 0;
		for (int i = 0; i < n; i++) {
			if (color[i] == 0)
				dfs_usefull(i);
		}
		if (!any)
			break;
	}

	for (int i = 0; i < n; i++) {
		color[i] = 0;
		for (int j = 0; j < (int)g[i].size(); j++) {
			bool flag = true;
			for (int k = 0; k < (int)g[i][j].size(); k++)
				flag &= usefull[g[i][j][k]];
			if (!flag)
				bad[i][j] = true;
		}
	}

	dfs_st(0);
	for (int i = 0; i < n; i++) {
		if (color[i] == 0)
			usefull[i] = false;
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < (int)g[i].size(); j++) {
			bool flag = true;
			for (int k = 0; k < (int)g[i][j].size(); k++)
				flag &= usefull[g[i][j][k]];
			if (!flag)
				bad[i][j] = true;
		}
	}
	//---------------------------------------------------------------------------------------------------------------------------

	vector < vector < pair <int, int> > > gg(n);
	for (int i = 0; i < n; i++) {
		if (!usefull[i])
			continue;
		for (int j = 0; j < (int)g[i].size(); j++) {
			if (bad[i][j] || g[i][j].empty())
				continue;
			gg[i].push_back(make_pair(g[i][j][0], g[i][j][1]));
		}
	}

	for (int i = 0; i < (int)cansym.size(); i++) {
		for (int j = 0; j < (int)cansym[i].size(); j++)
			cansym[i][j] = cansym[i][j] - 26 - 'A' + 'a';
	}

	cin >> s;
	int m = (int)s.size();

	vector < vector < vector<bool> > > dp(n, vector < vector<bool> >(m, vector<bool>(m)));

	for (int i = 0; i < (int)cansym.size(); i++) {
		if (!usefull[i])
			continue;
		for (int j = 0; j < (int)cansym[i].size(); j++) {
			for (int k = 0; k < m; k++) {
				if (s[k] == cansym[i][j])
					dp[i][0][k] = true;
			}
		}
	}

	for (int len = 1; len < m; len++) {
		for (int l = 0; l + len < m; l++) {
			int r = l + len;
			for (int k = l; k < r; k++) {
				for (int i = 0; i < n; i++) {
					for (int j = 0; j < (int)gg[i].size(); j++) {
						dp[i][len][l] = dp[i][len][l] | (dp[gg[i][j].first][k - l][l] & dp[gg[i][j].second][r - k - 1][k + 1]);
					}
				}
			}
		}
	}

	if (dp[0][m - 1][0])
		cout << "yes";
	else
		cout << "no";

	return 0;
}
