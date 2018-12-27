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
    freopen("nextperm.in", "r", stdin);
    freopen("nextperm.out", "w", stdout);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n;
	cin >> n;

	vector <int> arr(n);
	for (int i = 0; i < n; i++)
		cin >> arr[i];

	vector <int> next = arr;
	for (int i = n - 2; i >= 0; i--) {
		if (next[i] < next[i + 1]) {
			int minu = n + 1, iminu = -1;
			for (int j = i + 1; j < n; j++) {
				if (next[j] > next[i] && next[j] < minu) {
					minu = next[j];
					iminu = j;
				}
			}
			swap(next[i], next[iminu]);
			reverse(next.begin() + i + 1, next.end());
			break;
		}
	}

	if (next == arr) {
		for (int i = 0; i < n; i++)
			next[i] = 0;
	}

	vector <int> prev = arr;
	for (int i = n - 2; i >= 0; i--) {
		if (prev[i] > prev[i + 1]) {
			int maxu = -1, imaxu = -1;
			for (int j = i + 1; j < n; j++) {
				if (prev[j] < prev[i] && prev[j] > maxu) {
					maxu = prev[j];
					imaxu = j;
				}
			}
			swap(prev[i], prev[imaxu]);
			reverse(prev.begin() + i + 1, prev.end());
			break;
		}
	}

	if (prev == arr) {
		for (int i = 0; i < n; i++)
			prev[i] = 0;
	}

	for (int i = 0; i < n; i++)
		cout << prev[i] << " ";
	cout << endl;
	for (int i = 0; i < n; i++)
		cout << next[i] << " ";
		
	return 0;
}
