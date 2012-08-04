#include <cstdio>
#include <cstring>

const int MAXN = 1024;

void solveTriDiagSystem(int n, double *a, double *b, double *c, double *v, double *x) {
	/**
	 * n - number of equations
	 * a - sub-diagonal (means it is the diagonal below the main diagonal) -- indexed from 1..n-1
	 * b - the main diagonal
	 * c - sup-diagonal (means it is the diagonal above the main diagonal) -- indexed from 0..n-2
	 * v - right part
	 * x - the answer
	 */
	for (int i = 1; i < n; ++i) {
		double m = a[i] / b[i - 1];
		b[i] = b[i] - m * c[i - 1];
		v[i] = v[i] - m * v[i - 1];
	}
	x[n - 1] = v[n - 1] / b[n - 1];
	for (int i = n - 2; i >= 0; --i)
		x[i] = (v[i] - c[i] * x[i + 1]) / b[i];
}

int n, m, rr, cc;
double a[MAXN], b[MAXN], c[MAXN], v[MAXN], x[MAXN];

int main() {
	while (scanf("%d%d%d%d", &n, &m, &rr, &cc) != EOF) {
		memset(x, 0, sizeof(x));
		for (int i = n - 1; i >= rr; --i) {
			// Calculate the expected number of the i-th row
			for (int j = 0; j < m; ++j) {
				if (j > 0)
					a[j] = -1.0;
				if (j < m - 1)
					c[j] = -1.0;
				b[j] = 3.0;
				if (j == 0)
					--b[j];
				if (j == m - 1)
					--b[j];
				v[j] = x[j] + b[j] + 1;
			}
			solveTriDiagSystem(m, a, b, c, v, x);
		}
		printf("%.12lf\n", x[cc - 1]);
	}
	return 0;
}
