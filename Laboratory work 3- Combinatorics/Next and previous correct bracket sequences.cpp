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
 
int main() {
    freopen("nextbrackets.in", "r", stdin);
    freopen("nextbrackets.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
 
    string s;
	cin >> s;

	int n = (int)s.size();
	vector <int> d(n);
	d[0] = 1;
	for (int i = 1; i < n; i++) {
		if (s[i] == '(')
			d[i] = d[i - 1] + 1;
		else
			d[i] = d[i - 1] - 1;
	}

	for (int i = n - 1; i >= 0; i--) {
		if (s[i] == ')')
			continue;
		if (i == 0) {
			cout << "-";
			return 0;
		}
		if (d[i - 1] - 1 >= 0) {
			for (int j = 0; j < i; j++)
				cout << s[j];
			cout << ')';

			int cur = d[i - 1] - 1, len = n - i - 1;
			for (int j = 0; j < (len - cur) / 2; j++)
				cout << '(';
			cur += (len - cur) / 2;
			while (cur--)
				cout << ')';
			return 0;
		}
	}
 
    return 0;
}
