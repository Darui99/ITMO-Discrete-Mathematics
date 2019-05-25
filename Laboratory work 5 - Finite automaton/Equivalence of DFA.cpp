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
    freopen("equivalence.in", "r", stdin);
    freopen("equivalence.out", "w", stdout);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	int n1, m1, k1, n2, m2, k2;
	char c;

	cin >> n1 >> m1 >> k1;
	n1++;

	int x, a, b;
	vector <bool> term1(n1);
	for (int i = 0; i < k1; i++) {
		cin >> x;
		term1[x - 1] = true;
	}

	vector < vector<int> > g1(n1, vector<int>(26, n1 - 1));

	for (int i = 0; i < m1; i++) {
		cin >> a >> b >> c;
		g1[a - 1][(int)(c - 'a')] = b - 1;
	}

	cin >> n2 >> m2 >> k2;
	n2++;

	vector <bool> term2(n2);
	for (int i = 0; i < k2; i++) {
		cin >> x;
		term2[x - 1] = true;
	}

	vector < vector<int> > g2(n2, vector<int>(26, n2 - 1));

	for (int i = 0; i < m2; i++) {
		cin >> a >> b >> c;
		g2[a - 1][(int)(c - 'a')] = b - 1;
	}

	//--------------------------------------------------

	vector < vector<int> > g(n1 * n2);

	for (int i = 0; i < n1; i++) {
		for (int j = 0; j < n2; j++) {
			for (int s = 0; s < 26; s++) {
				int v = i * n2 + j, to = g1[i][s] * n2 + g2[j][s];
				g[v].push_back(to);
			}
		}
	}

	vector <int> dist(n1 * n2, (int)1e+9);
	dist[0] = 0;
	queue <int> q;
	q.push(0);

	while (!q.empty()) {
		int v = q.front();
		q.pop();

		if (term1[v / n2] != term2[v % n2]) {
			cout << "NO";
			return 0;
		}

		for (int i = 0; i < (int)g[v].size(); i++) {
			int to = g[v][i];
			if (dist[to] > dist[v] + 1) {
				dist[to] = dist[v] + 1;
				q.push(to);
			}
		}
	}
	cout << "YES";

	return 0;
}
