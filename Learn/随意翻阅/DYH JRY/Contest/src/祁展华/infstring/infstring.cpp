#include<set>
#include<map>
#include<cmath>
#include<queue>
#include<string>
#include<vector>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;
#define MOD 60988633526557ll
#define inf 2147483647
#define M 500010
#define LL long long
#define ULL unsigned long long
#define For(i,x,y) for(int i=(x);i<(y);i++)
#define rep(i,x,y) for(int i=(x);i<=(y);i++)
#define drep(i,x,y) for(int i=(x);i>=(y);i--)

inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}
	while('0'<=ch&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}

char ch[M];
LL res[M];ULL ha[2010][2010],power[2010];
set<ULL> S;

inline void init(int len){
	power[0]=1;For(i,1,len)power[i]=power[i-1]*151231ll;
	For(i,0,len){ha[i][i]=ch[i];For(j,i+1,len)ha[i][j]=ha[i][j-1]+power[j-i]*ch[j];}
}

inline bool ise(int l,int r,int x,int y){
	return ha[l][r]==ha[x][y];
}

int main(){
	freopen("infstring.in","r",stdin);
	freopen("infstring.out","w",stdout);
	int n=read(),q=read();scanf("%s",ch);
	int len=strlen(ch);For(i,len,1001)ch[i]=ch[i-len];init(1001);
	For(i,0,1001)rep(j,0,i){
		if(S.find(ha[j][i])==S.end())S.insert(ha[j][i]),res[i]++;
	}rep(i,1,1000)res[i]+=res[i-1];
	while(q--){
		int x=read();printf("%d\n",res[x-1]);
	}
	return 0;
}

