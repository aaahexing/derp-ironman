#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 1024;

int k, c[MAXN];
char s[MAXN], ans[MAXN];

int main() {
	while (scanf("%d", &k) != EOF) {
		memset(c, 0, sizeof(c));
		scanf("%s", s);
		for (int i = 0; s[i]; ++i) {
			++c[s[i]];
		}
		for (char ch = 'a'; ch <= 'z'; ++ch) {
			if (c[ch] % k != 0) {
				puts("-1");
				goto END;
			}
		}
		for (int i = 0; i < k; ++i) {
			for (char ch = 'a'; ch <= 'z'; ++ch) {
				if (c[ch] > 0) {
					for (int ii = 0; ii < c[ch] / k; ++ii)
						putchar(ch);
				}
			}
		}
		putchar('\n');
		END:;
	}
	return 0;
}
