#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll mod = 998244353ll;
const int MAXN = 205;

ll arr[MAXN], ans[3][MAXN], fact[MAXN];

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

inline vector<ll> mul_r(const vector <ll> &a, const vector<ll> &b) {
	int n = (int)a.size(), m = (int)b.size();
	vector <ll> mul(n + m);
	vector <bool> zero(n + m, true);
	for (int i = 0; i < n; i++)
	for (int j = 0; j < m; j++) {
		mul[i + j] += a[i] * b[j];
		if (mul[i + j] > 0ll)
			zero[i + j] = false;
		mul[i + j] %= mod;
	}
	while ((int)mul.size() > 1 && zero[(int)mul.size() - 1])
		mul.pop_back();
	return mul;
}

int main() {
    ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	fact[0] = 1ll;
	for (int i = 1; i < MAXN; i++)
		fact[i] = fact[i - 1] * (ll)i % mod;

	ll a = div_mod(1ll, 2ll);

	int n, m;
	cin >> n >> m;
	n++;

	vector <ll> arr(n);
	for (int i = 0; i < n; i++)
		cin >> arr[i];
	vector <ll> cur;

	ans[0][0] = 1ll;
	for (int i = 1; i < m; i++) {
		ll c = div_mod(1ll, fact[i]);
		for (int j = 1; j <= i; j++) {
			ll ac = a - (ll)j + 1ll;
			c = (c * ac) % mod;
		}
		if (i == 1)
			cur = arr;
		else
			cur = mul_r(cur, arr);
		for (int j = 0; j < min((int)cur.size(), m); j++) {
			ans[0][j] = (ans[0][j] + c * cur[j] % mod) % mod;
		}
	}

	for (int i = 0; i < m; i++)
		cout << ans[0][i] << ' ';
	cout << '\n';

	ans[1][0] = 1ll;
	for (int i = 1; i < m; i++) {
		ll c = div_mod(1ll, fact[i]);
		if (i == 1)
			cur = arr;
		else
			cur = mul_r(cur, arr);
		for (int j = 0; j < min((int)cur.size(), m); j++) {
			ans[1][j] = (ans[1][j] + c * cur[j] % mod) % mod;
		}
	}

	for (int i = 0; i < m; i++)
		cout << ans[1][i] << ' ';
	cout << '\n';

	for (int i = 1; i < m; i++) {
		ll c = div_mod(1ll, (ll)i) * pow(-1ll, i - 1);
		c = (c + mod) % mod;
		if (i == 1)
			cur = arr;
		else
			cur = mul_r(cur, arr);
		for (int j = 0; j < min((int)cur.size(), m); j++) {
			ans[2][j] = (ans[2][j] + c * cur[j] % mod) % mod;
		}
	}

	for (int i = 0; i < m; i++)
		cout << ans[2][i] << ' ';
	cout << '\n';

	return 0;
}
