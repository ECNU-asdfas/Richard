#include <set>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
typedef long long ll;
#define rep(i, a, b) for (int i = a; i <= b; ++ i)
const int N = 300005, inf = 1000000007; const double eps = 1e-5;
using namespace std;
int n, p[N][3]; bool flg;
set <int> S;
void solve() {
	rep(i, n + 2, 3 * n + 1) S.insert(-i);
	S.insert(inf);
	for (int i = n + 1; i >= 2; -- i) {
		int u = -(*S.lower_bound(-inf)), v = - (*S.lower_bound(- floor(sqrt((ll) u * u - (ll) i * i) - eps)));
		if (u - v >= i) return ;
		p[i][0] = i, p[i][1] = v, p[i][2] = u;
		S.erase(- u), S.erase(- v);
	}
	flg = true;
}
int main() {
	freopen("obtuse.in", "r", stdin);
	freopen("obtuse.out", "w", stdout);
	scanf("%d", &n);
	flg = false;
	solve();
	if (flg) {
		rep(i, 2, n + 1) printf("%d %d %d\n", p[i][0], p[i][1], p[i][2]);
		return 0;
	}
	printf("-1");
	return 0;
}
