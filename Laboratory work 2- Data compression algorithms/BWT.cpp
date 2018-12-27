#include <bits/stdc++.h>
using namespace std;

int main()
{
  freopen("bwt.in", "r", stdin);
  freopen("bwt.out", "w", stdout);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n;

	string s;
	cin >> s;

	n = (int)s.size();

	vector <int> arr(n);
	for (int i = 0; i < n; i++)
		arr[i] = (s[i] - 'a');

	vector <int> p(n), c(n), h(n), pn(n);
	for (int i = 0; i < n; i++)
		p[i] = i;

	for (int i = n - 1; i >= 0; i--)
	{
		for (int j = 0; j < n; j++)
			c[j] = 0;
		for (int j = 0; j < n; j++)
			c[arr[(p[j] + i) % n]]++;

		h[0] = 0;
		for (int j = 1; j < n; j++)
			h[j] = h[j - 1] + c[j - 1];

		for (int j = 0; j < n; j++)
		{
			int v = h[arr[(p[j] + i) % n]];
			h[arr[(p[j] + i) % n]]++;
			pn[v] = p[j];
		}
		p = pn;
	}

	for (int i = 0; i < n; i++)
		cout << s[(p[i] - 1 + n) % n];

	return 0;
}
