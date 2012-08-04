#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

long long dp[32][2][10][10];

long long gao(long long n) {
	if (n == 0)
		return 1;
	int dn = 0, di[32];
	for (long long m = n; m; m /= 10)
		di[dn++] = m % 10;
	reverse(di, di + dn);
	memset(dp, 0, sizeof(dp));
	dp[0][0][0][0] = 1;
	for (int i = 0; i < dn; ++i) {
		for (int less = 0; less < 2; ++less) {
			for (int a = 0; a < 10; ++a) {
				for (int b = 0; b < 10; ++b) {
					if (dp[i][less][a][b] > 0) {
						int to = (less == 1 ? 10 : di[i] + 1);
						for (int c = 0; c < to; ++c) {
							if (a != 0) {
								dp[i + 1][less | (c < di[i])][a][c] += dp[i][less][a][b];
							} else {
								dp[i + 1][less | (c < di[i])][b][c] += dp[i][less][a][b];
							}
						}
					}
				}
			}
		}
	}
	long long ret = 0;
	for (int i = 0; i <= n && i < 10; ++i)
		++ret;
	for (int less = 0; less < 2; ++less) {
		for (int a = 0; a < 10; ++a) {
			for (int b = 0; b < 10; ++b) {
				if (a != 0 && a == b) {
					ret += dp[dn][less][a][b];
				}
			}
		}
	}
	return ret;
}

int main() {
	long long l, r;
	while (cin >> l >> r) {
		cout << gao(r) - gao(l - 1) << endl;
	}
	return 0;
}
