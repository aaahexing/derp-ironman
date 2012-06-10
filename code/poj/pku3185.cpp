#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 20;

int gaussMod(int n, int a[][MAXN], int b[]) {
	for (int k = 0; k < n; ++k) {
		int maxi = 0, irow = k;
		for (int i = k + 1; i < n; ++i) {
			if (abs(maxi) < a[i][k])
				maxi = a[irow = i][k];
		}
		if (maxi == 0) {
			continue;
		}
		if (irow != k) {
			for (int j = k; j < n; ++j)
				swap(a[k][j], a[irow][j]);
			swap(b[k], b[irow]);
		}
		for (int i = k + 1; i < n; ++i) {
			if (a[i][k] == 1) {
				b[i] ^= b[k];
				for (int j = k; j < n; ++j)
					a[i][j] ^= a[k][j];
			}
		}
	}
	int free = 0, tb[MAXN], freev[MAXN];
	for (int i = 0; i < n; ++i) {
		bool all_zero = true;
		for (int j = 0; j < n; ++j) {
			if (a[i][j] != 0)
				all_zero = false;
		}
		if (all_zero) {
			if (b[i] > 0)
				return -1;
			freev[free++] = i;
		}
	}
	int ans = 1000000000;
	for (int mask = 0; mask < (1 << free); ++mask) {
		memcpy(tb, b, sizeof(int) * n);
		for (int i = 0; i < free; ++i) {
			if (mask & (1 << i))
				tb[freev[i]] = 1;
		}
		for (int i = n - 1; i >= 0; --i) {
			for (int j = i + 1; j < n; ++j) {
				if (a[i][j] == 1)
					tb[i] ^= tb[j];
			}
		}
		int cnt = 0;
		for (int i = 0; i < n; ++i)
			cnt += tb[i];
		ans = min(ans, cnt);
	}
	return ans;
}

void initMatrix(int n, int a[][MAXN]) {
	for (int i = 0; i < n; ++i)
		memset(a[i], 0, sizeof(int) * n);
	for (int i = 0; i < n; ++i) {
		a[i][i] = 1;
		if (i > 0)
			a[i][i - 1] = 1;
		if (i < n - 1)
			a[i][i + 1] = 1;
	}
}

int main() {
	int ans, n, a[MAXN][MAXN], b[MAXN];
	while (scanf("%d", &b[0]) != EOF) {
		n = 20;
		for (int i = 1; i < n; ++i)
			scanf("%d", &b[i]);
		initMatrix(n, a);
		ans = gaussMod(n, a, b);
		printf("%d\n", ans);
	}
	return 0;
}
