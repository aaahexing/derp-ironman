#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 5010;

int c[256];
char s[MAXN], t[MAXN];

void gao() {
	int ans = -1;
	int n = strlen(s);
	memset(c, 0, sizeof(c));
	for (int i = 0; i < n; ++i)
		++c[s[i]];
	for (int i = 0; i < n; ++i) {
		for (int ch = t[i] + 1; ch <= 'z'; ++ch) {
			if (c[ch] > 0) {
				ans = i;
				break;
			}
		}
		if (!c[t[i]])
			break;
		--c[t[i]];
	}
	if (ans == -1) {
		puts("-1");
	} else {
		memset(c, 0, sizeof(c));
		for (int i = 0; i < n; ++i)
			++c[s[i]];
		for (int i = 0; i < n; ++i) {
			if (i > ans) {
				for (int ch = 'a'; ch <= 'z'; ++ch) {
					while (c[ch]) {
						putchar(ch);
						--c[ch];
					}
				}
			} else {
				char ch = t[i];
				if (i == ans) {
					for (++ch; ch <= 'z'; ++ch) {
						if (c[ch])
							break;
					}
				}
				putchar(ch);
				--c[ch];
			}
		}
		puts("");
	}
}

int main() {
	while (scanf("%s%s", s, t) != EOF) {
		gao();
	}
	return 0;
}
