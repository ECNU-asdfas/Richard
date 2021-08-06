#include <cstdio>
#define L 1<<23
#define C (c=*A++)
#define ENS __attribute__((optimize("-O2")))
#define NES __attribute__((optimize("-O2"))) __inline__ __attribute__((always_inline))

int wt,ss[19];char fl[L],*A=fl;

NES void read(int &x){char c;x=0;while ('0'>C||c>'9');while ('0'<=c&&c<='9') x=(x<<3)+(x<<1)+c-48,C;}NES void print(int x){if (!x) putchar(48); else {for (wt=0;x;ss[++wt]=x%10,x/=10);for (;wt;putchar(ss[wt]+48),wt--);}}

ENS int main()
{
	freopen("t.in","r",stdin);freopen("t.out","w",stdout);
	
}
