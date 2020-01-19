#include <bits/stdc++.h>
using namespace std;

int main() {
    freopen("chvatal.in", "r", stdin);
    freopen("chvatal.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n;
	cin >> n;

	if (n == 3) {
		cout << "1 2 3";
		return 0;
	}

	vector < vector<bool> > g(n, vector<bool>(n));

	string s;
	for (int i = 1; i < n; i++) {
		cin >> s;
		for (int j = 0; j < (int)s.size(); j++) {
			if (s[j] == '1') {
				g[i][j] = g[j][i] = true;
			}
		}
	}

	deque <int> arr(n);
	for (int i = 0; i < n; i++)
		arr[i] = i;

	int good = 0;
	while (good <= n) {
		if (!g[arr[0]][arr[1]]) {
			good = 0;
			for (int j = 2; j < n - 1; j++) {
				if (g[arr[0]][arr[j]] && g[arr[1]][arr[j + 1]]) {
					reverse(arr.begin() + 1, arr.begin() + j + 1);
					break;
				}
			}
			if (!g[arr[0]][arr[1]]) {
				for (int j = 2; j < n; j++) {
					if (g[arr[0]][arr[j]]) {
						reverse(arr.begin() + 1, arr.begin() + j + 1);
						break;
					}
				}
			}
		}
		else {
			good++;
		}
		arr.push_back(arr.front());
		arr.pop_front();
	}

	for (int i = 0; i < n; i++)
		cout << arr[i] + 1 << " ";
    
    return 0;
}