#include <cstdio>
#include <algorithm>
#define L 1<<23
#define C (c=*A++)
#define ENS //__attribute__((optimize("-O2")))
#define NES inline//__attribute__((optimize("-O2"))) __inline__ __attribute__((always_inline))
#define N 400001

int s[N],t[N][26],le[N],len,link[N],wt,ss[19];char fl[L],*A=fl,fll[L],*B=fll;long long MAPLE[N];

NES void read(int &x){char c;x=0;while ('0'>C||c>'9');while ('0'<=c&&c<='9') x=(x<<3)+(x<<1)+c-48,C;}NES void print(long long x){if (!x) *B++=(48); else {for (wt=0;x;ss[++wt]=x%10,x/=10);for (;wt;*B++=(ss[wt]+48),wt--);}*B++='\n';}

ENS int main()
{
	freopen("infstring.in","r",stdin);freopen("2.out","w",stdout);int i,x,y,n,test,now,e,tp,q,last=1,cnt=1,len=-1;char c;
	for (*(fl+fread(fl,1,L,stdin))=EOF,read(n),read(test);'a'>C||c>'z';);for (i=0;i<n;s[i]=c-'a',C,i++);
	for (;test--;print(MAPLE[x]))
		for (read(x),--x;x>len;)
		{
			for (e=s[(++len)%n],MAPLE[len]=MAPLE[len-1],le[now=++cnt]=le[q=last]+1;q&&!t[q][e];t[q][e]=now,q=link[q]);
			if (q)
				if (le[q]+1==le[tp=t[q][e]]) link[now]=tp,MAPLE[len]+=le[now]-le[tp];
				else {for (++cnt,i=0;i<26;t[cnt][i]=t[tp][i],i++);for (link[cnt]=link[tp],le[cnt]=le[q]+1,MAPLE[len]+=le[now]-le[cnt],link[now]=link[tp]=cnt;q&&t[q][e]==tp;t[q][e]=cnt,q=link[q]);}
			else link[now]=1,MAPLE[len]+=le[now];last=now;
		}fwrite(fll,1,B-fll,stdout);
}
