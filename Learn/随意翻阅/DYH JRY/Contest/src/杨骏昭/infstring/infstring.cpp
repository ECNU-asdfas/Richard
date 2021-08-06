//by yjz
#include<algorithm>
#include<bitset>
#include<cstring>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<deque>
#include<fstream>
#include<iomanip>
#include<iostream>
#include<map>
#include<queue>
#include<set>
#include<stack>
#include<string>
#include<utility>
#include<vector>
using namespace std;
#define MP make_pair
#define PB push_back
#define FF first
#define SS second
typedef long long ll;
int n,q;
char s[300111];
int sa[300111],rk[300111],nsa[300111],nrk[300111],lg2[300111];
int b[300111],lcp[300111],tab[20][300111];
void makeb()
{
	memset(b,0,sizeof(b));
	for(int i=1;i<=n;i++)b[rk[i]]++;
	for(int i=1;i<=max(256,n);i++)b[i]+=b[i-1];
}
#define usb(i) MP(rk[i],i+k<=n?rk[i+k]:-1)
void construct_sa(int n)
{
	lg2[1]=0;
	for(int i=2;i<=300011;i++)lg2[i]=lg2[i>>1]+1;
	for(int i=1;i<=n;i++)rk[i]=s[i];
	makeb();
	for(int i=n;i>=1;i--)sa[b[rk[i]]--]=i;
	for(int k=1;k<n;k<<=1)
	{
		makeb();
		for(int i=n;i>=1;i--)if(sa[i]>k)nsa[b[rk[sa[i]-k]]--]=sa[i]-k;
		for(int i=n;i>=1;i--)if(sa[i]>n-k)nsa[b[rk[sa[i]]]--]=sa[i];
		nrk[nsa[1]]=1;
		for(int i=2;i<=n;i++)nrk[nsa[i]]=nrk[nsa[i-1]]+(usb(nsa[i-1])<usb(nsa[i]));
		swap(rk,nrk);
		swap(sa,nsa);
	}
	for(int i=1;i<=n;i++)rk[sa[i]]=i;
	
	int h=0;
	for(int i=1;i<=n;i++)
	{
		if(h>0)h--;
		if(rk[i]==1)continue;
		int j=sa[rk[i]-1];
		while(i+h<=n&&j+h<=n&&s[i+h]==s[j+h])h++;
		lcp[rk[i]-1]=h;
	}
/*	for(int i=1;i<=n;i++)
	{
		cout<<i<<":"<<sa[i]<<" ";
		printf("%s",s+sa[i]);
		cout<<" "<<lcp[i]<<endl;
	}*/
	for(int i=1;i<=n;i++)tab[0][i]=lcp[i];
	for(int i=1;i<20;i++)
	{
		for(int j=1;j<=n-(1<<i);j++)
		{
			tab[i][j]=min(tab[i-1][j],tab[i-1][j+(1<<(i-1))]);
		}
	}
}
int query(int x,int y)
{
	if(x>y)swap(x,y);
	int t=lg2[y-x];
	return min(tab[t][x],tab[t][y-(1<<t)]);
}
ll cur;
set<int>st;
void add(int x)
{
//	cout<<"add:"<<x<<endl;
	int l=-1,r=-1;
	set<int>::iterator it=st.lower_bound(x);
	if(it!=st.end())r=*it;
	if(it!=st.begin())
	{
		it--;
		l=*it;
		it++;
	}
	if(l!=-1&&r!=-1)cur-=query(l,r);
	st.insert(x);
	if(l!=-1)cur+=query(l,x);
	if(r!=-1)cur+=query(x,r);
//	cout<<"cur="<<cur<<endl;
}
ll ans[200111];
int main()
{
	freopen("infstring.in","r",stdin);
	freopen("infstring.out","w",stdout);
	bool same=1;
	scanf("%d%d",&n,&q);
	scanf("%s",s+1);
	reverse(s+1,s+n+1);
	int nn=2*n;
	for(int i=n+1;i<=nn;i++)s[i]=s[(i-1)%n+1];
	n=nn;
	for(int i=1;i<n;i++)same&=(s[i]==s[i+1]);
//	printf("%s\n",s+1);
	construct_sa(n);
	for(int i=n;i>=1;i--)
	{
		add(rk[i]);
		ans[i]=1ll*(n-i+1)*(n-i+2)/2-cur;
//		cout<<ans[i]<<" ";
	}
	for(int i=1;i<=q;i++)
	{
		int x;
		scanf("%d",&x);
		if(same)
		{
			printf("%d\n",x);
		}
		else
		{
			if(x<=n)printf("%I64d\n",ans[n-x+1]);
			else printf("%I64d\n",ans[1]+1ll*(n/2)*(x-n));
		}
	}
	return 0;
}
