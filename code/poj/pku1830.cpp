#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 30;

int gaussMod(int n, int a[][MAXN], int b[]) {
	for (int k = 0; k < n; ++k) {
		int maxi = 0, irow = k;
		for (int i = k; i < n; ++i) {
			if (abs(maxi) < abs(a[i][k]))
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
	int free = 0;
	for (int i = 0; i < n; ++i) {
		bool all_zero = true;
		for (int j = 0; j < n; ++j)
			if (a[i][j] == 1)
				all_zero = false;
		if (all_zero) {
			if (b[i] > 0)
				return -1;
			++free;
		}
	}
	return 1 << free;
}

int main() {
	int cas, n, s, t, a[MAXN][MAXN], b[MAXN];
	for (scanf("%d", &cas); cas--; ) {
		scanf("%d", &n);
		for (int i = 0; i < n; ++i)
			scanf("%d", &b[i]);
		for (int i = 0; i < n; ++i) {
			scanf("%d", &s);
			b[i] ^= s;
		}
		for (int i = 0; i < n; ++i)
			memset(a[i], 0, sizeof(int) * n);
		for (int i = 0; i < n; ++i)
			a[i][i] = 1;
		while (scanf("%d%d", &s, &t) != EOF && (s || t))
			a[t - 1][s - 1] = 1;
		int ans = gaussMod(n, a, b);
		if (ans < 0)
			puts("Oh,it's impossible~!!");
		else
			printf("%d\n", ans);
	}
	return 0;
}
