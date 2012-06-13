#include <cstdio>

int main() {
	int a, b, r;
	while (scanf("%d%d%d", &a, &b, &r) != EOF)
		printf("%s\n", (a >= r + r && b >= r + r) ? "First" : "Second");
	return 0;
}
