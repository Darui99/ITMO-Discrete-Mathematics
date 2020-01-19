#include <bits/stdc++.h>
using namespace std;

int main() {
    freopen("guyaury.in", "r", stdin);
    freopen("guyaury.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n;
	cin >> n;

	vector < vector<bool> > g(n, vector<bool>(n));

	string s;
	for (int i = 1; i < n; i++) {
		cin >> s;
		for (int j = 0; j < (int)s.size(); j++) {
			if (s[j] == '1') {
				g[i][j] = true;
			}
			else {
				g[j][i] = true;
			}
		}
	}

	vector <int> arr(n);
	for (int i = 0; i < n; i++)
		arr[i] = i;

	for (int i = 1; i < n; i++) {
		int pos = i;
		for (int j = 0; j < i; j++) {
			if (!g[arr[j]][arr[i]]) {
				pos = j;
				break;
			}
		}
		int v = arr[i];
		arr.erase(arr.begin() + i);
		arr.insert(arr.begin() + pos, v);
	}

	int end = -1;
	for (int i = n - 1; i >= 0; i--) {
		if (g[arr[i]][arr[0]]) {
			end = i;
			break;
		}
	}

	while (end < n - 1) {
		for (int i = end + 1; i < n; i++) {
			bool flag = false;
			for (int j = 0; j <= end; j++) {
				if (g[arr[i]][arr[j]]) {
					for (int t = end + 1; t <= i; t++) {
						int v = arr[t];
						arr.erase(arr.begin() + t);
						arr.insert(arr.begin() + j + t - end - 1, v);
					}
					end = i;
					flag = true;
					break;
				}
			}
			if (flag)
				break;
		}
	}

	for (int i = 0; i < n; i++)
		cout << arr[i] + 1 << " ";
    
    return 0;
}
