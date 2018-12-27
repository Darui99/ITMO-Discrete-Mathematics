#include <bits/stdc++.h>
using namespace std;

int main()
{
  freopen("lzw.in", "r", stdin);
  freopen("lzw.out", "w", stdout);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	const int alph = 26;
	vector < vector<int> > trie(1, vector<int>(alph, -1));

	string s;
	cin >> s;

	int n = (int)s.size();

	for (int i = 0; i < alph; i++)
	{
		trie[0][i] = (int)trie.size();
		trie.push_back(vector<int>(alph, -1));
	}

	for (int i = 0; i < n;)
	{
		int v = 0;
		bool flag = true;
		for (int j = i; j < n; j++)
		{
			int c = (s[j] - 'a');
			if (trie[v][c] == -1)
			{
				trie[v][c] = (int)trie.size();
				cout << v - 1 << " ";
				v = (int)trie.size();
				trie.push_back(vector<int>(alph, -1));
				i = j;
				flag = false;
				break;
			}
			v = trie[v][c];
		}
		if (flag)
		{
			cout << v - 1 << " ";
			break;
		}
	}

	return 0;
}
