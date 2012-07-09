#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

inline bool isPrime(long long n) {
	if (n == 2)
		return true;
	for (long long i = 2; i <= n / i; ++i) {
		if (n % i == 0)
			return false;
	}
	return true;
}

long long cnt(long long n, long long k);

long long gao(long long n, long long k) {
	int ret = n;
	for (int i = 2; i < k; ++i)
		ret -= cnt(n, i);
	return ret;
}

inline long long cnt(long long n, long long k) {
	if (n < k || !isPrime(k))
		return 0;
	// Add this will much faster
	if (n / k < k)
		return 1;
	return gao(n / k, k);
}

int main() {
	int a, b, k;
	while (scanf("%d%d%d", &a, &b, &k) != EOF) {
		if (!isPrime(k)) {
			cout << "0" << endl;
		} else {
			cout << cnt(b, k) - cnt(a - 1, k) << endl;
		}
	}
	return 0;
}
