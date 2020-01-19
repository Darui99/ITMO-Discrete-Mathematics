#include <bits/stdc++.h>
using namespace std;

bool ask(int x, int y) {
	cout << "1 " << x + 1 << " " << y + 1 << endl;
	string s;
	cin >> s;
	return (s == "YES");
}

int main() {
    //freopen("guyaury.in", "r", stdin);
    //freopen("guyaury.out", "w", stdout);
    //ios_base::sync_with_stdio(false);
    //cin.tie(nullptr);
    //cout.tie(nullptr);
    
    int n;
	cin >> n;

	vector < vector<bool> > g(n, vector<bool>(n));

	vector <int> arr(n);
	for (int i = 0; i < n; i++)
		arr[i] = i;

	for (int i = 1; i < n; i++) {
		int l = -1, r = i;
		while (r - l > 1) {
			int mid = (l + r) / 2;
			bool ij = ask(arr[i], arr[mid]);
			if (ij)
				r = mid;
			else
				l = mid;
		}
		int v = arr[i];
		arr.erase(arr.begin() + i);
		arr.insert(arr.begin() + r, v);
	}

	cout << "0 ";
	for (int i = 0; i < n; i++) {
		cout << arr[i] + 1 << " ";
	}
	cout << endl;
    
    return 0;
}
