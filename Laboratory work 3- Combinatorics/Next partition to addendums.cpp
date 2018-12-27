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
 
int convert(const string &s) {
	int res = 0;
	for (int i = (int)s.size() - 1, r = 1; i >= 0; i--, r *= 10)
		res += (int)(s[i] - '0') * r;
	return res;
}
 
int main() {
    freopen("nextpartition.in", "r", stdin);
    freopen("nextpartition.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
 
    string s;
	cin >> s;

	string now = "";
	int n;
	vector <int> arr;

	for (int i = 0; i < (int)s.size(); i++) {
		if (s[i] < '0' || s[i] > '9') {
			if (s[i] == '=') {
				n = convert(now);
			} else {
				arr.push_back(convert(now));
			}
			now = "";
			continue;
		}
		now.push_back(s[i]);
	}
	if (!now.empty())
		arr.push_back(convert(now));

	if (arr.back() == n) {
		cout << "No solution";
		return 0;
	}

	int x = arr[(int)arr.size() - 2] + 1;
	int sum = x;
	for (int i = 0; i < (int)arr.size() - 2; i++)
		sum += arr[i];

	cout << n << "=";
	for (int i = 0; i < (int)arr.size() - 2; i++)
		cout << arr[i] << "+";

	if (n - sum < x) {
		cout << n - (sum - x);
	} else {
		int dif = n - (sum - x);
		for (int i = 0; i < dif / x - 1; i++)
			cout << x << "+";
		cout << dif % x + x;
	}
 
    return 0;
}
