#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll mod = 998244353ll;

inline ll bin_pow(ll a, ll n) {
	ll u = a, res = 1ll;
	while (n) {
		if (n % 2ll == 1ll)
			res = (res * u) % mod;
		u = (u * u) % mod;
		n /= 2ll;
	}
	return res;
}

inline ll div_mod(ll a, ll b) {
	return a * bin_pow(b, mod - 2ll) % mod;
}

int main() {
    ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int n, m, k;
	cin >> n >> m;
	n++; m++;
	k = max(1000, max(n, m));

	vector <ll> a(n), b(m);
	for (int i = 0; i < n; i++)
		cin >> a[i];
	for (int i = 0; i < m; i++)
		cin >> b[i];
	while ((int)a.size() < k)
		a.push_back(0ll);
	while ((int)b.size() < k)
		b.push_back(0ll);

	vector <bool> zero(k, true);
	vector <ll> add(k);
	for (int i = 0; i < k; i++) {
		add[i] = a[i] + b[i];
		if (add[i] > 0ll)
			zero[i] = false;
		add[i] %= mod;
	}

	while ((int)add.size() > 1 && zero[(int)add.size() - 1])
		add.pop_back();

	cout << (int)add.size() - 1 << '\n';
	for (int i = 0; i < (int)add.size(); i++)
		cout << add[i] << ' ';
	cout << '\n';

	vector <ll> mul(n + m);
	zero.clear();
	zero.resize(n + m, true);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++) {
			mul[i + j] += a[i] * b[j];
			if (mul[i + j] > 0ll)
				zero[i + j] = false;
			mul[i + j] %= mod;
		}

	while ((int)mul.size() > 1 && zero[(int)mul.size() - 1])
		mul.pop_back();

	cout << (int)mul.size() - 1 << '\n';
	for (int i = 0; i < (int)mul.size(); i++)
		cout << mul[i] << ' ';
	cout << '\n';

	vector <ll> div(1000);
	div[0] = div_mod(a[0], b[0]);
	for (int i = 1; i < 1000; i++) {
		ll sum = 0ll;
		for (int j = 1; j <= i; j++)
			sum = (sum + b[j] * div[i - j] % mod) % mod;
		div[i] = (a[i] + mod - sum) % mod;
	}

	for (int i = 0; i < 1000; i++)
		cout << div[i] << ' ';

	return 0;
}
