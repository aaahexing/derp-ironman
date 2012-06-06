#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 1001;
const int MODD = 1000000007;

int n, m, k, dp[MAXN][MAXN];

int main() {
	while (scanf("%d%d%d", &n, &m, &k) != EOF) {
		int mx = max(n, m);
		memset(dp, 0, sizeof(dp));
		for (int i = 3; i <= mx; ++i)
			dp[1][i] = (i - 2) * (i - 1) / 2;
		for (int kk = 2; kk <= k; ++kk) {
			int sum = 0;
			for (int i = 3; i <= mx; ++i) {
				sum = (sum + dp[kk - 1][i - 2]) % MODD;
				dp[kk][i] = (sum + dp[kk][i - 1]) % MODD;
			}
		}
		cout << (dp[k][n] * 1LL * dp[k][m]) % MODD << endl;
	}
	return 0;
}
