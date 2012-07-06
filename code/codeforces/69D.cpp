#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int a, b, n, d, x[21], y[21], dp[810][810][2][2];

int gao(int a, int b, int v1, int v2) {
	int &ret = dp[a + 400][b + 400][v1][v2];
	if (ret != -1)
		return ret;
	if (a * a + b * b > d * d) {
		return ret = 1;
	}
	if (v1 && !gao(b, a, v2, 0)) {
		return ret = 1;
	}
	for (int i = 0; i < n; ++i) {
		if (!gao(a + x[i], b + y[i], v2, v1))
			return ret = 1;
		if (v1 && !gao(b + y[i], a + x[i], v2, 0))
			return ret = 1;
	}	
	return ret = 0;
}

int main() {
	while (scanf("%d%d%d%d", &a, &b, &n, &d) != EOF) {
		for (int i = 0; i < n; ++i)
			scanf("%d%d", &x[i], &y[i]);
		memset(dp, -1, sizeof(dp));
		printf("%s\n", gao(a, b, 1, 1) ? "Anton" : "Dasha");
	}
	return 0;
}
