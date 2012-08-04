#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 42;

int n;
char s[MAXN], pre[MAXN][MAXN];
long long p[MAXN], dp[MAXN][MAXN];

void output(int i, int j) {
	if (i > 0 || j > 0) {
		putchar(pre[i][j]);
		if (pre[i][j] == 'H') {
			output(i - 1, j);
		} else {
			output(i, j - 1);
		}
	}
	if (i == n && j == n)
		putchar('\n');
}

int main() {
	while (cin >> n >> s) {
		p[0] = 1;
		for (int i = 1; i < MAXN; ++i)
			p[i] = p[i - 1] * 10LL;
		memset(dp, -1, sizeof(dp));
		dp[0][0] = 0;
		for (int c = 0; c < (n + n); ++c) {
			for (int i = 0; i <= n && i <= c; ++i) {
				int j = c - i;
				int v = s[n + n - 1 - c] - '0';
				if (dp[i + 1][j] < dp[i][j] + v * p[i]) {
					dp[i + 1][j] = dp[i][j] + v * p[i];
					pre[i + 1][j] = 'H';
				}
				if (dp[i][j + 1] < dp[i][j] + v * p[j]) {
					dp[i][j + 1] = dp[i][j] + v * p[j];
					pre[i][j + 1] = 'M';
				}
			}
		}
		output(n, n);
	}
	return 0;
}
