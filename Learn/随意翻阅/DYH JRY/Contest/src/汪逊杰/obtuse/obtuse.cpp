#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

const int N = 11000;

int n, m, cnt;
bool vis[N];
int Sqrt[N][N];
struct tri {
	int x, y, z;
	tri(int _x = 0, int _y = 0, int _z = 0):x(_x), y(_y), z(_z) {}
};
tri ans[N];

inline int Min(int a, int b) {
	return a < b ? a : b;
}
void print(void) {
	for (int i = 1; i <= n; i++) {
		printf("%d %d %d\n", ans[i].x, ans[i].y, ans[i].z);
	}
	fclose(stdin); fclose(stdout);
	exit(0);
}
void dfs(int step) {
	int x, y, z;
	if (step > n) {
		print(); return;
	}
	for (int i = m; i >= 2; i--) {
		if (!vis[i]) {
			for (int j = i + 1; j <= m; j++)
			if (!vis[j]) {
				x = Sqrt[i][j] + 1;
				y = Min(i + j, m);
				for (int k = y; k >= x; k--)
				if (!vis[k]) {
					ans[++cnt] = tri(i, j, k);
					vis[i] = vis[j] = vis[k] = 1;
					dfs(step + 1); --cnt;
					vis[i] = vis[j] = vis[k] = 0;
				}
			}
		}
	}
}

int main(void) {
	freopen("obtuse.in", "r", stdin);
	freopen("obtuse.out", "w", stdout);
	cin >> n; m = n * 3 + 1;
	for (int i = 1; i <= m; i++)
		for (int j = i; j <= m; j++)
			Sqrt[i][j] = Sqrt[j][i] = sqrt(i * i + j * j);
	dfs(1); puts("-1");
	fclose(stdin); fclose(stdout);
	return 0;
}
