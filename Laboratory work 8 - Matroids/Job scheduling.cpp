#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

bool cmp(const pair<ll, ll> &a, const pair<ll, ll> &b) {
	if (a.second != b.second)
		return a.second > b.second;
	else
		return a.first < b.first;
}

int main() {
    freopen("schedule.in", "r", stdin);
    freopen("schedule.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
	cin >> n;

	vector < pair<ll, ll> > arr(n);
	for (int i = 0; i < n; i++)
		cin >> arr[i].first >> arr[i].second;
	sort(arr.begin(), arr.end(), cmp);

	ll ans = 0ll;
	set <int> s;
	for (int i = 0; i <= n; i++)
		s.insert(i);

	for (int i = 0; i < n; i++) {
		auto p = s.lower_bound(arr[i].first);
		if (p == s.begin())
			ans += arr[i].second;
		else {
			p--;
			s.erase(p);
		}
	}
	
	cout << ans;
	
	return 0;
}
