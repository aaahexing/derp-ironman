#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MODD = 1000000007;

char src[1010], tar[1010];
int n, k, c, dp0[100010], dp1[100010];

int main() {
	while (scanf("%s%s%d", src, tar, &k) != EOF) {
		c = 0;
		n = strlen(src);
		memset(dp0, 0, sizeof(dp0));
		memset(dp1, 0, sizeof(dp1));
		for (int i = 0; i < n; ++i) {
			bool eq = true;
			for (int j = 0; j < n; ++j) {
				if (src[(i + j) % n] != tar[j]) {
					eq = false;
					break;
				}
			}
			c += eq;
		}
		if (!strcmp(src, tar)) {
			dp0[0] = 1;
			dp1[0] = 0;
		} else {
			dp0[0] = 0;
			dp1[0] = 1;
		}
		for (int i = 1; i <= k; ++i) {
			dp0[i] = (dp0[i - 1] * 1LL * (c - 1) + dp1[i - 1] * 1LL * c) % MODD;
			dp1[i] = (dp1[i - 1] * 1LL * (n - c - 1) + dp0[i - 1] * 1LL * (n - c)) % MODD;
		}
		printf("%d\n", dp0[k]);
	}
	return 0;
}
