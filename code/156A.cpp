#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 2010;
const int INFF = 1000000000;

int n, m, ans;
char a[MAXN], b[MAXN];

int main() {
	while (scanf("%s", a) != EOF) {
		scanf("%s", b);
		n = strlen(a);
		m = strlen(b);
		ans = INFF;
		for (int i = -m; i < n; ++i) {
			int cost = 0;
			for (int j = 0; j < m; ++j) {
				if (i + j < 0 || i + j >= n || a[i + j] != b[j])
					++cost;
			}
			ans = min(ans, cost);
		}
		printf("%d\n", ans);
	}
	return 0;
}
