#include <cstdio>
#include <iostream>
#include <cstring>
#define ll long long
#define mod 987321
using namespace std;
char s[10000];
int n,q,x;
ll h[10000],p[10000],ans;
int vis[1000000];
ll hash(int l,int r){
	return (h[r]+mod-(p[r-l+1]*h[l-1]%mod))%mod;
}
int main(){
	freopen ("infstring.in","r",stdin);
	freopen ("infstring.out","w",stdout);
	p[0]=1;
	for (int i=1;i<10000;i++) p[i]=(p[i-1]*27)%mod;
	scanf ("%d%d",&n,&q);
	scanf ("%s",s+1);
	for (int i=n;i<=1000;i++)
		s[i+1]=s[i%n+1];
	h[0]=0;
	for (int i=1;i<=1000;i++)
		h[i]=(27*h[i-1])%mod+s[i]-'a'+1;
	while (q--){
		ans=0;
		memset(vis,0,sizeof(vis));
		scanf ("%d",&x);
		for (int l=1;l<=x;l++){
			for (int i=1;i+l-1<=x;i++){
				int ha=hash(i,i+l-1);
				if (vis[ha]<l){
					ans++;
					vis[ha]=l;
				}
			}
		}
		printf ("%lld\n",ans);
	}
	return 0;
}

