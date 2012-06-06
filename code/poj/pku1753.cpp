#include <cmath>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
using namespace std;

const int MAXN = 300;

int gaussMod(int n, int a[][MAXN], int b[]) {
	int free, tb[MAXN];
	for (int k = 0; k < n; ++k) {
		int maxi = 0, irow = k;
		for (int i = k; i < n; ++i) {
			if (abs(a[i][k]) > abs(maxi))
				maxi = a[irow = i][k];
		}
		if (maxi == 0) {
			free = n - k;
			// No unique solution
			break;
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
	int ans = 1000000000;
	for (int i = n - free; i < n; ++i) {
		if (b[i] > 0) {
			// No solution
			return ans;
		}
	}
	for (int mask = 0; mask < (1 << free); ++mask) {
		memcpy(tb, b, sizeof(int) * n);
		for (int i = 0; i < free; ++i) {
			if (mask & (1 << i)) {
				tb[n - 1 - i] = 1;
			}
		}
		// Backsubstitution
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
	for (int i = 0; i < n * n; ++i)
		memset(a[i], 0, sizeof(int) * (n * n));
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			int ii = i * n + j;
			a[ii][ii] = 1;
			if (i > 0)
				a[ii][ii - n] = 1;
			if (i < n - 1)
				a[ii][ii + n] = 1;
			if (j > 0)
				a[ii][ii - 1] = 1;
			if (j < n - 1)
				a[ii][ii + 1] = 1;
		}
	}
}

void initVector(char c, char s[][MAXN], int n, int b[]) {
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			b[i * n + j] = (s[i][j] == c);
}

int main() {
	char s[MAXN][MAXN];
	int cas, n, ans, b[MAXN], a[MAXN][MAXN];
	while (scanf("%s", s[0]) != EOF) {
		n = 4;
		for (int i = 1; i < n; ++i)
			scanf("%s", s[i]);
		ans = 1000000000;
		initMatrix(n, a);
		initVector('b', s, n, b);
		ans = min(ans, gaussMod(n * n, a, b));
		initMatrix(n, a);
		initVector('w', s, n, b);
		ans = min(ans, gaussMod(n * n, a, b));
		if (ans >= 1000000000)
			printf("Impossible\n");
		else
			printf("%d\n", ans);
	}
	return 0;
}

