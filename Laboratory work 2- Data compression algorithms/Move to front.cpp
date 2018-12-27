#include <bits/stdc++.h>
using namespace std;

int main()
{
	freopen("mtf.in", "r", stdin);
  freopen("mtf.out", "w", stdout);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	string s;
	cin >> s;

	int n = (int)s.size(), m;

	string alph = s;
	sort(alph.begin(), alph.end());
	alph.resize(unique(alph.begin(), alph.end()) - alph.begin());
	m = (int)alph.size();

	for (int i = 0; i < n; i++)
	{
		int pos;
		for (int j = 0; j < m; j++)
		{
			if (s[i] == alph[j])
			{
				pos = j;
				break;
			}
		}
		cout << pos + 1 << " ";
		alph.erase(alph.begin() + pos);
		alph.insert(alph.begin(), s[i]);
	}

	return 0;
}
