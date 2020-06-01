#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int S = 7;

inline vector<ll> tk(int k) {
    vector<ll> res(S);
    res[k] = 1ll;
    return res;
}

inline bool is_zero(const vector<ll> &a) {
    bool res = true;
    for (int i = 0; i < (int)a.size(); i++)
        res &= (a[i] != 0ll);
    return res;
}

inline vector<ll> add_r(const vector <ll> &a, const vector<ll> &b) {
    int n = max((int)a.size(), (int)b.size());
    vector <ll> add(n);
    for (int i = 0; i < n; i++) {
        if (i < (int)a.size())
            add[i] += a[i];
        if (i < (int)b.size())
            add[i] += b[i];
    }
    while ((int)add.size() > S)
        add.pop_back();
    return add;
}

inline vector<ll> mul_r(const vector <ll> &a, const vector<ll> &b) {
    int n = (int)a.size(), m = (int)b.size();
    vector <ll> mul(n + m);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            mul[i + j] += a[i] * b[j];
        }
    while ((int)mul.size() > S)
        mul.pop_back();
    return mul;
}

inline vector<ll> pow_r(const vector <ll> &a, ll n) {
    if (n == 0ll)
        return tk(0);
    if (n % 2ll == 0ll) {
        vector<ll> res = pow_r(a, n / 2ll);
        return mul_r(res, res);
    } else {
        vector<ll> res = pow_r(a, n - 1ll);
        return mul_r(res, a);
    }
}

inline vector<ll> seq_r(const vector<ll> &x) {
    vector<ll> res = tk(0);
    vector <ll> pc = tk(0);
    vector<ll> a = x;
    a[0] = 0ll;
    for (int i = 1; i <= S; i++) {
        pc = mul_r(pc, a);
        res = add_r(res, pc);
    }
    return res;
}

inline vector<ll> mset_r(const vector<ll> &a) {
    vector <ll> res = tk(0);
    for (int i = 1; i < (int)a.size(); i++)
        res = mul_r(res, pow_r(seq_r(tk(i)), a[i]));
    return res;
}

string s;

vector <ll> rec(int l, int r) {
    if (l == r) {
        if (s[l] != 'B')
            throw 37;
        return tk(1);
    }
    char c = s[l];
    l += 2;
    r--;
    if (c == 'L') {
        return seq_r(rec(l, r));
    }
    if (c == 'S') {
        return mset_r(rec(l, r));
    }
    int d = 0;
    for (int i = l; i <= r; i++) {
        if (s[i] == '(')
            d++;
        if (s[i] == ')')
            d--;
        if (s[i] == ',' && d == 0) {
            return mul_r(rec(l, i - 1), rec(i + 1, r));
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> s;
    vector <ll> res = rec(0, (int)s.size() - 1);

    for (int i = 0; i < (int)res.size(); i++)
        cout << res[i] << ' ';

    return 0;
}
