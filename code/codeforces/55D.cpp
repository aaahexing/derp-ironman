#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 21;	// maximum digits
const int MODD = 2520;	// lcm(1, 2, 3, 4, 5, 6, 7, 8, 9)
// counts of divs
const int c2s[] = { 0, 0, 1, 0, 2, 0, 1, 0, 3, 0 };
const int c3s[] = { 0, 0, 0, 1, 0, 0, 1, 0, 0, 2 };
const int c5s[] = { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0 };
const int c7s[] = { 0, 0, 0, 0, 0, 0, 0, 1, 0, 0 };
// Powers
const int p2s[] = { 1, 2, 4, 8 };
const int p3s[] = { 1, 3, 9 };
const int p5s[] = { 1, 5 };
const int p7s[] = { 1, 7 };

long long cas, l, r, dp[MAXN][2][MODD][4][3][2][2];

long long gao(long long n) {
	if (n == 0)
		return 1;
	int dn = 0, di[MAXN];
	while (n) {
		di[dn++] = n % 10;
		n /= 10;
	}
	reverse(di, di + dn);
	long long ret = 0;
	memset(dp, 0, sizeof(dp));
	dp[0][0][0][0][0][0][0] = 1;
	for (int i = 0; i < dn; ++i) {
		for (int less = 0; less < 2; ++less) {
			for (int mod = 0; mod < MODD; ++mod) {
				for (int c2 = 0; c2 < 4; ++c2) {
					for (int c3 = 0; c3 < 3; ++c3) {
						for (int c5 = 0; c5 < 2; ++c5) {
							for (int c7 = 0; c7 < 2; ++c7) {
								const long long &ref = dp[i][less][mod][c2][c3][c5][c7];
								if (ref > 0) {
									// Try to add the succeeded states
									int to = (less == 1 ? 10 : di[i] + 1);
									for (int dig = 0; dig < to; ++dig) {
										if (i == dn - 1) {
											// some optimizations considering that the modular property
											if (c2 && dig % 2 != 0)
												continue;
											if (c5 && dig % 5 != 0)
												continue;
										}
										int cc2 = max(c2, c2s[dig]);
										int cc3 = max(c3, c3s[dig]);
										int cc5 = max(c5, c5s[dig]);
										int cc7 = max(c7, c7s[dig]);
										dp[i + 1][less | (dig < di[i])][(mod * 10 + dig) % MODD][cc2][cc3][cc5][cc7] += ref;
									}									
								}
							}
						}
					}
				}
			}
		}
	}
	for (int less = 0; less < 2; ++less) {
		for (int mod = 0; mod < MODD; ++mod) {
			for (int c2 = 0; c2 < 4; ++c2) {
				if (mod % p2s[c2])
					continue;
				for (int c3 = 0; c3 < 3; ++c3) {
					if (mod % p3s[c3])
						continue;
					for (int c5 = 0; c5 < 2; ++c5) {
						if (mod % p5s[c5])
							continue;
						for (int c7 = 0; c7 < 2; ++c7) {
							if (mod % p7s[c7])
								continue;
							// Add to the answer
							ret += dp[dn][less][mod][c2][c3][c5][c7];
						}
					}
				}
			}
		}
	}
	return ret;
}

int main() {
	cin >> cas;
	while (cas--) {
		cin >> l >> r;
		cout << gao(r) - gao(l - 1) << endl;
	}
	return 0;
}
