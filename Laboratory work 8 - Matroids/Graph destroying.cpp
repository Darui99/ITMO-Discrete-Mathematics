#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

vector <int> p, sz;

int get(int v) {
	if (p[v] != v)
		p[v] = get(p[v]);
	return p[v];
}

void join(int v, int u) {
	v = get(v);
	u = get(u);

	if (v == u)
		return;

	if (sz[v] < sz[u])
		swap(v, u);
	p[u] = v;
	sz[v] += sz[u];
}

int main() {
    freopen("destroy.in", "r", stdin);
    freopen("destroy.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    ll n, m, s;
	cin >> n >> m >> s;

	p.resize(n);
	sz.resize(n);

	for (int i = 0; i < n; i++) {
		p[i] = i;
		sz[i] = 1;
	}

	vector < vector<ll> > arr(m, vector<ll>(4));
	for (int i = 0; i < m; i++) {
		cin >> arr[i][1] >> arr[i][2] >> arr[i][0];
		arr[i][1]--; arr[i][2]--;
		arr[i][3] = i;
	}
	sort(arr.begin(), arr.end());
	reverse(arr.begin(), arr.end());

	vector <bool> ans(m, true);
	for (int i = 0; i < m; i++) {
		if (get(arr[i][1]) == get(arr[i][2]))
			continue;
		join(arr[i][1], arr[i][2]);
		ans[arr[i][3]] = false;
	}
	ll sum = 0ll;
	for (int i = 0; i < m; i++) {
		if (!ans[arr[i][3]])
			continue;
		sum += arr[i][0];
	}
	for (int i = 0; i < m; i++) {
		if (!ans[arr[i][3]])
			continue;
		if (sum <= s)
			break;
		ans[arr[i][3]] = false;
		sum -= arr[i][0];
	}

	vector <int> del;
	for (int i = 0; i < m; i++) {
		if (ans[i])
			del.push_back(i);
	}

	cout << (int)del.size() << '\n';
	for (int i = 0; i < (int)del.size(); i++)
		cout << del[i] + 1 << " ";
	
	return 0;
}
