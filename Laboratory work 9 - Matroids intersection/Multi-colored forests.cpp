#include <bits/stdc++.h>
using namespace std;

const int inf = (int)1e+9 + 7;

struct edge {
	int a, b, c, num;
};

vector <bool> cl;
vector < vector< pair<int, int> > > tr;
vector < pair<int, int> > par;
int timer = 1;
vector <int> tin, tout, tr_num;

void dfs(int v, int p, int pn, int num) {
	tr_num[v] = num;
	par[v] = make_pair(p, pn);
	tin[v] = timer++;
	for (int i = 0; i < (int)tr[v].size(); i++) {
		int to = tr[v][i].first, ton = tr[v][i].second;
		if (to == p)
			continue;
		dfs(to, v, ton, num);
	}
	tout[v] = timer++;
}

void init() {
	int n = (int)cl.size();
	par.clear();
	par.resize(n);
	tin.clear();
	tin.resize(n);
	tout.clear();
	tout.resize(n);
	tr_num.clear();
	tr_num.resize(n, -1);
	timer = 1;

	int numeric = 0;
	for (int i = 0; i < n; i++) {
		if (cl[i] && tr_num[i] == -1) {
			dfs(i, -1, -1, numeric);
			numeric++;
		}
	}
}

int main() {
    freopen("rainbow.in", "r", stdin);
    freopen("rainbow.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n, m;
	cin >> n >> m;

	cl.resize(n);
	tr.resize(n);

	vector <edge> arr(m);
	for (int i = 0; i < m; i++) {
		cin >> arr[i].a >> arr[i].b >> arr[i].c;
		arr[i].a--; arr[i].b--;
		arr[i].num = i;
	}

	unordered_set <int> col;
	vector <bool> used(m);

	while (true) {
		init();
		vector < vector<int> > g(m);
		vector <int> A, B;
		for (int i = 0; i < m; i++) {
			if (used[i])
				A.push_back(i);
			else
				B.push_back(i);
		}
		// exchange graph building
		for (int i = 0; i < (int)B.size(); i++) {
			int v = arr[B[i]].a, u = arr[B[i]].b, c = arr[B[i]].c;
			// I2 (rainbow)
			bool can = (col.count(c) == 0);
			for (int j = 0; j < (int)A.size(); j++) {
				if (arr[A[j]].c == c || can)
					g[B[i]].push_back(A[j]);
			}
			// I1 (graph)
			if (tr_num[v] == tr_num[u] && tr_num[v] != -1) {
				vector <int> cnt(m);
				int cur = v;
				while (par[cur].first != -1) {
					cnt[par[cur].second]++;
					cur = par[cur].first;
				}
				cur = u;
				while (par[cur].first != -1) {
					cnt[par[cur].second]++;
					cur = par[cur].first;
				}
				for (int j = 0; j < (int)A.size(); j++) {
					if (cnt[A[j]] == 1)
						g[A[j]].push_back(B[i]);
				}
			}
			else {
				for (int j = 0; j < (int)A.size(); j++)
					g[A[j]].push_back(B[i]);
			}
		}
		// finding P
		vector <bool> S(m), T(m);
		vector <int> d(m, inf);
		vector <int> bp(m, -1);
		queue <int> q;
		//// finding S and T
		for (int i = 0; i < (int)B.size(); i++) {
			int v = arr[B[i]].a, u = arr[B[i]].b, c = arr[B[i]].c;
			if (tr_num[v] != tr_num[u] || tr_num[v] == -1) {
				S[B[i]] = true;
				d[B[i]] = 0;
				q.push(B[i]);
				bp[B[i]] = -1;
			}
			if (col.count(c) == 0)
				T[B[i]] = true;
		}
		while (!q.empty()) {
			int v = q.front();
			q.pop();
			for (int i = 0; i < (int)g[v].size(); i++) {
				int to = g[v][i];
				if (d[to] > d[v] + 1) {
					d[to] = d[v] + 1;
					bp[to] = v;
					q.push(to);
				}
			}
		}
		int minu = inf, iminu = -1;
		for (int i = 0; i < m; i++) {
			if (!T[i])
				continue;
			if (d[i] < minu) {
				minu = d[i];
				iminu = i;
			}
		}
		if (minu == inf)
			break;
		vector <int> path;
		int cur = iminu;
		while (true) {
			path.push_back(cur);
			if (bp[cur] == -1)
				break;
			cur = bp[cur];
		}
		// Update A
		for (int i = 0; i < (int)path.size(); i++) {
			used[path[i]] = !used[path[i]];
		}
		cl.clear();
		cl.resize(n);
		tr.clear();
		tr.resize(n);
		col.clear();
		for (int i = 0; i < m; i++) {
			if (used[i]) {
				cl[arr[i].a] = cl[arr[i].b] = true;
				tr[arr[i].a].push_back(make_pair(arr[i].b, i));
				tr[arr[i].b].push_back(make_pair(arr[i].a, i));
				col.insert(arr[i].c);
			}
		}
	}

	vector <int> ans;
	for (int i = 0; i < m; i++) {
		if (used[i])
			ans.push_back(i);
	}

	cout << (int)ans.size() << '\n';
	for (int i = 0; i < (int)ans.size(); i++)
		cout << ans[i] + 1 << ' ';
	
	return 0;
}
