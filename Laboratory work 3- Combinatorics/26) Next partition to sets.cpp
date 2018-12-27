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

vector <int> parse(const string &s) {
	string now = "";
	vector <int> res;

	for (int i = 0; i < (int)s.size(); i++) {
		if (s[i] == ' ') {
			res.push_back(convert(now));
			now = "";
		} else {
			now.push_back(s[i]);
		}
	}
	if (!now.empty())
		res.push_back(convert(now));

	return res;
}

void printAns(int n, const vector < vector<int> > &arr) {
	cout << n << " " << (int)arr.size() << '\n';
	for (int i = 0; i < (int)arr.size(); i++) {
		for (int j = 0; j < (int)arr[i].size(); j++)
			cout << arr[i][j] + 1 << " ";
		cout << '\n';
	}
	cout << '\n';
}

void solve() {
	int n, m;
	cin >> n >> m;
	if (n == 0)
		exit(0);

	string inp = "";
	vector < vector<int> > arr, ans;
	for (int i = 0; i < m; i++) {
		while (inp.empty())
			getline(cin, inp);
		arr.push_back(parse(inp));
		inp = "";
	}

	vector <int> num(n);
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < (int)arr[i].size(); j++) {
			arr[i][j]--;
			num[arr[i][j]] = i;
		}
	}

	for (int i = m - 1; i >= 0; i--) {
		int last = arr[i].back();
		for (int j = last + 1; j < n; j++) {
			if (num[j] > num[last]) {
				ans = arr;
				vector <int> del;
				for (int t = m - 1; t > i; t--) {
					while (!ans.back().empty()) {
						del.push_back(ans.back().back());
						ans.back().pop_back();
					}
					ans.pop_back();
				}
				ans[i].push_back(j);
				
				sort(del.begin(), del.end());
				for (int t = 0; t < (int)del.size(); t++) {
					if (del[t] == j)
						continue;
					ans.push_back(vector<int>{del[t]});
				}

				printAns(n, ans);
				return;
			}
		}
		for (int j = (int)arr[i].size() - 1; j > 0; j--) {
			for (int t = arr[i][j] + 1; t < n; t++) {
				if (num[t] >= num[arr[i][j]]) {
					ans = arr;
					vector <int> del;
					for (int k = m - 1; k > i; k--) {
						while (!ans.back().empty()) {
							del.push_back(ans.back().back());
							ans.back().pop_back();
						}
						ans.pop_back();
					}
					for (int k = (int)arr[i].size() - 1; k >= j; k--) {
						del.push_back(ans.back().back());
						ans.back().pop_back();
					}
					ans.back().push_back(t);
					sort(del.begin(), del.end());
					for (int k = 0; k < (int)del.size(); k++) {
						if (del[k] == t)
							continue;
						ans.push_back(vector<int>{del[k]});
					}

					printAns(n, ans);
					return;
				}
			}
		}
	}

	for (int i = 0; i < n; i++)
		ans.push_back(vector<int>{i});
	printAns(n, ans);
	return;
}
 
int main() {
    freopen("nextsetpartition.in", "r", stdin);
    freopen("nextsetpartition.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
 
    while (true)
		solve();
 
    return 0;
}
