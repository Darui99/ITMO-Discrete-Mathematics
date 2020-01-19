#include <bits/stdc++.h>
using namespace std;

const int inf = (int)1e+9 + 7;

struct edge {
	int a, b, c, num;
};

int N, M;
vector <edge> st;

vector <bool> cl;
vector < vector< pair<int, int> > > tr;
vector < pair<int, int> > par;
vector <int> tr_num;

void dfs(int v, int p, int pn, int num) {
	tr_num[v] = num;
	par[v] = make_pair(p, pn);
	for (int i = 0; i < (int)tr[v].size(); i++) {
		int to = tr[v][i].first, ton = tr[v][i].second;
		if (to == p)
			continue;
		dfs(to, v, ton, num);
	}
}

void init() {
	int n = (int)cl.size();
	par.clear();
	par.resize(n);
	tr_num.clear();
	tr_num.resize(n, -1);

	int numeric = 0;
	for (int i = 0; i < n; i++) {
		if (cl[i] && tr_num[i] == -1) {
			dfs(i, -1, -1, numeric);
			numeric++;
		}
	}
}

bool check(int k, bool t) {
	int n = N * k, m = M * k;

	cl.clear();
	cl.resize(n);
	tr.clear();
	tr.resize(n);

	vector <edge> arr(m);
	for (int j = 0; j < k; j++) {
		for (int i = 0; i < M; i++) {
			int num = j * M + i;
			arr[num] = st[i];
			arr[num].a += j * N;
			arr[num].b += j * N;
			arr[num].num = num;
			arr[num].c = i;
		}
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

	if (t) {
		vector < vector<int> > nas(k);
		for (int i = 0; i < (int)ans.size(); i++)
			nas[ans[i] / M].push_back(arr[ans[i]].num % M);
		cout << k << '\n';
		for (int i = 0; i < k; i++) {
			for (int j = 0; j < N - 1; j++)
				cout << nas[i][j] + 1 << ' ';
			cout << '\n';
		}
	}

	return ((int)ans.size() == (N - 1) * k);
}

int main() {
    freopen("multispan.in", "r", stdin);
    freopen("multispan.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> N >> M;

	st.resize(M);
	for (int i = 0; i < M; i++) {
		cin >> st[i].a >> st[i].b;
		st[i].a--; st[i].b--;
		st[i].num = i;
	}

	int l = 0, r = M / (N - 1) + 1;
	while (r - l > 1) {
		int mid = (l + r) / 2;
		if (check(mid, false))
			l = mid;
		else
			r = mid;
	}

	check(l, true);
	
	return 0;
}