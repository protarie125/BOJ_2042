#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <tuple>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

using ll = long long;
using vb = vector<bool>;
using vvb = vector<vb>;
using vi = vector<int>;
using vvi = vector<vi>;
using vl = vector<ll>;
using vvl = vector<vl>;
using pii = pair<int, int>;
using vii = vector<pii>;
using pll = pair<ll, ll>;
using vll = vector<pll>;

int n, m, k;
int sz;
vl dat;

void putData() {
	for (const auto& x : dat) {
		cout << x << ' ';
	}
	cout << '\n';
}

ll query_part(int x, int y, int key, int l, int r) {
	//cout << x << ',' << y << ',' << key << ',' << l << ',' << r << '\n';

	if (y <= x) {
		//cout << " -> 0\n";
		return 0LL;
	}

	if (y <= l || r <= x) {
		//cout << " -> 0\n";
		return 0LL;
	}

	if (l == x && y == r) {
		//cout << " -> " << dat[key] << "\n";
		return dat[key];
	}

	auto ret = ll{ 0 };
	const auto m = (l + r) / 2;
	ret += query_part(x, min(y, m), key * 2 + 1, l, m);
	ret += query_part(max(m, x), y, key * 2 + 2, m, r);
	//cout << " -> " << ret << "\n";
	return ret;
}

ll query(int x, int y) {
	return query_part(x, y, 0, 0, sz / 2);
}

void update(int i, ll x) {
	auto idx = i + sz / 2 - 1;
	dat[idx] = x;
	idx = (idx - 1) / 2;

	if (0 == idx) {
		return;
	}

	while (true) {
		dat[idx] = dat[idx * 2 + 1] + dat[idx * 2 + 2];

		if (0 == idx) {
			return;
		}

		idx = (idx - 1) / 2;
	}
}

int main() {
	ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	cin >> n >> m >> k;

	sz = 1;
	while (sz < n) {
		sz *= 2;
	}
	sz *= 2;

	dat = vl(sz - 1, 0);

	for (auto i = 0; i < n; ++i) {
		ll x;
		cin >> x;
		update(i, x);
		//putData();
	}

	for (auto i = 0; i < m + k; ++i) {
		ll a, b, c;
		cin >> a >> b >> c;
		if (1 == a) {
			update(b - 1, c);
			//putData();
		}
		else if (2 == a) {
			cout << query(b - 1, c) << '\n';
		}
	}

	return 0;
}