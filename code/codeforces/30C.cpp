#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 1010;

struct Target {
	int x, y, t;
	double p;
} a[MAXN];

int n;
double dp[MAXN];

inline bool operator< (const Target &l, const Target &r) {
	return l.t < r.t;
}

inline long long sqr(int x) {
	return (long long)x * x;
}

inline bool ok(int i, int j) {
	return sqr(a[i].x - a[j].x) + sqr(a[i].y - a[j].y) <= sqr(a[i].t - a[j].t); 
}

int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i)
			scanf("%d%d%d%lf", &a[i].x, &a[i].y, &a[i].t, &a[i].p);
		sort(a + 1, a + 1 + n);
		double ans = 0.0;
		memset(dp, 0, sizeof(dp));
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j < i; ++j) {
				if (ok(i, j))
					dp[i] = max(dp[i], dp[j]);
			}
			dp[i] += a[i].p;
			ans = max(ans, dp[i]);
		}
		printf("%.9lf\n", ans);
	}
	return 0;
}
