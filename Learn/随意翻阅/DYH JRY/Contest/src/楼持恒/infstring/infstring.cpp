#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<map>
using namespace std;
#define ll unsigned long long
#define LL long long
map<ll,bool>M;
LL ans[200001],Add;
int i,j,k,n,m,l,sum,x,q;
char s[100001];
int main()
{
	freopen("infstring.in","r",stdin);
	freopen("infstring.out","w",stdout);
	scanf("%d%d",&n,&q);
	for(getchar(),i=0;i<n;i++)s[i]=getchar();
	for(i=0;i<n;i++)s[i+n]=s[i];
	n<<=1;
	ans[1]=1;M[s[0]]=1;
	for(i=2;i<=n;i++){
		sum=0;ans[i]=ans[i-1];
		for(j=i-1;j>=0;j--){
			sum=sum*127+s[j];
			if(!M[sum])ans[i]++,M[sum]=1;
		}
	}
	Add=ans[n]-ans[n-1];
	while(q--){
		scanf("%d",&x);
		if(x<=n)printf("%I64d\n",ans[x]);else printf("%I64d\n",ans[n]+(x-n)*Add);
	}
	return 0;
}
