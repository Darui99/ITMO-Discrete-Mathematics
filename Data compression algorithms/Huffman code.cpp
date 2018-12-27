#include <bits/stdc++.h>
using namespace std;

int main()
{
  freopen("huffman.in", "r", stdin);
  freopen("huffman.out", "w", stdout);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n;
	cin >> n;

	vector <long long> arr(n);
	for (int i = 0; i < n; i++)
		cin >> arr[i];
	sort(arr.begin(), arr.end());

	long long ans = 0ll, cur;
	queue <long long> q;

	int frontnum = n;
	vector < pair<int, int> > par(n, make_pair(-1, -1));
	int curpar[2];

	for (int i = 0; i < n || (int)q.size() > 1;)
	{
		cur = 0ll;
		for (int t = 0; t < 2; t++)
		{
			if (q.empty())
			{
				cur += arr[i];
				curpar[t] = i;
				i++;
				continue;
			}
			if (i == n)
			{
				cur += q.front();
				curpar[t] = frontnum;
				frontnum++;
				q.pop();
				continue;
			}
			if (arr[i] < q.front())
			{
				cur += arr[i];
				curpar[t] = i;
				i++;
			}
			else
			{
				cur += q.front();
				curpar[t] = frontnum;
				frontnum++;
				q.pop();
			}
		}
		q.push(cur);
		par.push_back(make_pair(curpar[0], curpar[1]));
	}

	vector <long long> len(frontnum + 1);
	for (int i = frontnum; i >= 0; i--)
	{
		if (par[i] == make_pair(-1, -1))
			continue;
		len[par[i].first] = len[i] + 1;
		len[par[i].second] = len[i] + 1;
	}

	for (int i = 0; i < n; i++)
		ans += arr[i] * len[i];
	cout << ans;

	return 0;
}
