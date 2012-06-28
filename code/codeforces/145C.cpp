#include <map>
#include <cstdio>
#include <vector>
#include <cassert>
#include <cstring>
#include <algorithm>
using namespace std;

const int MODD = 1000000007;

vector<int> l;
map<int, int> mi;
int n, k, ln, un, a[100010], fp[100010], dp[1024][1024];

void genLucky(int n, vector<int> &v) {
	if (n > 0)
		v.push_back(n);
	if ((long long)n * 10 + 4 <= 1000000000)
		genLucky(n * 10 + 4, v);
	if ((long long)n * 10 + 7 <= 1000000000)
		genLucky(n * 10 + 7, v);
}

inline bool isLucky(int x) {
	do {
		int d = x % 10;
		if (d != 4 && d != 7)
			return false;
		x /= 10;
	} while (x > 0);
	return true;
}

// Solve ax + by = gcd(a, b)
void extended_gcd(int a, int b, long long &x, long long &y) {
	if (b == 0) {
		x = 1, y = 0;
	} else {
		long long xx, yy;
		extended_gcd(b, a % b, xx, yy);
		x = yy, y = xx - (a / b) * yy;
	}
}

// Solve ax = 1 (mod p)
inline long long modInv(int a, int p) {
	long long x, y;
	extended_gcd(a, p, x, y);
	return ((x % p) + p) % p;
}

// Calculate a^n mod p
inline long long pow(int a, int n, int p) {
	long long ret = 1, fac = a;
	for (; n; n >>= 1, fac = (fac * fac) % p) {
		if (n & 1)
			ret = (ret * fac) % p;
	}
	return ret;
}

// Solve ax = 1 (mod p) using Fermat's little theorem
inline long long modInv2(int a, int p) {
	return pow(a, p - 2, p);
}

inline int c(int n, int m) {
	if (m < 0 || m > n)
		return 0;
	if (m == 0)
		return 1;
	return (((fp[n] * (long long)modInv(fp[m], MODD)) % MODD) * (long long)modInv(fp[n - m], MODD)) % MODD;
}

int main() {
	genLucky(0, l);
	ln = l.size();
	sort(l.begin(), l.end());
	fp[0] = 1;
	for (int i = 1; i <= 100000; ++i)
		fp[i] = (fp[i - 1] * 1LL * i) % MODD;
	while (scanf("%d%d", &n, &k) != EOF) {
		un = 0;
		mi.clear();
		for (int i = 0; i < n; ++i) {
			scanf("%d", &a[i]);
			if (isLucky(a[i])) {
				++mi[a[i]];
			}
			else
				++un;
		}
		memset(dp, 0, sizeof(dp));
		dp[0][0] = 1;
		for (int i = 1; i <= ln; ++i) {
			for (int j = 0; j <= i; ++j) {
				dp[i][j] = dp[i - 1][j];
				if (j > 0 && mi[l[i - 1]] > 0) {
					dp[i][j] = (dp[i][j] + (long long)dp[i - 1][j - 1] * mi[l[i - 1]]) % MODD;
				}
			}
		}
		int ans = 0;
		for (int j = 0; j <= ln && j <= k; ++j) {
			if (dp[ln][j] > 0) {
				ans = (ans + (long long)dp[ln][j] * c(un, k - j)) % MODD;
			}	
		}
		printf("%d\n", ans);
	}
	return 0;
}
