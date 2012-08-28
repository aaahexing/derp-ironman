#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 200010;

struct EdgeNode {
	int i, ei, prev;
};

// EdgeList
int ecnt;
int prev[MAXN];
EdgeNode edge[MAXN * 2];

inline void init(int n) {
	ecnt = 0;
	memset(prev, -1, sizeof(int) * n);
}

inline void addEdge(int a, int b, int ei) {
	edge[ecnt].i = b;
	edge[ecnt].ei = ei;
	edge[ecnt].prev = prev[a];
	prev[a] = ecnt++;
}

vector<int> ans[MAXN];
int n, a[MAXN], b[MAXN], dp[MAXN];

int dfs(int i, int src, int depth) {
	dp[i] = 0;
	for (int j = prev[i]; j != -1; j = edge[j].prev) {
		if (edge[j].i != src) {
			int ii = edge[j].i;
			int cost = edge[j].ei & 1;
			dp[i] += dfs(ii, i, depth + 1) + cost;
		}
	}
	return dp[i];
}

void gao(int i, int src) {
	for (int j = prev[i]; j != -1; j = edge[j].prev) {
		if (edge[j].i != src) {
			int ii = edge[j].i;
			int cost = edge[j].ei & 1;
			dp[ii] = dp[ii] + (dp[i] - dp[ii] - cost) + (cost ^ 1);
			gao(ii, i);
		}
	}
}

int main() {
	while (scanf("%d", &n) != EOF) {
		init(n);
		for (int i = 0; i < n - 1; ++i) {
			scanf("%d%d", &a[i], &b[i]);
			--a[i], --b[i];
			addEdge(a[i], b[i], i * 2);
			addEdge(b[i], a[i], i * 2 + 1);
		}
		// pre-dfs
		dp[0] = dfs(0, -1, 0);
		// refine the dp-values with its father's information
		gao(0, -1);
		for (int i = 0; i < n; ++i) {
			ans[i].clear();
		}
		for (int i = 0; i < n; ++i) {
			ans[dp[i]].push_back(i);
		}
		for (int i = 0; i < n; ++i) {
			if (!ans[i].empty()) {
				printf("%d\n", i);
				for (int j = 0; j < ans[i].size(); ++j) {
					printf("%d ", ans[i][j] + 1);
				}
				puts("");
				break;
			}
		}
	}
	return 0;
}
