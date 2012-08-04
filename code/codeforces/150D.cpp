#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 160;

char s[MAXN];
int n, a[MAXN], dp[MAXN][MAXN][MAXN];

inline void update(int &v, int a, int b) {
	if (a >= 0 && b >= 0)
		v = max(v, a + b);
}

int gao(int s, int t, int l) {
	if (l < 0 || l > t - s)
		return -1;
	if (t - s <= 0)
		return l ? -1 : 0;
	// t - s >= 1 && l >= 0 && l <= t - s
	if (t - s == 1) {
		return l ? 0 : a[1];
	} else {
		int &ret = dp[s][t][l];
		if (ret != -2)
			return ret;
		ret = -1;
		if (l == 0) {
			for (int i = s + 1; s <)	
		}
	}
}

int main() {
	while (scanf("%d", &n) != EOF) {
		a[0] = 0;
		for (int i = 1; i <= n; ++i)
			scanf("%d", &a[i]);
		scanf("%s", s);
		for (int i = 0; i <= n; ++i)
			for (int j = 0; j <= n; ++j)
				for (int k = 0; k <= n; ++k)
					dp[i][j][k] = -2;
		for (int k = 0; k <= n; ++k) {
			printf("k = %d\n", k);
			gao(0, n, k);
		}
	}
	return 0;
}
