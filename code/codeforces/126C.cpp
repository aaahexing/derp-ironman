#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 2001;

char a[MAXN][MAXN];
int n, v[MAXN], r[MAXN], c[MAXN];

int gao() {
	int ret = 0;
	memset(r, 0, sizeof(int) * n);
	memset(c, 0, sizeof(int) * n);
	for (int i = 0; i < n - 1; ++i) {
		for (int j = n - 1; j > i; --j) {
			if (a[i][j] ^ r[i] ^ c[j]) {
				++ret;
				r[i] ^= 1;
				c[j] ^= 1;
			}
		}
	}
	for (int i = 0; i < n; ++i)
		v[i] ^= (r[i] ^ c[i]);
	memset(r, 0, sizeof(int) * n);
	memset(c, 0, sizeof(int) * n);
	for (int i = n - 1; i > 0; --i) {
		for (int j = 0; j < i; ++j) {
			if (a[i][j] ^ r[i] ^ c[j]) {
				++ret;
				r[i] ^= 1;
				c[j] ^= 1;
			}
		}
	}
	for (int i = 0; i < n; ++i)
		v[i] ^= (r[i] ^ c[i]);
	for (int i = 0; i < n; ++i)
		ret += v[i];
	return ret;
}

int main() {
	while (scanf("%d", &n) != EOF) {
		memset(v, 0, sizeof(int) * n);
		for (int i = 0; i < n; ++i) {
			scanf("%s", a[i]);
			for (int j = 0; j < n; ++j)
				a[i][j] -= '0';
			v[i] ^= (int)a[i][i];
		}
		printf("%d\n", gao());
	}
	return 0;
}

