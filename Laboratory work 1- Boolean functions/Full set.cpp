#include <bits/stdc++.h>
using namespace std;

bool T0(const vector <int> &arr)
{
	return (arr[0] == 0);
}

bool T1(const vector <int> &arr)
{
	return (arr.back() == 1);
}

bool L(vector <int> arr)
{
	int n = (int)arr.size();

	vector <int> ans(n);
	ans[0] = arr[0];

	vector <int> p;
	for (int i = 1; i < n; i++)
	{
		p.clear();
		p.resize((int)arr.size() - 1);
		for (int j = 0; j < (int)p.size(); j++)
			p[j] = (arr[j] ^ arr[j + 1]);
		ans[i] = p[0];
		arr.swap(p);
	}

	for (int i = 1; i < n; i++)
	{
		if ((i & (i - 1)) != 0 && ans[i])
			return false;
	}
	return true;
}

bool S(int n, const vector <int> &arr)
{
	int primero = (1 << n) - 1;
	for (int i = 0; i < (1 << n); i++)
	{
		if (arr[i] == arr[(i ^ primero)])
			return false;
	}
	return true;
}

bool M(const vector <int> &arr)
{
	int n = (int)arr.size();

	for (int i = 0; i < n; i++)
	{
		bool flag = true;
		for (int mask = 0; mask < n; mask++)
		{
			if ((mask & i) != mask)
				continue;
			flag &= (arr[mask] <= arr[i]);
		}
		if (!flag)
			return false;
	}
	return true;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	vector <bool> post(5, true);

	int q;
	cin >> q;

	while (q--)
	{
		int n; char c;
		cin >> n;

		vector <int> arr((1 << n));
		for (int i = 0; i < (1 << n); i++)
		{
			cin >> c;
			arr[i] = (c - '0');
		}

		if (!T0(arr))
			post[0] = false;
		if (!T1(arr))
			post[1] = false;
		if (!L(arr))
			post[2] = false;
		if (!S(n, arr))
			post[3] = false;
		if (!M(arr))
			post[4] = false;
	}

	if (!post[0] && !post[1] && !post[2] && !post[3] && !post[4])
		cout << "YES";
	else
		cout << "NO";

	return 0;
}
