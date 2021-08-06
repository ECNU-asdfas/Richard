#include<set>
#include<map>
#include<cmath>
#include<queue>
#include<string>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;
#define MOD 1000000007
#define inf 1047483647
#define For(i,x,y) for(int i=(x);i<(y);i++)
#define rep(i,x,y) for(int i=(x);i<=(y);i++)
#define drep(i,x,y) for(int i=(x);i>=(y);i--)

inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}
	while('0'<=ch&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}

int f[500010];
struct Node{
	int a,b,c,d;
} fr[500010];

int main(){
	freopen("obtuse.in","r",stdin);
	freopen("obtuse.out","w",stdout);
	int n=read();if(n>5)return puts("-1"),0;
	n*=3;f[0]=1;rep(i,0,(1<<n)-2)if(f[i]){
		int j;rep(k,0,n-1)if(((1<<k)&i)==0){j=k;break;}
		rep(k,j+1,n-1)if(((1<<k)&i)==0){
			rep(w,k+1,n-1)if(((1<<w)&i)==0&&j+2+k+2>w+2&&(j+2)*(j+2)+(k+2)*(k+2)<(w+2)*(w+2)){
				f[i|(1<<j)|(1<<k)|(1<<w)]=1;
				fr[i|(1<<j)|(1<<k)|(1<<w)]=(Node){i,j,k,w};
			}
		}
	}if(!f[(1<<n)-1])return puts("-1"),0;
	int i=(1<<n)-1;
	while(i){
		printf("%d %d %d\n",fr[i].b+2,fr[i].c+2,fr[i].d+2);
		i=fr[i].a;
	}
	return 0;
}

