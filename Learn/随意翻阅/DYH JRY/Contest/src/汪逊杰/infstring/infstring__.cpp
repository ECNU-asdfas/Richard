#include <map>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 10010;

inline int Min(int a, int b) {
	return a < b ? a : b;
}

char ch[N];
struct Pair {
	int x, y;
	inline friend bool operator <(const Pair &a, const Pair &b) {
		int len = Min(a.y - a.x, b.y - b.x);
		for (int i = 0; i <= len; i++)
			if (ch[i + a.x] != ch[i + b.x])
				return ch[i + a.x] < ch[i + b.x];
		return a.y - a.x < b.y - b.x;
	}
	Pair(int _x = 0, int _y = 0):x(_x), y(_y) {}
};
map<Pair, bool> S;
int n, q, last, ans, t, x;
int Ans[N];
struct Query {
	int a, i, ans;
	Query(int _a = 0, int _i = 0, int _ans = 0):a(_a), i(_i) {}
	inline friend bool operator <(const Query &a, const Query &b) {
		return a.a < b.a;
	}
};
Query a[N];

int main(void) {
	freopen("infstring.in", "r", stdin);
	freopen("infstring_.out", "w", stdout);
	scanf("%d %d\n", &n, &q);
	gets(ch); t = 1000 / n + 10;
	for (int j = n; j <= t; j += n)
		for (int i = 0; i < n; i++)
			ch[j + i] = ch[i];
	for (int i = 1; i <= q; i++) {
		scanf("%d", &x);
		a[i] = Query(x, i);
	}
	sort(a + 1, a + q + 1);
	for (int i = 1; i <= q; i++) {
		for (int k = last; k < a[i].a; k++)
			for (int j = 0; j <= k; j++) {
				if (!S[Pair(j, k)]) {
					S[Pair(j, k)] = 1; ans++;
				}
			}
		last = a[i].a - 1; a[i].ans = ans;
		swap(a[i].i, a[i].a);
	}
	sort(a + 1, a + q + 1);
	for (int i = 1; i <= q; i++)
		printf("%d\n", a[i].ans);
	fclose(stdin); fclose(stdout);
	return 0;
}
