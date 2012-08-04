#include <map>
#include <cstdio>
#include <string>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 32;

struct State {
	int w, a, b;
	State(int _w = -1, int _a = 0, int _b = 0)
		: w(_w), a(_a), b(_b) {}
};

int n;
string s[MAXN];

int score(const string &st) {
	int ret = 0, sum_v = 0, max_v = 0;
	for (int i = 0; i < st.length(); ++i) {
		int c = st[i] - 'a' + 1;
		sum_v += c;
		max_v = max(max_v, c);
	}
	ret += max_v * sum_v;
	for (int i = 0; i < n; ++i)
		if (s[i].find(st) != -1)
			++ret;
	return ret;
}

inline bool sort_state(const string &l, const string &r) {
	return l.length() > r.length();
}

inline bool operator< (const State &l, const State &r) {
	if (l.w != r.w) {
		return l.w > r.w;
	} else if (l.a != r.a) {
		return l.a > r.a;
	} else {
		return l.b < r.b;
	}
}

void gao() {
	map<string, int> dict;
	dict[""] = 0;
	for (int i = 0; i < n; ++i) {
		const string &st = s[i];
		for (int j = 0; j < st.length(); ++j) {
			for (int k = 1; j + k <= st.length(); ++k)
				dict[st.substr(j, k)] = 0;
		}
	}
	int sn = 0;
	vector<string> states;
	for (map<string, int> :: iterator it = dict.begin(); it != dict.end(); ++it) {
		states.push_back(it->first);
		it->second = sn++;
	}
	sort(states.begin(), states.end(), sort_state);
	vector<State> dp(sn);
	for (int i = 0; i < sn; ++i)
		dp[i] = State(-1, 0, 0);
	for (int i = 0; i < sn; ++i) {
		int ii;
		const string &ss = states[i];
		State cur = dp[dict[ss]];
		if (ss.length() > 0) {
			ii = dict[ss.substr(1)];
			dp[ii] = min(dp[ii], State(-cur.w, cur.b + score(ss), cur.a));
			ii = dict[ss.substr(0, ss.length() - 1)];
			dp[ii] = min(dp[ii], State(-cur.w, cur.b + score(ss), cur.a));	
		}
	}
	int ii = dict[""];
	printf("%s\n", dp[ii].w > 0 ? "First" : "Second");
	printf("%d %d\n", dp[ii].a, dp[ii].b);
}

int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 0; i < n; ++i)
			cin >> s[i];
		gao();
	}
	return 0;
}
