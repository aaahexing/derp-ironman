#include <queue>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 100010;

int n, an, sum, mini, a[MAXN], b[MAXN], ans[MAXN];

int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 0; i < n; ++i)
			scanf("%d", &a[i]);
		for (int i = 0; i < n; ++i)
			scanf("%d", &b[i]);
		memset(ans, 0, sizeof(int) * n);
		sum = 0;
		mini = 1000000010;
		for (int i = 0; i < n; ++i) {
			sum += a[i] - b[i];
			mini = min(mini, sum);
		}
		sum = 0;
		for (int i = 0; i < n; ++i) {
			if (mini - sum >= 0)
				ans[i] = 1;
			sum += a[i] - b[i];
		}
		sum = 0;
		mini = 1000000010;
		for (int i = n - 1; i >= 0; --i) {
			sum += a[i] - b[(i + n - 1) % n];
			mini = min(mini, sum);
		}
		sum = 0;
		for (int i = n - 1; i >= 0; --i) {
			if (mini - sum >= 0)
				ans[i] = 1;
			sum += a[i] - b[(i + n - 1) % n];
		}
		an = 0;
		for (int i = 0; i < n; ++i)
			an += ans[i];
		printf("%d\n", an);
		for (int i = 0; i < n; ++i) {
			if (ans[i])
				printf("%d ", i + 1);
		}
		puts("");
	}
	return 0;
}

