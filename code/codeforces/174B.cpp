#include <cstdio>
#include <string>
#include <cstring>
using namespace std;

const int maxn = 400010;

int pn;
char s[maxn];
string part[maxn];

bool gao() {
	if (s[0] == '.')
		return false;
	for (int i = 1; s[i]; ++i) {
		if (s[i] == '.') {
			if (s[i - 1] == '.' || s[i + 1] == '\0')
				return false;
		}
	}
	pn = 0;
	for (char *p = strtok(s, "."); p; p = strtok(NULL, "."))
		part[pn++] = p;
	if (pn < 2)
		return false;
	if (part[0].length() < 1 || part[0].length() > 8)
		return false;
	if (part[pn - 1].length() < 1 || part[pn - 1].length() > 3)
		return false;
	for (int i = 1; i < pn - 1; ++i) {
		if (part[i].length() < 2 || part[i].length() > 11)
			return false;
	}
	return true;
}

int main() {
	while (scanf("%s", s) != EOF) {
		if (!gao()) {
			puts("NO");
		} else {
			puts("YES");
			printf("%s", part[0].c_str());
			for (int i = 1; i < pn - 1; ++i) {
				int l = min(3, (int)part[i].length() - 1);
				printf(".%s\n%s", part[i].substr(0, l).c_str(), part[i].substr(l).c_str());
			}
			printf(".%s\n", part[pn - 1].c_str());
		}
	}
	return 0;
}

