#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

long long n, h, ans, dp[36][36];

long long gao(int n, int h) {
	if (h == 0)
		return n == 0;
	long long &ret = dp[n][h];
	if (ret != -1)
		return ret;
	ret = 0;
	for (int li = 0; li <= n - 1; ++li) {
		int ri = n - 1 - li;
		for (int hh = 0; hh <= h - 1; ++hh) {
			ret += gao(li, hh) * gao(ri, h - 1);
			ret += gao(li, h - 1) * gao(ri, hh);
		}
		ret -= gao(li, h - 1) * gao(ri, h - 1);
	}
	return ret;
}

int main() {
	while (cin >> n >> h) {
		ans = 0;
		memset(dp, -1, sizeof(dp));
		for (int hh = h; hh <= n; ++hh)
			ans += gao(n, hh);
		cout << ans << endl;
	}
	return 0;
}
