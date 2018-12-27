#include <bits/stdc++.h>
using namespace std;

typedef unsigned int uint;

vector <string> ans;

void add(int num, bool neg)
{
	if (neg)
		ans.back().push_back('~');
	ans.back().push_back((char)(num + '0'));
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n;
	cin >> n;

	vector <uint> arr(n), st;
	for (int i = 0; i < n; i++)
		cin >> arr[i];

	st = arr;
	sort(arr.begin(), arr.end());
	arr.resize(unique(arr.begin(), arr.end()) - arr.begin());

	n = (int)arr.size();
	vector <int> num(n);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < (int)st.size(); j++)
		{
			if (arr[i] == st[j])
				num[i] = j + 1;
		}
	}

	uint s;
	cin >> s;

	if (s == 0)
	{
		cout << "~1&1";
		return 0;
	}
	if (n == 1)
	{
		if (arr[0] == s)
			cout << "1";
		else
			cout << "Impossible";
		return 0;
	}

	vector <int> was(100, -1);
	was[0] = 0;

	for (int i = 0; i < 32; i++)
	{
		bool res = ((1 << i) & s);
		uint cur = 0;
		vector <bool> bit(n);
		for (int u = 0; u < n; u++)
		{
			bit[u] = ((1 << i) & arr[u]);
			cur |= (1 << u) * bit[u];
		}

		if (was[cur] == -1)
			was[cur] = res;
		else if (was[cur] != res)
		{
			cout << "Impossible";
			return 0;
		}

		if (!res)
			continue;

		ans.push_back("");

		ans.back().push_back('(');
		for (int u = 0; u < n; u++)
		{
			add(num[u], !bit[u]);
			if (u < n - 1)
				ans.back() += "&";
		}
		ans.back().push_back(')');
	}

	for (int i = 0; i < (int)ans.size(); i++)
	{
		cout << ans[i];
		if (i < (int)ans.size() - 1)
			cout << "|";
	}

	return 0;
}
