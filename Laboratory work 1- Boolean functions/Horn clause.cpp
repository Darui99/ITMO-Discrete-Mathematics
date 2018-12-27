#include <bits/stdc++.h>
using namespace std;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n, k, x;
	cin >> n >> k;

	vector <int> val(n, -1);
	vector < vector< pair<int, int> > > arr(k);
	for (int i = 0; i < k; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cin >> x;
			if (x != -1)
				arr[i].push_back(make_pair(j, x));
		}
	}

	stack < pair<int, int> > newval;
	while (true)
	{
		for (int i = 0; i < k; i++)
		{
			if ((int)arr[i].size() == 1)
			{
				if (val[arr[i][0].first] != -1 && val[arr[i][0].first] == (!arr[i][0].second))
				{
					cout << "YES";
					return 0;
				}
				if (val[arr[i][0].first] == -1)
					newval.push(arr[i][0]);
			}
		}
		if (newval.empty())
		{
			cout << "NO";
			return 0;
		}
		while (!newval.empty())
		{
			val[newval.top().first] = newval.top().second;
			newval.pop();
		}
		for (int i = 0; i < k; i++)
		{
			if ((int)arr[i].size() == 0)
				continue;
			bool primero = false;
			vector < pair<int, int> > unknow;
			for (int j = 0; j < (int)arr[i].size(); j++)
			{
				if (val[arr[i][j].first] == arr[i][j].second)
				{
					arr[i].clear();
					primero = true;
					break;
				}
				if (val[arr[i][j].first] == -1)
					unknow.push_back(arr[i][j]);
			}
			if ((int)unknow.size() == 0 && !primero)
			{
				cout << "YES";
				return 0;
			}
			if (!primero)
				arr[i].swap(unknow);
		}
	}

	return 0;
}
