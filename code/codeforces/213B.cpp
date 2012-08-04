#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 128;
const int MODD = 1000000007;

int n, ans, a[MAXN], c[MAXN][MAXN], dp[11][MAXN];

int gao(int i, int n) {
	if (i == 10)
		return n == 0;
	int &ret = dp[i][n];
	if (ret == -1) {
		ret = 0;
		for (int j = max(0, a[i]); j <= n; ++j)
			ret = (ret + gao(i + 1, n - j) * 1LL * c[n][j]) % MODD;
	}
	return ret;
}

int main() {
	for (int i = 0; i < MAXN; ++i)
		c[i][0] = 1;
	for (int i = 1; i < MAXN; ++i)
		for (int j = 1; j <= i; ++j)
			c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % MODD;
	while (scanf("%d", &n) != EOF) {
		for (int i = 0; i < 10; ++i)
			scanf("%d", &a[i]);
		ans = 0;
		for (int l = 1; l <= n; ++l) {
			for (int i = 1; i < 10; ++i) {
				--a[i];
				memset(dp, -1, sizeof(dp));
				ans = (ans + gao(0, l - 1)) % MODD;
				++a[i];
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}
