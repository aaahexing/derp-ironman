#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 110;

int n, k, ep;
double x[MAXN], y[MAXN], dp[MAXN][MAXN];

inline double sqr(double x) {
	return x * x;
}

inline double dis(double x0, double y0, double x1, double y1) {
	return sqr(x0 - x1) + sqr(y0 - y1);
}

int main() {
	while (scanf("%d", &n) != EOF) {
		scanf("%d%d", &k, &ep);
		for (int i = 0; i <= n; ++i)
			scanf("%lf%lf", &x[i], &y[i]);
		double l = 0.0, r = 1e10;
		for (int iter = 0; iter < 100; ++iter) {
			double m = (l + r) * 0.5;
			dp[0][0] = 1.0;
			for (int i = 1; i <= n; ++i) {
				double d = dis(x[i], y[i], x[0], y[0]);
				double p = (d > m * m ? exp(1.0 - d / m / m) : 1.0);
				for (int j = 0; j <= i; ++j) {
					dp[i][j] = dp[i - 1][j] * (1 - p);
					if (j > 0)
						dp[i][j] += dp[i - 1][j - 1] * p;
				}
			}
			double fail = 0.0;
			for (int j = 0; j < k; ++j)
				fail += dp[n][j];
			if (fail * 1000 <= ep)
				r = m;
			else
				l = m;
		}
		printf("%.9lf\n", 0.5 * (l + r));
	}
	return 0;
}
