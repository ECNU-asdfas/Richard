#include <cstdio>
#include <cmath>
#include <algorithm>
#define L 1<<23
#define C (c=*A++)
#define ENS //__attribute__((optimize("-O2")))
#define NES inline//__attribute__((optimize("-O2"))) __inline__ __attribute__((always_inline))
#define N 300007

using namespace std;int j,a[N],n,mx,f[N],g[N],wt,ss[19];char fl[L],*A=fl;bool u[N];

NES void read(int &x){char c;x=0;while ('0'>C||c>'9');while ('0'<=c&&c<='9') x=(x<<3)+(x<<1)+c-48,C;}NES void print(int x){if (!x) putchar(48); else {for (wt=0;x;ss[++wt]=x%10,x/=10);for (;wt;putchar(ss[wt]+48),wt--);}}
NES int F(int x){return f[x]?f[x]=F(f[x]):x;}NES int G(int x){return g[x]?g[x]=G(g[x]):x;}
NES bool dfs(int x)
{
	if (!x) return true;
	for (int k=mx;k>3;k--)
		if (!u[k])
			for (int j=k-1;j>2;j--)
				if (!u[j])
				{
					for (int i=j-1;i>1;i--)
						if (!u[i]&&(i+j>k&&i*i+j*j<k*k))
							if ((u[i]=u[j]=u[k]=true,dfs(x-1)))
								{print(i),putchar(' '),print(j),putchar(' '),print(k),putchar('\n');return true;}
							else u[i]=u[j]=u[k]=false;
				}return false;
}

ENS int main()
{
	freopen("obtuse.in","r",stdin);freopen("obtuse.out","w",stdout);
	int n,i,t1,t2,t3,t4,j;long long tmp,tp;
	if (*(fl+fread(fl,1,L,stdin))=EOF,read(n),mx=3*n+1,n<=19) {dfs(n);return 0;}
	else
		if (n==20)
		{
			puts("17 22 28");
			puts("15 24 29");
			puts("19 23 30");
			puts("16 26 31");
			puts("21 25 33");
			puts("20 27 34");
			puts("18 32 37");
			puts("13 35 38");
			puts("14 36 39");
			puts("11 40 42");
			puts("12 41 43");
			puts("2 44 45");
			puts("3 46 47");
			puts("4 48 49");
			puts("5 50 51");
			puts("6 52 53");
			puts("7 54 55");
			puts("8 56 57");
			puts("9 58 59");
			puts("10 60 61");
		}
		else
		{
			int lim=0.63*mx;
			for (i=mx;i>lim;i--)
				if (!f[i])
				{
					t1=F(2),t2=G((int)sqrt((long long)i*i-(long long)t1*t1+0.5));
					t1=G((int)sqrt((long long)i*i-(long long)t2*t2-0.5));
					print(t1),putchar(' '),print(t2),putchar(' '),print(i),putchar('\n');
					f[t1]=t1+1,g[t1]=t1-1,f[t2]=t2+1,g[t2]=t2-1,f[i]=i+1,g[i]=i-1;
				}
			for (;i>1;i--)
				if (!g[i])
				{
					for (tmp=2147483647,t2=(long long)i*i,j=2;j<i;j++)
						if (!g[j])
						{
							t1=G((int)sqrt(t2-(long long)j*j+0.5));
							if (t1!=1&&(tp=t2-(long long)j*j-(long long)t1*t1)<tmp&&tp>0)
								t3=t1,t4=j,tmp=tp;
						}
					if (t3>t4) swap(t3,t4);
					print(t3),putchar(' '),print(t4),putchar(' '),print(i),putchar('\n');
					g[t3]=t3-1,g[t4]=t4-1,g[i]=i-1;
				}
		}
}
