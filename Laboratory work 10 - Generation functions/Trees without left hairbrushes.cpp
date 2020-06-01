#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll mod = 998244353ll;
const int MAXN = 5005;

ll fact[MAXN];

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

inline ll C(int n, int m) {
	if (n < m)
		return 0ll;
	return div_mod(fact[n], fact[m] * fact[n - m] % mod);
}

int main() {
    ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	fact[0] = 1ll;
	for (ll i = 1ll; i < (ll)MAXN; i++)
		fact[i] = fact[i - 1] * i % mod;

	int n, k;
	cin >> n >> k;

	vector <ll> a, b;
	for (int i = n - 2, j = 0; i >= j; i--, j++) {
		a.push_back(C(i, j) * pow(-1, j));
		a.back() = (a.back() + mod) % mod;
	}
	for (int i = n - 1, j = 0; i >= j; i--, j++) {
		b.push_back(C(i, j) * pow(-1, j));
		b.back() = (b.back() + mod) % mod;
	}

	while ((int)a.size() < k)
		a.push_back(0ll);
	while ((int)b.size() < k)
		b.push_back(0ll);

	vector <ll> div(k);
	div[0] = div_mod(a[0], b[0]);
	for (int i = 1; i < k; i++) {
		ll sum = 0ll;
		for (int j = 1; j <= i; j++)
			sum = (sum + b[j] * div[i - j] % mod) % mod;
		div[i] = (a[i] + mod - sum) % mod;
	}

	for (int i = 0; i < k; i++)
		cout << div[i] << '\n';

	return 0;
}
