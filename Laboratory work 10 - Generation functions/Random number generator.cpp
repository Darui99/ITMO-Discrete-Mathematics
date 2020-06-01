#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll mod =  104857601ll;

inline vector<ll> mul_r(const vector <ll> &a, const vector<ll> &b) {
    int n = (int)a.size(), m = (int)b.size();
    vector <ll> mul(n + m);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            mul[i + j] += ((a[i] + mod) % mod) * ((b[j] + mod) % mod);
            mul[i + j] %= mod;
        }
    mul.pop_back();
    return mul;
}

inline vector<ll> neg(const vector<ll> &a) {
    vector <ll> res = a;
    for (int i = 1; i < (int)a.size(); i += 2)
        res[i] = -res[i];
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int k;
    ll n;

    cin >> k >> n;
    n--;

    vector <ll> arr(k);
    for (int i = 0; i < k; i++)
        cin >> arr[i];

    vector <ll> q(k + 1);
    for (int i = 1; i <= k; i++) {
        cin >> q[i];
        q[i] = -q[i];
    }
    q[0] = 1ll;

    vector <ll> p(k);
    for (int i = 0; i < k; i++) {
        ll cur = 0ll;
        for (int j = 0; j < i; j++)
            cur = (cur + arr[i - j - 1] * -q[j + 1] % mod + mod) % mod;
        p[i] = (arr[i] + mod - cur) % mod;
    }

    while (n >= k) {
        vector <ll> g = neg(q);
        vector <ll> q1 = mul_r(q, g);
        vector <ll> p1 = mul_r(p, g);
        for (int i = 0; i < (int)q1.size(); i += 2)
            q[i / 2] = q1[i];
        for (int i = n % 2ll; i < (int)p1.size(); i += 2)
            p[i / 2] = p1[i];
        n /= 2ll;
    }

    vector <ll> res(k);
    for (int i = 0; i < k; i++) {
        ll cur = 0ll;
        for (int j = 0; j < i; j++)
            cur = (cur + res[i - j - 1] * -q[j + 1] % mod + mod) % mod;
        res[i] = (cur + p[i]) % mod;
    }

    cout << res[n];

    return 0;
}

