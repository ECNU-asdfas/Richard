#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

const int c[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
int map[1000][1000];
int n;
struct point {
	int x, y;
	point(int a = 0, int b = 0):x(a), y(b) {}
};
point p[1000000];
bool vis[1000][1000];
int cnt;

void check(void) {
	for (int i = 0; i <= n; i++)
		for (int j = 0; j <= n; j++)
			if (map[i][j]) return;
	for (int i = 1; i <= cnt; i++) printf("%d %d\n", p[i].x, p[i].y);
}
void dfs(int x, int y, int d = 1) {
	if (x == 0 && y == 0 && d) {
		check(); return;
	}
	for (int i = 0; i < 4; i++) {
		int a = x + c[i][0],
			b = y + c[i][1];
		if (a >= 0 && b >= 0 && a <= n && b <= n && !vis[a][b]) {
			vis[a][b] = 1; p[++cnt] = point(a, b);
			if (i & 1) {
				map[max(a, x)][max(b, y)]--; map[max(a, x)][max(b, y) + 1]--;
			} else {
				map[max(a, x)][max(b, y)]--; map[max(a, x) + 1][max(b, y)]--;
			}
			dfs(a, b); cnt--; vis[a][b] = 0;
			if (i & 1) {
				map[max(a, x)][max(b, y)]++; map[max(a, x)][max(b, y) + 1]++;
			} else {
				map[max(a, x)][max(b, y)]++; map[max(a, x) + 1][max(b, y)]++;
			}
		}
	}
}

int main(void) {
	freopen("loopy.in", "r", stdin);
	freopen("loopy.out", "w", stdout);
	cin >> n; //vis[0][0] = 1;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			cin >> map[i][j];
	dfs(0, 0, 0);
	fclose(stdin); fclose(stdin);
}
