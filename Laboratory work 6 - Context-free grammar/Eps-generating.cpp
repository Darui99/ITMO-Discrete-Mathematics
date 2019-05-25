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

vector <int> eps;
vector < vector< vector<int> > > g;
vector <int> color;

void dfs(int v) {
	color[v] = 1;
	for (int i = 0; i < (int)g[v].size(); i++) {
		bool flag = true;
		vector <int> tos = g[v][i];
		for (int j = 0; j < (int)tos.size(); j++) {
			int to = tos[j];
			if (color[to] == 0)
				dfs(to);
			flag &= eps[to];
		}
		eps[v] |= flag;
	}
	color[v] = 2;
}

int main() {
    freopen("epsilon.in", "r", stdin);
    freopen("epsilon.out", "w", stdout);
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
	eps.resize(n);
	color.resize(n);

	for (int i = 0; i < (int)arr.size(); i++) {
		if ((int)arr[i].size() == 4)
			eps[num[(int)(arr[i][0] - 'A')]] = true;
	}

	for (int i = 0; i < (int)arr.size(); i++) {
		vector <int> edges;
		bool flag = true;
		for (int j = 1; j < (int)arr[i].size(); j++) {
			flag &= (arr[i][j] < 'a' || arr[i][j] > 'z');
			if ('A' <= arr[i][j] && arr[i][j] <= 'Z') {
				edges.push_back(num[(int)(arr[i][j] - 'A')]);
			}
		}
		if (flag)
			g[num[(int)(arr[i][0] - 'A')]].push_back(edges);
	}

	for (int i = 0; i < n; i++) {
		if (color[i] == 0)
			dfs(i);
	}

	for (int i = 0; i < alph; i++) {
		if (num[i] >= 0 && eps[num[i]])
			cout << (char)(i + 'A') << " ";
	}

	return 0;
}
