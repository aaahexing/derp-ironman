#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

long long n, d;

long long gao() {
	for (int c = 18; c >= 0; --c) {
		long long base = 1;
		for (int i = 0; i < c; ++i) {
			base *= 10LL;
		}
		if (n % base >= base - 1) {
			if (n / base > 0 && 0 <= d) {
				return n;
			}
		} else {
			if (n / base >= 1 && n - ((n / base - 1) * base + base - 1) <= d) {
				return (n / base - 1) * base + base - 1;
			}
		}
	}
	return n;
}

int main() {
	while (cin >> n >> d) {
		cout << gao() << endl;
	}
	return 0;
}
