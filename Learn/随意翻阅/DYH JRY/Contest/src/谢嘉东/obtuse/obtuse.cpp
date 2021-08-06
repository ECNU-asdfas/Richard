#include<cstdio>  
#include<iostream>  
#include<algorithm>  
#include<cstdlib>  
#include<cstring>
#include<string>
#include<climits>
#include<vector>
#include<cmath>
#include<set>
#define LL long long

using namespace std;

int n,f[2010];
vector<int > dp[50010];
struct data
{
	int x,y,z;
}ans[100010];
set <int> S;
bool flag;
int main()
{	
	freopen("obtuse.in","r",stdin);
	freopen("obtuse.out","w",stdout);
	cin>>n;
	if (n>5)
	{
		for (int i=1;i<=n;i++)
			ans[i].x=i+1;
	flag=true;int p=0,s=3*n+1;
		while (p<=n)
		{
			flag=false;
			if (p>0)
			{
			ans[p].z=s;s--;
			ans[p].y=s;s--;
			if (ans[p].y+ans[p].x<=ans[p].z || ans[p].x*ans[p].x+ans[p].y*ans[p].y>=ans[p].z*ans[p].z) {flag=true;break;}
			}
			int t=n+1;
			for (int i=n;i>p;i--)
				ans[i].y=++t;
			for (int i=n;i>p;i--)
			{
				ans[i].z=++t;
				if (ans[i].y+ans[i].x<=ans[i].z || ans[i].x*ans[i].x+ans[i].y*ans[i].y>=ans[i].z*ans[i].z) {flag=true;break;}
			}
			if (!flag) break;
			p++;
		}
		if (!flag)
		{
			for (int i=1;i<=n;i++)
				printf("%d %d %d\n",ans[i].x,ans[i].y,ans[i].z);
			return 0;
		}
		flag=true,p=0,s=3*n+1;
		while (p<=n)
		{
			flag=false;
			if (p>0)
			{
			ans[p].z=s;s--;
			ans[p].y=s;s--;
			if (ans[p].y+ans[p].x<=ans[p].z || ans[p].x*ans[p].x+ans[p].y*ans[p].y>=ans[p].z*ans[p].z) {flag=true;break;}
			}
			int t=n+1;
			for (int i=n;i>p;i--)
				ans[i].y=++t;
			for (int i=p+1;i<=n;i++)
			{
				ans[i].z=++t;
				if (ans[i].y+ans[i].x<=ans[i].z || ans[i].x*ans[i].x+ans[i].y*ans[i].y>=ans[i].z*ans[i].z) {flag=true;break;}
			}
			if (!flag) break;
			p++;
		}
		if (!flag)
		{
			for (int i=1;i<=n;i++)
				printf("%d %d %d\n",ans[i].x,ans[i].y,ans[i].z);
			return 0;
		}
		else
		{
			flag=false;
				for (int i=n+2;i<=2*n+1;i++)
			S.insert(-i);
			S.insert(1000000010);
			for (int i=n+1;i>=2;i--)
			{
				int u=-(*S.lower_bound(-1000000010)),
				v=-(*S.lower_bound(-floor(sqrt((LL)u*u-(LL)i*i)-1e-9)));
				if (u-v>=i) break;
				ans[i].x= i,ans[i].y= v,ans[i].z= u;
				S.erase(- u), S.erase(- v);
			}
			flag=true;
			for (int i=2;i<=n+1;i++)
				printf("%d %d %d\n",ans[i].x,ans[i].y,ans[i].z);
			return 0;
		}
		cout<<-1<<endl;
	}
	else
	{
	int s=0;
	for (int i=2;i<=3*n-1;i++)
		for (int j=i+1;j<=3*n;j++)
			for (int k=j+1;k<=min(i+j-1,3*n+1);k++)
				if (i*i+j*j<k*k)
					f[++s]=(1<<(i-2))|(1<<(j-2))|(1<<(k-2)),
					ans[s].x=i,ans[s].y=j,ans[s].z=k;
	int Max=0;
	for(int i=1;i<=s;i++)
		for (int j=Max;j>=0;j--)
			if (dp[j].size()>0 || j==0)
				if ((j&f[i])==0 && dp[j|f[i]].size()==0)
				{
					for (int k=0;k<dp[j].size();k++)
						dp[f[i]|j].push_back(dp[j][k]);
					dp[f[i]|j].push_back(i);
					Max=max(Max,f[i]|j);
				}
	if (dp[(1<<(3*n))-1].size()==0) printf("-1\n");
	else
	{
		for (int i=0;i<n;i++)
			printf("%d %d %d\n",ans[dp[(1<<(3*n))-1][i]].x,ans[dp[(1<<(3*n))-1][i]].y,ans[dp[(1<<(3*n))-1][i]].z);
	}
	}
	return 0;
}

