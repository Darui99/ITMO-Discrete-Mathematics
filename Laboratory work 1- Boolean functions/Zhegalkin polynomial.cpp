#include <bits/stdc++.h>
using namespace std;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n;
	cin >> n;

	vector <string> name((1 << n));
	vector <int> arr((1 << n));

	for (int i = 0; i < (1 << n); i++)
		cin >> name[i] >> arr[i];

	vector <int> ans((1 << n));
	ans[0] = arr[0];
	vector <int> p;
	for (int i = 1; i < (1 << n); i++)
	{
		p.clear();
		p.resize((int)arr.size() - 1);
		for (int j = 0; j < (int)p.size(); j++)
			p[j] = (arr[j] ^ arr[j + 1]);
		ans[i] = p[0];
		arr.swap(p);
	}

	for (int i = 0; i < (1 << n); i++)
		cout << name[i] << " " << ans[i] << endl;

	return 0;
}
