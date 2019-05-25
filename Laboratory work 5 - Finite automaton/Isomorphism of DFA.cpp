/*─────────▄──────────────▄
────────▌▒█───────────▄▀▒▌
────────▌▒▒▀▄───────▄▀▒▒▒▐
───────▐▄▀▒▒▀▀▀▀▄▄▄▀▒▒▒▒▒▐
─────▄▄▀▒▒▒▒▒▒▒▒▒▒▒█▒▒▄█▒▐
───▄▀▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▀██▀▒▌
──▐▒▒▒▄▄▄▒▒▒▒▒▒▒▒▒▒▒▒▒▀▄▒▒▌
──▌▒▒▐▄█▀▒▒▒▒▄▀█▄▒▒▒▒▒▒▒█▒▐
─▐▒▒▒▒▒▒▒▒▒▒▒▌██▀▒▒▒▒▒▒▒▒▀▄▌
─▌▒▀▄██▄▒▒▒▒▒▒▒▒▒▒▒░░░░▒▒▒▒▌
─▌▀▐▄█▄█▌▄▒▀▒▒▒▒▒▒░░░░░░▒▒▒▐
▐▒▀▐▀▐▀▒▒▄▄▒▄▒▒▒▒▒░░░░░░▒▒▒▒▌
▐▒▒▒▀▀▄▄▒▒▒▄▒▒▒▒▒▒░░░░░░▒▒▒▐
─▌▒▒▒▒▒▒▀▀▀▒▒▒▒▒▒▒▒░░░░▒▒▒▒▌
─▐▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▐
──▀▄▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▄▒▒▒▒▌
────▀▄▒▒▒▒▒▒▒▒▒▒▄▄▄▀▒▒▒▒▄▀
───▐▀▒▀▄▄▄▄▄▄▀▀▀▒▒▒▒▒▄▄▀*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    freopen("isomorphism.in", "r", stdin);
    freopen("isomorphism.out", "w", stdout);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	// 0 - ordinary, 1 - start, 2 - term, 3 - start & term
	multiset < pair<int, pair<int, vector<int> > > > have[2];

	for (int t = 0; t < 2; t++) {
		int n, m, k, x, a, b;
		cin >> n >> m >> k;

		vector < pair<int, pair <int, vector <int> > > > arr(n);
		for (int i = 0; i < n; i++)
			arr[i].second.second.resize(26);

		arr[0].first++;
		for (int i = 0; i < k; i++) {
			cin >> x;
			arr[x - 1].first += 2;
		}

		char c;
		for (int i = 0; i < m; i++) {
			cin >> a >> b >> c;
			a--; b--; x = (int)(c - 'a');
			arr[a].second.first += (1 << x);
			arr[b].second.second[x]++;
		}

		for (int i = 0; i < n; i++)
			have[t].insert(arr[i]);
	}

	if (have[0] == have[1])
		cout << "YES";
	else
		cout << "NO";

	return 0;
}
