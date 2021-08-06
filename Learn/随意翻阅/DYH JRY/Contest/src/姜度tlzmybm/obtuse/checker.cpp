#include <cstdio>
#define L 1<<23
#define C (c=*A++)
#define ENS //__attribute__((optimize("-O2")))
#define NES inline//__attribute__((optimize("-O2"))) __inline__ __attribute__((always_inline))
#define N 300007

int ti[N],wt,ss[19];char fl[L],*A=fl;

NES void read(int &x){char c;x=0;while ('0'>C||c>'9');while ('0'<=c&&c<='9') x=(x<<3)+(x<<1)+c-48,C;}NES void print(int x){if (!x) putchar(48); else {for (wt=0;x;ss[++wt]=x%10,x/=10);for (;wt;putchar(ss[wt]+48),wt--);}}

ENS int main()
{
	freopen("obtuse.in","r",stdin);
	int n,a,b,c,i;
	*(fl+fread(fl,1,L,stdin))=EOF,read(n);
	freopen("obtuse.out","r",stdin);freopen("t.out","w",stdout);
	for (*(fl+fread(fl,1,L,stdin))=EOF,A=fl,i=1;i<=n;i++)
		if (read(a),read(b),read(c),ti[a]++,ti[b]++,ti[c]++,(a>b||b>c||a>c)||a+b<=c||((long long)a*a+(long long)b*b>=(long long)c*c))
		{
			puts("NIE");return 0;
		}
	for (i=2;i<=3*n+1;i++) if (ti[i]!=1)
	{
		puts("NIE");return 0;
	}
	puts("TAK");
}
