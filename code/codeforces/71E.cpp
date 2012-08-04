#include <map>
#include <cstdio>
#include <string>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const char elem[][4] = { 
	"H",
	"He",
	"Li",
	"Be",
	"B",
	"C",
	"N",
	"O",
	"F",
	"Ne",
	"Na",
	"Mg",
	"Al",
	"Si",
	"P",
	"S",
	"Cl",
	"Ar",
	"K",
	"Ca",
	"Sc",
	"Ti",
	"V",
	"Cr",
	"Mn",
	"Fe",
	"Co",
	"Ni",
	"Cu",
	"Zn",
	"Ga",
	"Ge",
	"As",
	"Se",
	"Br",
	"Kr",
	"Rb",
	"Sr",
	"Y",
	"Zr",
	"Nb",
	"Mo",
	"Tc",
	"Ru",
	"Rh",
	"Pd",
	"Ag",
	"Cd",
	"In",
	"Sn",
	"Sb",
	"Te",
	"I",
	"Xe",
	"Cs",
	"Ba",
	"La",
	"Ce",
	"Pr",
	"Nd",
	"Pm",
	"Sm",
	"Eu",
	"Gd",
	"Tb",
	"Dy",
	"Ho",
	"Er",
	"Tm",
	"Yb",
	"Lu",
	"Hf",
	"Ta",
	"W",
	"Re",
	"Os",
	"Ir",
	"Pt",
	"Au",
	"Hg",
	"Tl",
	"Pb",
	"Bi",
	"Po",
	"At",
	"Rn",
	"Fr",
	"Ra",
	"Ac",
	"Th",
	"Pa",
	"U",
	"Np",
	"Pu",
	"Am",
	"Cm",
	"Bk",
	"Cf",
	"Es",
	"Fm",
	"Md",
	"No",
	"Lr",
	"Rf",
	"Db",
	"Sg",
	"Bh",
	"Hs",
	"Mt",
	"Ds",
	"Rg",
	"Cn",
	"Uut",
	"Fl",
	"Uup",
	"Lv",
	"Uus",
	"Uuo",
};

const int MAXN = 18;

string ele;
vector<int> can[110];
map<string, int> ele_map;
int n, m, max_v, vec[MAXN], tar[MAXN], dp[1 << MAXN][MAXN], pre[1 << MAXN][MAXN];

int main() {
	ele_map.clear();
	for (int i = 1; i <= 100; ++i)
		ele_map[elem[i - 1]] = i;
	while (cin >> n >> m) {
		for (int i = 0; i < n; ++i) {
			cin >> ele;
			vec[i] = ele_map[ele];
		}
		max_v = 0;
		for (int i = 0; i < m; ++i) {
			cin >> ele;
			tar[i] = ele_map[ele];
			max_v = max(max_v, tar[i]);
		}
		for (int i = 0; i <= max_v; ++i)
			can[i].clear();
		for (int mask = 0; mask < (1 << n); ++mask) {
			int sum = 0;
			for (int i = 0; i < n; ++i) {
				if (mask & (1 << i))
					sum += vec[i];
			}
			if (sum <= max_v)
				can[sum].push_back(mask);
		}
		memset(dp, 0, sizeof(dp));
		dp[0][0] = 1;
		for (int mask = 0; mask < (1 << n); ++mask) {
			for (int i = 0; i < m; ++i) {
				if (dp[mask][i]) {
					int v = tar[i];
					for (int j = 0; j < can[v].size(); ++j) {
						int nmask = can[v][j];
						if ((mask & nmask) == 0) {
							dp[mask | nmask][i + 1] = 1;
							pre[mask | nmask][i + 1] = mask;
						}
					}
				}
			}
		}
		int mask = (1 << n) - 1;
		if (dp[mask][m] == 0) {
			puts("NO");
		} else {
			puts("YES");
			for (int i = m; i > 0; --i) {
				vector<int> add;
				int nmask = mask ^ pre[mask][i];
				for (int j = 0; j < n; ++j) {
					if (nmask & (1 << j))
						add.push_back(j);
				}
				for (int j = 0; j < add.size(); ++j) {
					if (j) putchar('+');
					printf("%s", elem[vec[add[j]] - 1]);
				}
				printf("->%s\n", elem[tar[i - 1] - 1]);
				mask = pre[mask][i];
			}
		}
	}
	return 0;
}
