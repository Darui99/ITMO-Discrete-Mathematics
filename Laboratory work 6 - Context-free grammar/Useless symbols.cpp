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

vector <bool> usefull;
vector < vector< vector<int> > > g;
vector < vector<bool> > bad;
vector <int> color;

bool any;

void dfs(int v) {
	color[v] = 1;
	for (int i = 0; i < (int)g[v].size(); i++) {
		if (bad[v][i])
			continue;
		bool flag = true;
		vector <int> tos = g[v][i];
		for (int j = 0; j < (int)tos.size(); j++) {
			int to = tos[j];
			if (color[to] == 0)
				dfs(to);
			flag &= usefull[to];
		}
		if (!usefull[v] && flag)
			any = true;
		usefull[v] = usefull[v] | flag;
	}
	color[v] = 2;
}

int main() {
    freopen("useless.in", "r", stdin);
    freopen("useless.out", "w", stdout);
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
	int numeric = 0;
	num[(int)(start - 'A')] = numeric++;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < (int)arr[i].size(); j++) {
			if ('A' <= arr[i][j] && arr[i][j] <= 'Z') {
				if (num[(int)(arr[i][j] - 'A')] == -1)
					num[(int)(arr[i][j] - 'A')] = numeric++;
			}
		}
	}

	n = numeric + 1;

	g.resize(n);
	usefull.resize(n);
	color.resize(n);
	bad.resize(n);

	for (int i = 0; i < (int)arr.size(); i++) {
		vector <int> edges;
		for (int j = 1; j < (int)arr[i].size(); j++) {
			if ('A' <= arr[i][j] && arr[i][j] <= 'Z') {
				edges.push_back(num[(int)(arr[i][j] - 'A')]);
			}
		}
		if (edges.empty()) {
			usefull[num[(int)(arr[i][0] - 'A')]] = true;
		}
		else {
			g[num[(int)(arr[i][0] - 'A')]].push_back(edges);
		}
	}

	for (int i = 0; i < n; i++)
		bad[i].resize((int)g[i].size());

	while (true) {
		any = false;
		for (int i = 0; i < n; i++)
			color[i] = 0;
		for (int i = 0; i < n; i++) {
			if (color[i] == 0)
				dfs(i);
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

	dfs(0);

	for (int i = 0; i < alph; i++) {
		if (num[i] >= 0 && (!usefull[num[i]] || color[num[i]] == 0))
			cout << (char)(i + 'A') << " ";
	}

	return 0;
}
