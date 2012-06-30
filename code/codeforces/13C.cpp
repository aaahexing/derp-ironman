#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 5001;

int n, m, pre, cur, min_cost;
long long a[MAXN], b[MAXN], dp[2][MAXN];

int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 0; i < n; ++i)
			cin >> a[i];
		memcpy(b, a, sizeof(a[0]) * n);
		sort(b, b + n);
		m = unique(b, b + n) - b;
		for (int j = 0; j < m; ++j)
			dp[0][j] = 0;
		for (int i = 1; i <= n; ++i) {
			cur = i & 1;
			pre = 1 - cur;
			for (int j = 0; j < m; ++j) {
				dp[cur][j] = dp[pre][j] + abs(a[i - 1] - b[j]);
				if (j > 0)
					dp[cur][j] = min(dp[cur][j], dp[cur][j - 1]);
			}
		}
		long long ans = -1;
		for (int j = 0; j < m; ++j) {
			if (ans == -1 || ans > dp[n & 1][j])
				ans = dp[n & 1][j];
		}
		cout << ans << endl;
	}
	return 0;
}
