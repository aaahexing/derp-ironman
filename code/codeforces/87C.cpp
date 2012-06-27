#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 100010;
const int INFF = 1000000000;

int g[MAXN], s[MAXN];

int gao(int n) {
	int tag[100], ans = INFF;
	for (int i = 3; i <= n; ++i) {
		int nn = i + i;
		memset(tag, 0, sizeof(tag));
		for (int k = 2; k * k <= nn; ++k) {
			if (nn % k == 0) {
				int kk[] = { k, nn / k };
				for (int t = 0; t < 2; ++t) {
					int a0 = nn / kk[t] - (kk[t] - 1);
					if (a0 > 0 && a0 % 2 == 0) {
						a0 /= 2;
						int ak = a0 + (kk[t] - 1);
						int sg = s[ak] ^ s[a0 - 1];
						if (sg == 0 && i == n) {
							ans = min(ans, kk[t]);
						}
						tag[sg] = 1;
					}
				}
			}
		}	
		for (g[i] = 0; tag[g[i]]; ++g[i]);
		s[i] = s[i - 1] ^ g[i];
	}
	return ans < INFF ? ans : -1;
}

int main() {
	int n;
	while (scanf("%d", &n) != EOF)
		printf("%d\n", gao(n));
	return 0;
}
