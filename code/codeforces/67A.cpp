#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 1024;

char s[MAXN];
int n, v, a[MAXN];

int main() {
	while (scanf("%d%s", &n, s) != EOF) {
		for (int i = 0; i < n; ++i)
			a[i] = 1;
		for (int j = 0; j < n; ++j) {
			for (int i = 0; i < n - 1; ++i) {
				if (s[i] == 'L') {
					if (a[i] <= a[i + 1])
						a[i] = a[i + 1] + 1;
				} else if (s[i] == 'R') {
					if (a[i] >= a[i + 1])
						a[i + 1] = a[i] + 1;
				} else {
					a[i + 1] = a[i] = max(a[i], a[i + 1]);
				}
			}	
		}
		for (int i = 0; i < n; ++i) {
			if (i) putchar(' ');
			printf("%d", a[i]);
		}
		puts("");
	}
	return 0;
}
