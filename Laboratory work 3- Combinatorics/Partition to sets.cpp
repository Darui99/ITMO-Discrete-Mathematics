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

int n, k;
vector <bool> used;
vector < vector<int> > ans, var;
vector <int> arr;

int setset(int pos, int can) {
	int res = 0;
	if ((int)arr.size() == can || pos == n) {
		if (!arr.empty()) {
			var.push_back(arr);
			res++;
		}
		return res;
	}

	res += setset(pos + 1, can);
	if (!used[pos]) {
		arr.push_back(pos);
		res += setset(pos + 1, can);
		arr.pop_back();
	}
	return res;
}

void rec(int pos) {
	if (pos == k) {
		for (int i = 0; i < k; i++) {
			for (int j = 0; j < (int)ans[i].size(); j++) {
				cout << ans[i][j] + 1 << ' ';
			}
			cout << '\n';
		}
		cout << '\n';
		return;
	}

	if (pos == k - 1) {
		vector <int> cur;
		for (int i = 0; i < n; i++) {
			if (!used[i])
				cur.push_back(i);
		}
		if (!cur.empty() && (ans.empty() || (!ans.empty() && cur > ans.back()))) {
			ans.push_back(cur);
			rec(pos + 1);
			ans.pop_back();
		}
		return;
	}

	int free = 0;
	for (int i = 0; i < n; i++)
		free += (!used[i]);

	int act = setset(0, free - (k - pos - 1));
	for (int step = 0; step < act; step++)
	{
		if (!ans.empty() && var.back() < ans.back()) {
			var.pop_back();
			continue;
		}
		ans.push_back(var.back());
		for (int j = 0; j < (int)var.back().size(); j++)
			used[var.back()[j]] = true;
		rec(pos + 1);
		for (int j = 0; j < (int)var.back().size(); j++)
			used[var.back()[j]] = false;
		ans.pop_back();
		var.pop_back();
	}

}

int main() {
    freopen("part2sets.in", "r", stdin);
    freopen("part2sets.out", "w", stdout);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> n >> k;
	used.resize(n);
	rec(0);

	return 0;
}
