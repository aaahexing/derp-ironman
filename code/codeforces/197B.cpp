#include <cstdio>
#include <algorithm>
using namespace std;

int gcd(int a, int b) {
	return b == 0 ? a : gcd(b, a % b);
}

int main() {
	int n, m, an, am;
	while (scanf("%d%d", &n, &m) != EOF) {
		scanf("%d", &an);
		for (int i = 0; i < n; ++i)
			scanf("%*d");
		scanf("%d", &am);
		for (int i = 0; i < m; ++i)
			scanf("%*d");
		if (n < m) {
			puts("0/1");
		} else {
			if (an * am < 0)
				putchar('-');
			if (n > m) {
				puts("Infinity");				
			} else {
				an = abs(an);
				am = abs(am);
				int g = gcd(an, am);
				printf("%d/%d\n", an / g, am / g);
			}
		}
	}
	return 0;
}
