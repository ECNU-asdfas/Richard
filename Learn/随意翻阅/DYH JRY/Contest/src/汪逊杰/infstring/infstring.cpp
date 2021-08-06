#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstring>
using namespace std;

typedef long long ll;

const int N = 4100, INF = 1 << 30;

inline int Min(int a, int b) {
	return a < b ? a : b;
}

inline void read(ll &x) {
	static char c; x = 0;
	for (c = getchar(); c < '0' || c > '9'; c = getchar());
	for (; c >= '0' && c <= '9'; c = getchar()) x = x * 10ll + c - '0';
}

char ch[N << 1];
int n, q;
ll x, tmp, ans, res, p;
ll delta[N], org[N];
ll Ans;
struct SuffixArray {
    int buc[N], SA[N], y[N], x[N];
    int height[N], rank[N];
	int m, len;
	char s[N];
	void Init(char* a, int l) {
		len = l; s[l] = 1;
		for (int i = 0; i < l; i++) s[i] = a[i];
		GetSA(); GetHeight(); Check();
	}
	void GetSA(void) {
		m = N - 10;
		for (int i = 0; i < m; i++) buc[i] = 0;
		for (int i = 0; i < len; i++) buc[x[i] = s[i]]++;
		for (int i = 1; i < m; i++) buc[i] += buc[i - 1];
		for (int i = len - 1; i >= 0; i--) SA[--buc[x[i]]] = i;
		for (int k = 1; k <= len; k <<= 1) {
			int p = 0;
			for (int i = len - 1; i >= len - k; i--) y[p++] = i;
			for (int i = 0; i < len; i++) if (SA[i] >= k) y[p++] = SA[i] - k;
			for (int i = 0; i < m; i++) buc[i] = 0;
			for (int i = 0; i < len; i++) buc[x[y[i]]]++;
			for (int i = 1; i < m; i++) buc[i] += buc[i - 1];
			for (int i = len - 1; i >= 0; i--) SA[--buc[x[y[i]]]] = y[i];
			swap(x, y);
			p = 1; x[SA[0]] = 0;
			for (int i = 1; i < len; i++) {
				if (y[SA[i - 1]] == y[SA[i]] && y[SA[i - 1] + k] == y[SA[i] + k])
					x[SA[i]] = p - 1;
				else x[SA[i]] = p++;
			}
			if (p >= len) break;
			m = p;
		}
	}
	void GetHeight(void) {
		int j, k = 0;
		for (int i = 0; i < len; i++) rank[SA[i]] = i;
		for (int i = 0; i < len; i++) {
			if (rank[i] == 0) {height[0] = 0; continue;}
			if (k) k--;
			int j = SA[rank[i] - 1];
			while (s[i + k] == s[j + k] && i + k < len && j + k < len) k++;
			height[rank[i]] = k;
		}
	}
	int Check(void) {
		int ans = (len + 1) * len / 2;
		for (int i = 1; i < len; i++) ans -= height[i];
		return ans;
	}
};
SuffixArray SA;

int main(void) {
	freopen("infstring.in", "r", stdin);
	freopen("infstring.out", "w", stdout);
	scanf("%d %d\n", &n, &q);
	gets(ch); 
	for (int i = 0; i < n; i++) ch[i + n] = ch[i];
	for (int i = 0; i < n; i++) ch[i + n * 2] = ch[i];
	for (int i = 0; i < 2 * n; i++) {
		SA.Init(ch, i + 1);
		org[i + 1] = SA.Check();
	}
	res = p = org[n * 2];
	for (int i = 0; i < n; i++) {
		SA.Init(ch, n * 2 + i + 1);
		delta[i + 1] = SA.Check() - p;
	}
	for (int i = 1; i <= q; i++) {
		read(x);
		if (x <= 2 * n) {
			printf("%I64d\n", org[x]);
		} else {
			tmp = x / n - 2;
			ans = tmp * delta[n] + delta[x % n] + res;
			printf("%I64d\n", ans);
		}
	}
	fclose(stdin); fclose(stdout);
	return 0;
}
