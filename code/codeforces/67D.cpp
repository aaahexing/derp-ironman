#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 1000010;

int n, c, a[MAXN], b[MAXN], dp[MAXN];

int search(int n, int v) {
	int l = 0, r = n - 1;
	while (l < r) {
		int m = (l + r + 1) / 2;
		if (dp[m] >= v)
			l = m;
		else
			r = m - 1;
	}
	return l;
}

int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i) {
			scanf("%d", &c);
			b[c] = i;
		}
		for (int i = 1; i <= n; ++i) {
			scanf("%d", &c);
			a[b[c]] = i;
		}
		int dn = 1;
		memset(dp, 0, sizeof(dp));
		dp[0] = n + 1;
		for (int i = 1; i <= n; ++i) {
			int l = search(dn, a[i]);
			dp[l + 1] = max(dp[l + 1], a[i]);
			dn = max(dn, l + 2);
		}
		for (int i = n; i >= 0; --i) {
			if (dp[i] > 0) {
				printf("%d\n", i);
				break;
			}
		}
	}
	return 0;
}
