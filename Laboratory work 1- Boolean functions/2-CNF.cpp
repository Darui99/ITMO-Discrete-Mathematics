#include <bits/stdc++.h>
using namespace std;

vector < vector<int> > g, g1;
vector <int> color, ord, comp;

void dfs(int v)
{
	color[v] = 1;
	for (int i = 0; i < (int)g[v].size(); i++)
	{
		int to = g[v][i];
		if (color[to] == 0)
			dfs(to);
	}
	color[v] = 2;
	ord.push_back(v);
}

int cur_comp = 0;
void dfs0(int v)
{
	comp[v] = cur_comp;
	color[v] = 1;
	for (int i = 0; i < (int)g1[v].size(); i++)
	{
		int to = g1[v][i];
		if (color[to] == 0)
			dfs0(to);
	}
	color[v] = 2;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n, m;
	cin >> n >> m;

	g.resize(2 * n);
	g1.resize(2 * n);
	color.resize(2 * n);
	comp.resize(2 * n);

	int a, b;
	for (int i = 0; i < m; i++)
	{
		cin >> a >> b;
		if (a < 0)
			a = (-a - 1) * 2 + 1;
		else
			a = (a - 1) * 2;

		if (b < 0)
			b = (-b - 1) * 2 + 1;
		else
			b = (b - 1) * 2;

		g[(a ^ 1)].push_back(b);
		g[(b ^ 1)].push_back(a);

		g1[b].push_back((a ^ 1));
		g1[a].push_back((b ^ 1));
	}

	for (int i = 0; i < 2 * n; i++)
	{
		if (color[i] == 0)
			dfs(i);
	}
	for (int i = 0; i < 2 * n; i++)
		color[i] = 0;
	for (int i = 2 * n - 1; i >= 0; i--)
	{
		int now = ord[i];
		if (color[now] == 0)
		{
			dfs0(now);
			cur_comp++;
		}
	}

	bool flag = false;
	for (int i = 0; i < 2 * n; i += 2)
		flag |= (comp[i] == comp[i + 1]);

	if (flag)
		cout << "YES";
	else
		cout << "NO";

	return 0;
}
