#include <set>
#include <cstdio>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

set< vector<string> > S;

bool gao(const vector<string> &vs) {
	if (S.find(vs) != S.end())
		return false;
	int vn = vs.size() - 1;
	if (vn == 0)
		return true;
	if (vn > 0 && (vs[vn - 1][0] == vs[vn][0] || vs[vn - 1][1] == vs[vn][1])) {
		vector<string> nvs(vs.begin(), vs.end() - 1);
		nvs[vn - 1] = vs[vn];
		if (gao(nvs))
			return true;
	}
	if (vn > 2 && (vs[vn - 3][0] == vs[vn][0] || vs[vn - 3][1] == vs[vn][1])) {
		vector<string> nvs(vs.begin(), vs.end() - 1);
		nvs[vn - 3] = vs[vn];
		if (gao(nvs))
			return true;
	}
	S.insert(vs);
	return false;
}

int main() {
	int n;
	while(cin >> n) {
		S.clear();
		vector<string> vs(n);
		for (int i = 0; i < n; ++i)
			cin >> vs[i];
		cout << (gao(vs) ? "YES" : "NO") << endl;
	}
	return 0;
}
