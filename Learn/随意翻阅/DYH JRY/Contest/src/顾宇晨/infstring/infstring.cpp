#include<set>
#include<map>
#include<queue>
#include<cmath>
#include<string>
#include<cstdio>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
#define rep(i,a,b) for (int i=a; i<=b; i++)
#define per(i,a,b) for (int i=a; i>=b; i--)
using namespace std;
typedef long long LL;

inline int read() {
    int x=0,f=1; char ch=getchar();
    while (!(ch>='0'&&ch<='9')) {if (ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9') {x=x*10+(ch-'0'); ch=getchar();}
    return x*f;
}

const int N = 100005;
const int Mod = 3775331;
const int base = 27;

int n,len;
char s[N];
bool hash[Mod];
int bas[N];

int gethash(int l,int r) {
	int ret=0;
	per(i,r,l) {
		ret=(ret+1LL*(s[i]-'a'+1)*bas[r-i])%Mod;
	}
	return ret;
}

int main() {

    #ifndef ONLINE_JUDGE
        freopen("infstring.in","r",stdin);
        freopen("infstring.out","w",stdout);
    #endif

	n=read(); int q=read();
	scanf("%s",s); len=strlen(s);
	bas[0]=1; rep(i,1,1005) bas[i]=(1LL*bas[i-1]*base)%Mod;
	int totlen=len;
	while (totlen<=1005) {
		rep(i,totlen,totlen+len-1) s[i]=s[i-len];
		totlen+=len;
	}
	while (q--) {
		int x=read();
		memset(hash,0,sizeof(hash));
		int ans=0;
		rep(i,0,x-1) {
			rep(j,i,x-1) {
				int nowh=gethash(i,j);
				if (hash[nowh]) continue;
				hash[nowh]=1; ans++;
			}
		}
		cout<<ans<<endl;
	}

    return 0;
}

