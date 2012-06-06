#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 300;

int gaussMod(int n, int a[][MAXN], int b[]) {
	int row, col, maxi, index[MAXN];
	for (int i = 0; i < n; ++i)
		index[i] = i;
	for (int k = 0; k < n; ++k) {
		maxi = 0;
		row = col = k;
		for (int i = k; i < n; ++i)
			for (int j = k; j < n; ++j)
				if (abs(maxi) < abs(a[i][j]))
					maxi = a[row = i][col = j];
		if (maxi == 0) {
			// No solution if there're still several bi == 1
			for (int i = k; i < n; ++i) {
				if (b[i] == 1)
					return -1;
			}
			break;
		}
		if (col != k) {
			for (int i = 0; i < n; ++i)
				swap(a[i][col], a[i][k]);
			swap(index[col], index[k]);
		}
		if (row != k) {
			for (int j = 0; j < n; ++j)
				swap(a[row][j], a[k][j]);
			swap(b[row], b[k]);
		}
		for (int i = k + 1; i < n; ++i) {
			if (a[i][k] == 1) {
				b[i] ^= b[k];
				for (int j = n - 1; j >= k; --j)
					a[i][j] ^= a[k][j];		
			}
		}
	}
	for (int i = n - 1; i >= 0; --i) {
		for (int k = n - 1; k >= i + 1; --k) {
			if (a[i][k] == 1) {
				b[i] ^= b[k];
				a[i][k] ^= a[k][k];
			}
		}
	}
	for (int i = 0; i < n; ++i) {
		if (index[i] != i) {
			swap(b[i], b[index[i]]);
			swap(index[i], index[index[i]]);
		}
	}
	int ans = 0;
	for (int i = 0; i < n; ++i)
		ans += b[i];
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

int main() {
	char s[128];
	int cas, n, b[MAXN], a[MAXN][MAXN];
	scanf("%d", &cas);
	for (int ca = 1; ca <= cas; ++ca) {
		scanf("%d", &n);
		for (int i = 0; i < n; ++i) {
			scanf("%s", s);
			for (int j = 0; j < n; ++j)
				b[i * n + j] = (s[j] == 'w');
		}
		initMatrix(n, a);
		int ans = gaussMod(n * n, a, b);
		if (ans >= 0)
			printf("%d\n", ans);
		else
			printf("inf\n");
	}
	return 0;
}

