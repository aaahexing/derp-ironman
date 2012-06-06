#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 110;

bool gaussMod(int n, int a[][MAXN], int b[]) {
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
		if (maxi == 0)
			return false;
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
		for (int k = n - 1; k > i; --k) {
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
	return true;
}

void initMatrix(int a[][MAXN]) {
	memset(a, 0, sizeof(a));
	for (int i = 0; i < 5; ++i) {
		for (int j = 0; j < 6; ++j) {
			int ii = i * 6 + j;
			a[ii][ii] = 1;
			if (i > 0)
				a[ii][ii - 6] = 1;
			if (i < 4)
				a[ii][ii + 6] = 1;
			if (j > 0)
				a[ii][ii - 1] = 1;
			if (j < 5)
				a[ii][ii + 1] = 1;
		}
	}
}

int main() {
	int cas, b[MAXN], a[MAXN][MAXN];
	scanf("%d", &cas);
	for (int ca = 1; ca <= cas; ++ca) {
		for (int i = 0; i < 5; ++i)
			for (int j = 0; j < 6; ++j)
				scanf("%d", &b[i * 6 + j]);
		initMatrix(a);
		if (gaussMod(30, a, b)) {
			printf("PUZZLE #%d\n", ca);
			for (int i = 0; i < 5; ++i) {
				for (int j = 0; j < 6; ++j) {
					if (j) putchar(' ');
					printf("%d", b[i * 6 + j]);
				}
				putchar('\n');
			}
		}
	}
	return 0;
}

