#include <cmath>
#include <cstdio>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

string s;
int k, n, cc[1000010][2];

int main() {
	while (cin >> k >> s) {
		vector<int> i1;
		long long ans = 0;
		int n = s.length();
		int c = 0, pi = -1;
		for (int i = 0; i < n; ++i) {
			c += (s[i] == '0');
			if (i == n - 1 || s[i] == '1') {
				ans += (long long)c * (long long)(c + 1) / 2;
				if (s[i] == '1')
					i1.push_back(i);
				cc[i][0] = c;
				if (pi != -1)
					cc[pi][1] = c;
				pi = i;
				c = 0;
			}
		}
		if (k > 0) {
			ans = 0;
			for (int i = 0; i + k - 1 < (int)i1.size(); ++i)
				ans += (long long)(1 + cc[i1[i]][0]) * (long long)(1 + cc[i1[i + k - 1]][1]);
		}
		cout << ans << endl;
	}
	return 0;
}
