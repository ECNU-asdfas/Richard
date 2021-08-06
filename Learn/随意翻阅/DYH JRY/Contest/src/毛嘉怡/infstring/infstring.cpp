#include <set>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
typedef long long ll;
#define rep(i, a, b) for (int i = a; i <= b; ++ i)
#define per(i, a, b) for (int i = a; i >= b; -- i)
const int N = 300005; const double eps = 1e-6;
using namespace std;
int n, m, cnt, a[N][26], mx[N], fail[N], s[N], rk[N], bin[N], sa[N], tmp[N];
char ch[N]; ll f[N], g[N], ans, sum; int h[N], mn[N][22];
set <int> L, R;
struct ques { int x, id; } b[N];
bool cmp(ques a, ques b) { return a.x < b.x; }
void Add(int p) { ans += mx[p] - mx[fail[p]]; }
void Del(int p) { ans -= mx[p] - mx[fail[p]]; }
int extend(int p, int c) {
	if (a[p][c] && mx[a[p][c]] == mx[p] + 1) return a[p][c];
	int np = ++ cnt; mx[np] = mx[p] + 1;
	for ( ; !a[p][c] && p; p = fail[p]) a[p][c] = np;
	if (!p) fail[np] = 1; else {
		int q = a[p][c];
		if (mx[q] == mx[p] + 1) fail[np] = q; else {
			int nq = ++ cnt; mx[nq] = mx[p] + 1;
			memcpy(a[nq], a[q], sizeof(a[q]));
			Del(q), fail[nq] = fail[q], fail[q] = fail[np] = nq, Add(q);
			for ( ; a[p][c] == q; p = fail[p]) a[p][c] = nq; Add(nq);
		}
	}
	Add(np);
	return np;
}
void suffix_array(int n) {
	int sz = max(n, 26);
	rep(i, 0, n - 1) rk[i] = s[i];
	rep(i, 0, sz - 1) bin[i] = 0;
	rep(i, 0, n - 1) ++ bin[rk[i]];
	rep(i, 1, sz - 1) bin[i] += bin[i - 1];
	per(i, n - 1, 0) sa[-- bin[rk[i]]] = i; 
	for (int j = 1; j <= n; j <<= 1) {
		int p = 0;
		rep(i, n - j, n - 1) tmp[p ++] = i;
		rep(i, 0, n - 1) if (sa[i] - j >= 0) tmp[p ++] = sa[i] - j;
		rep(i, 0, sz - 1) bin[i] = 0;
		rep(i, 0, n - 1) ++ bin[rk[i]];
		rep(i, 1, sz - 1) bin[i] += bin[i - 1];
		per(i, n - 1, 0) sa[-- bin[rk[tmp[i]]]] = tmp[i];
		tmp[sa[0]] = 0, p = 0;
		rep(i, 1, n - 1) {
			int v0 = sa[i - 1], v1 = sa[i], v00, v01;
			if (v0 + j < n) v00 = rk[v0 + j]; else v00 = - 1;
			if (v1 + j < n) v01 = rk[v1 + j]; else v01 = - 1;
			if (rk[v0] == rk[v1] && v00 == v01) tmp[sa[i]] = p; else tmp[sa[i]] = ++ p;
		}
		rep(i, 0, n - 1) rk[i] = tmp[i];
	}
}
int work(int i, int j, int ret) {
	for ( ; i + ret < 3 * n && j + ret < 3 * n && s[i + ret] == s[j + ret]; ) ++ ret;
	return ret;
}
void calc() {
	if (rk[0] == 0) h[0] = 0; else h[0] = work(sa[rk[0] - 1], 0, 0);
	rep(i, 1, 3 * n - 1) if (rk[i] == 0) h[i] = 0;
		else h[i] = work(sa[rk[i] - 1], i, max(h[i - 1] - 1, 0));
}
int getmn(int l, int r) {
	int i = floor(log(r - l + 1) / log(2) + eps);
	return min(mn[l][i], mn[r - (1 << i) + 1][i]);
}
void add(int l, int r) {
	int len = 3 * n - r, tmp = 2 * n - r;
	tmp = max(tmp, getmn(l + 1, r));
	sum += max(len - tmp, 0);
}
void del(int l, int r) {
	int len = 3 * n - r, tmp = 2 * n - r;
	tmp = max(tmp, getmn(l + 1, r));
	sum -= max(len - tmp, 0);
}
void solve() {
	g[0] = sum = 0;
	L.insert(-1), R.insert(3 * n);
	rep(i, 1, n) {
		int u = n - i;
		int l = *L.lower_bound(-u), r = *R.lower_bound(u);
		if (r < 3 * n) del(l, r);
		add(l, u); if (r < 3 * n) add(u, r);
		L.insert(-u), R.insert(u);
		g[i] = sum;
	}
}
void pre() {
	ans = 0, cnt = 1;
	int last = 1, top = 1;
	rep(i, 1, n) {
		last = extend(last, ch[i] - 'a');
		for ( ; top <= m && b[top].x == i; ++ top)
			f[b[top].id] = ans;
	}
	rep(i, 1, n) {
		last = extend(last, ch[i] - 'a');
		for ( ; top <= m && b[top].x == n + i; ++ top)
			f[b[top].id] = ans;
	}
	rep(i, 0, 3 * n - 1) s[3 * n - 1 - i] = ch[i % n + 1] - 'a';
	suffix_array(3 * n), calc();
	rep(i, 0, 3 * n - 1) mn[i][0] = h[i];
	rep(j, 1, 20) for (int i = 0; i + (1 << (j - 1)) < 3 * n; ++ i)
		mn[i][j] = min(mn[i][j - 1], mn[i + (1 << (j - 1))][j - 1]);
	solve();
	rep(i, top, m) f[b[i].id] = ans + g[n] * ((b[i].x - 2 * n) / n) + g[b[i].x % n];  
}
int main() {
	freopen("infstring.in", "r", stdin);
	freopen("infstring.out", "w", stdout);
	scanf("%d%d", &n, &m);
	scanf("%s", ch + 1);
	rep(i, 1, m) scanf("%d", &b[i].x), b[i].id = i;
	sort(b + 1, b + m + 1, cmp);
	pre();
	rep(i, 1, m) printf("%I64d\n", f[i]);
	return 0;
}
