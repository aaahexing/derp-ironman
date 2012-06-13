#include <cstdio>
#include <string>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 100010;

char s[MAXN];
vector<int> p[26];

int main() {
	while (scanf("%s", s) != EOF) {
		for (int i = 0; i < 26; ++i)
			p[i].clear();
		for (int i = 0; s[i]; ++i)
			p[s[i] - 'a'].push_back(i);
		int mini = 0;
		string ans = "";
		for (int j = 25; j >= 0; --j) {
			int sz = p[j].size();
			for (int i = 0; i < sz; ++i) {
				if (p[j][i] >= mini) {
					ans += 'a' + j;
					mini = max(mini, p[j][i]);
				}
			}
		}
		printf("%s\n", ans.c_str());
	}
	return 0;
}
