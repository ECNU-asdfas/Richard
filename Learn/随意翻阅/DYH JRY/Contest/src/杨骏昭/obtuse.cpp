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
bool hs[300111];
int a[1011],an,n;
void out()
{
	for(int i=0;i<an;i+=3)
	{
		cout<<a[i]<<" "<<a[i+1]<<" "<<a[i+2]<<endl;
	}
	exit(0);
}
void dfs(int x)
{
//	cout<<"dfs:"<<x<<endl;
//	for(int i=0;i<an;i++)cout<<a[i]<<" ";cout<<endl;
	a[an++]=x;
	hs[x]=1;
	for(int i=3*n+1;i>=n+2;i--)
	{
		if(hs[i])continue;
		for(int j=i-x+1;j<i;j++)
		{
			if(hs[j])continue;
			if(x+j<=i)break;
//			cout<<x<<" "<<j<<" "<<i<<endl;
			if(x*x+j*j<i*i)
			{
				hs[i]=1;
				hs[j]=1;
				a[an++]=j;a[an++]=i;
				int k=2;
				while(hs[k])k++;
				if(k>3*n+1)
				{
					out();
				}
				else
				{
					dfs(k);
				}
				an-=2;
				hs[i]=0;
				hs[j]=0;
			}
		}
	}
	hs[x]=0;
	an--;
}
int b[100111][3];
int main()
{
	freopen("obtuse.in","r",stdin);
	freopen("obtuse.out","w",stdout);
	cin>>n;
	if(n<=20)dfs(2);
	for(int i=2;i<=n+1;i++)b[i-1][0]=i,hs[i]=1;
	int it=3*n+1;
	for(int i=1;i<=n;i++)
	{
		while(hs[it])it--;
		if(hs[it-i])break;
		b[i][2]=it;
		hs[it]=1;
		int j=it-i;
		hs[j]=1;
		b[i][1]=j;
	}
	it=2;
	for(int i=1;i<=n;i++)
	{
		if(b[i][1]==0)
		{
			while(hs[it])it++;
			hs[it]=1;
			b[i][1]=it;
		}
	}
	for(int i=1;i<=n;i++)
	{
		if(b[i][2]==0)
		{
			while(hs[it])it++;
			hs[it]=1;
			b[i][2]=it;
		}
	}
	bool f=1;
	for(int i=1;i<=n;i++)
	{
		printf("%d %d %d\n",b[i][0],b[i][1],b[i][2]);
		f&=(b[i][0]+b[i][1]>b[i][2])&&(1ll*b[i][0]*b[i][0]+1ll*b[i][1]*b[i][1]<1ll*b[i][2]*b[i][2]);
		if(f==0)
		{
			cout<<"WA!"<<endl;
			return 0;
		}
	}
//	cout<<f<<endl;
	return 0;
}
