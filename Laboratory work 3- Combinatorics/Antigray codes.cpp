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

int n;

vector <int> convert(int x) {
	vector <int> res;
	while (x) {
		res.push_back(x % 3);
		x /= 3;
	}
	while ((int)res.size() < n)
		res.push_back(0);
	return res;
}

vector <int> shift(vector <int> x, int k) {
	vector <int> res = x;
	for (int i = 0; i < (int)x.size(); i++)
		res[i] = (res[i] + k) % 3;
	return res;
}

void print(vector <int> x) {
	for (int i = 0; i < (int)x.size(); i++)
		cout << x[i];
	cout << '\n';
}

int main() {
    freopen("antigray.in", "r", stdin);
    freopen("antigray.out", "w", stdout);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> n;

	for (int i = 0; i < (int)pow(3, n - 1); i++) {
		print(shift(convert(i), 0));
		print(shift(convert(i), 1));
		print(shift(convert(i), 2));
	}

	return 0;
}
