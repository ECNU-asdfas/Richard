#include <cstdio>
#define L 1<<23
#define C (c=*A++)
#define ENS __attribute__((optimize("-O2")))
#define NES __attribute__((optimize("-O2"))) __inline__ __attribute__((always_inline))

int n,mx,lim,wt,ss[19];char fl[L],*A=fl;bool u[4001];

NES void read(int &x){char c;x=0;while ('0'>C||c>'9');while ('0'<=c&&c<='9') x=(x<<3)+(x<<1)+c-48,C;}NES void print(int x){if (!x) putchar(48); else {for (wt=0;x;ss[++wt]=x%10,x/=10);for (;wt;putchar(ss[wt]+48),wt--);}}
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
	freopen("obtuse.in","r",stdin);freopen("2.out","w",stdout);
	*(fl+fread(fl,1,L,stdin))=EOF;
//	u[2]=u[3]=u[4]=u[5]=u[6]=u[8]=u[7]=u[10]=u[16]=u[9]=u[14]=u[18]=u[11]=u[19]=u[22]=u[12]=u[20]=u[24]=true,
//	u[37]=u[33]=u[16]=true;
	read(n),mx=3*n+1,dfs(n);
}
