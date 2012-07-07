#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

char s[210];
int n, k, a, b, l;

int main() {
	while (scanf("%d%d%d%s", &k, &a, &b, s) != EOF) {
		n = strlen(s);
		if (n < k * a || n > k * b) {
			puts("No solution");
		} else {
			int na, nb, nt;
			for (int x = 0; x <= k; ++x) {
				na = x;
				nb = k - 1 - x;
				nt = n - (b * nb + a * na);
				if (na >= 0 && nb >= 0 && nt >= a && nt <= b)
					break;
			}
			for (int i = 0; i < n && k; --k) {
				if (nb > 0) {
					l = b;
					--nb;
				} else if (na > 0) {
					l = a;
					--na;
				} else {
					l = nt;
				}
				printf("%.*s\n", l, s + i);
				i += l;
			}
		}
	}
	return 0;
}

