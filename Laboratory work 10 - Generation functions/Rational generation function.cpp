#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int n;
	cin >> n;

	vector <ll> a(n), c(n);
	for (int i = 0; i < n; i++)
		cin >> a[i];
	for (int i = 0; i < n; i++)
		cin >> c[i];

	vector <ll> p(n);
	for (int i = 0; i < n; i++) {
		ll cur = 0ll;
		for (int j = 0; j < i; j++)
			cur += a[i - j - 1] * c[j];
		p[i] = a[i] - cur;
	}

	while ((int)p.size() > 1 && p.back() == 0ll)
		p.pop_back();

	cout << (int)p.size() - 1 << '\n';
	for (int i = 0; i < (int)p.size(); i++)
		cout << p[i] << ' ';
	cout << '\n';

	cout << n << '\n' << "1 ";
	for (int i = 0; i < n; i++)
		cout << -c[i] << ' ';
	for (int i = 0; i < n; i++)

	return 0;
}
