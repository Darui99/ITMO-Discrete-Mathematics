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
typedef long double ld;

const ld eps = (ld)1e-6;
typedef vector < vector<ld> > vvl;

inline vvl mul(const vvl &x, const vvl &y) {
	int a = (int)x.size(), b = (int)y.size(), c = (int)y[0].size();
	vvl res(a, vector<ld>(c));
	for (int i = 0; i < a; i++) {
		for (int j = 0; j < c; j++) {
			for (int k = 0; k < b; k++) {
				res[i][j] += x[i][k] * y[k][j];
			}
		}
	}
	return res;
}

inline bool check(const vvl &arr) {
	bool flag = true;
	for (int i = 1; i < (int)arr.size(); i++) {
		for (int j = 0; j < (int)arr[0].size(); j++) {
			flag &= (fabs(arr[i][j] - arr[i - 1][j]) < eps);
		}
	}
	return flag;
}

int main() {
    freopen("markchain.in", "r", stdin);
    freopen("markchain.out", "w", stdout);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	int n;
	cin >> n;

	vvl p(n, vector<ld>(n));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> p[i][j];
		}
	}

	while (!check(p)) {
		p = mul(p, p);
	}

	for (int i = 0; i < n; i++) {
		cout << p[0][i] << endl;
	}

	return 0;
}
