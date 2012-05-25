#include <cmath>
#include <cstdio>
using namespace std;

int main() {
	int n, m, h, s, sum0, sum1;
	while (scanf("%d%d%d", &n, &m, &h) != EOF) {
		sum0 = sum1 = 0;
		for (int i = 1; i <= m; ++i) {
			scanf("%d", &s);
			sum0 += s;
			if (i != h)
				sum1 += s;
		}
		double ans = 1.0;
		if (sum0 < n) {
			ans = -1.0;
		} else if (sum1 >= n - 1) {
			for (int i = 1; i <= n - 1; ++i) {
				ans *= (sum1 - i + 1);
				ans /= (sum0 - i);
			}
			ans = 1.0 - ans;
		}
		printf("%.9lf\n", ans);
	}
	return 0;
}
