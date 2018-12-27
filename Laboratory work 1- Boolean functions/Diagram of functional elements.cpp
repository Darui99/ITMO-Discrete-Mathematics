#include <bits/stdc++.h>
using namespace std;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n, sz, x, cntleaf = 0;
	cin >> n;

	vector < vector<int> > g(n);
	vector < vector<int> > arr(n);
	vector <int> leafs;

	for (int i = 0; i < n; i++)
	{
		cin >> sz;
		for (int t = 0; t < sz; t++)
		{
			cin >> x;
			g[i].push_back(x - 1);
		}
		if (sz > 0)
		{
			arr[i].resize((1 << sz));
			for (int t = 0; t < (1 << sz); t++)
				cin >> arr[i][t];
		}
		else
		{
			cntleaf++;
			leafs.push_back(i);
		}
	}
	reverse(leafs.begin(), leafs.end());

	int depth = 0;
	vector <int> len(n);
	for (int i = 0; i < n; i++)
	{
		reverse(g[i].begin(), g[i].end());

		for (int j = 0; j < (int)g[i].size(); j++)
		{
			int to = g[i][j];
			len[i] = max(len[i], len[to] + 1);
		}
		depth = max(depth, len[i]);
	}
	
	cout << depth << '\n';

	for (int mask = 0; mask < (1 << cntleaf); mask++)
	{
		vector <int> val(n, -1);

		for (int i = 0; i < cntleaf; i++)
			val[leafs[i]] = (((1 << i) & mask) > 0);

		for (int i = 0; i < n; i++)
		{
			if (val[i] == -1)
			{
				int num = 0;
				for (int j = 0; j < (int)g[i].size(); j++)
					num += val[g[i][j]] * (1 << j);
				val[i] = arr[i][num];
			}
		}
		cout << val[n - 1];
	}

	return 0;
}
