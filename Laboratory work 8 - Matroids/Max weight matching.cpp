#include <bits/stdc++.h>
using namespace std;

vector < vector<int> > g;
vector <int> match;
vector <bool> used;

bool dfs(int v) {
	if (used[v])
		return false;
	used[v] = true;
	for (int i = 0; i < (int)g[v].size(); i++) {
		int to = g[v][i];
		if (match[to] == -1 || dfs(match[to])) {
			match[to] = v;
			return true;
		}
	}
	return false;
}

inline void kuhn(int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			used[j] = false;
		dfs(i);
	}
}

int main() {
    freopen("matching.in", "r", stdin);
    freopen("matching.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n;
	cin >> n;

	g.resize(n);
	used.resize(n);
	match.resize(n, -1);

	vector < pair<int, int> > arr(n);
	for (int i = 0; i < n; i++) {
		cin >> arr[i].first;
		arr[i].second = i;
	}
	sort(arr.begin(), arr.end());
	reverse(arr.begin(), arr.end());

	vector <int> num(n);
	for (int i = 0; i < n; i++)
		num[arr[i].second] = i;

	for (int i = 0; i < n; i++) {
		int sz, x;
		cin >> sz;
		while (sz--) {
			cin >> x;
			x--;
			g[num[i]].push_back(x);
		}
	}

	kuhn(n);

	vector <int> ans(n, -1);
	for (int i = 0; i < n; i++) {
		if (match[i] != -1)
			ans[match[i]] = i;
	}
	for (int i = 0; i < n; i++)
		cout << ans[num[i]] + 1 << " ";
	
	return 0;
}
