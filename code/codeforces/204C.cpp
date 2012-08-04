#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

int n;
double cc, total;
char a[200010], b[200010];
double sum1[26], sum2[26];

int main() {
	while (scanf("%d%s%s", &n, a, b) != EOF) {
		cc = 0;
		memset(sum1, 0, sizeof(sum1));
		memset(sum2, 0, sizeof(sum2));
		for (int i = 0; i < n; ++i) {
			sum1[a[i] - 'A'] += i + 1;
			cc += (n - i) * sum1[b[i] - 'A'];
			cc += (n - i) * sum2[a[i] - 'A'];
			sum2[b[i] - 'A'] += i + 1;
		}
		printf("%.9lf\n", 6.0 * cc / n / (n + 1) / (n + n + 1));
	}
	return 0;
}
