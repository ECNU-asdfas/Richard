#include<iostream>
#include<cstdio>
#include<cstring>
#define rg register
#define rep(i,x,y) for(rg int i=(x);i<=(y);++i)
#define per(i,x,y) for(rg int i=(x);i>=(y);--i)
using namespace std;
namespace sjj118{
	
typedef long long LL;
const int N=1e5+10,alp=26,P=N<<1;
inline bool vaild(char c){return c>='a'&&c<='z';}
inline char gc(){char c=getchar();while(!vaild(c))c=getchar();return c;}
int n,q,s[N];
LL count[P],ans[N];
struct SAM{
	int tot,son[P][alp],pr[P],step[P];
	SAM(){tot=1;}
	int ins(int p,int c){
		int k=++tot;step[k]=step[p]+1;count[k]=count[p];
		while(p&&son[p][c]==0)son[p][c]=k,p=pr[p];
		if(p){
			int q=son[p][c];
			if(step[q]==step[p]+1)pr[k]=q,count[k]+=step[k]-step[q];
			else{
				int nq=++tot;step[nq]=step[p]+1;
				memcpy(son[nq],son[q],sizeof(son[q]));
				pr[nq]=pr[q];count[k]+=step[nq]-step[pr[nq]];
				count[k]-=step[q]-step[pr[q]];
				count[k]+=step[q]-step[nq];
				pr[q]=pr[k]=nq;
				count[k]+=step[k]-step[nq];
				while(p&&son[p][c]==q)son[p][c]=nq,p=pr[p];
			}
		}else pr[k]=1,count[k]+=step[k]-step[1];
		return k;
	}
	void build(int*a,int n){
		int k=1;
		rep(i,1,n){
			k=ins(k,a[i]);
			ans[i]=count[k];
		}
	}
}sam;
int main(){
	freopen("infstring.in","r",stdin);freopen("infstring.out","w",stdout);
	scanf("%d%d",&n,&q);
	rep(i,1,n)s[i]=gc()-'a';
	int m=n,p=0;
	while(m<100000){
		s[++m]=s[++p];
		if(p==n)p=0;
	}
	n=m;
	sam.build(s,n);
	rep(i,1,q){
		int x;scanf("%d",&x);
		printf("%I64d\n",ans[x]);
	}
	return 0;
}
}
int main(){
	return sjj118::main();
}
