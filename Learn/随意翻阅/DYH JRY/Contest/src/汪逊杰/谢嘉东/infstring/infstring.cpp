#include<cstdio>  
#include<iostream>  
#include<algorithm>  
#include<cstdlib>  
#include<cstring>
#include<string>
#include<climits>
#include<vector>
#include<cmath>
#define LL long long

using namespace std;

int n,m;
LL f[1010];
char s[1010];
const int Maxm=1000;
struct data
{
	int mo1,mo2;
	data(int a=0,int b=0):mo1(a),mo2(b){}
};
const int mo1=9940613,mo2=239641;
vector <data> q[Maxm+10];

bool check(int u,int v,int l)
{
	for (int i=0;i<q[l].size();i++)
		if (u==q[l][i].mo1 && v==q[l][i].mo2) return false;
	return true;
}

void init()
{
	memset(f,0,sizeof(f));
	int u=0,v=0;
	for (int i=1;i<=n;i++)
	{
		u=0,v=0;
		for (int j=i;j<=n;j++)
		{
			u=(u*26%mo1+s[j]-'a')%mo1;
			v=(v*26%mo2+s[j]-'a')%mo2;
			if (check(u,v,j-i+1)) q[j-i+1].push_back(data(u,v)),f[j]++;
		}
	}
	int x=0,y=0,h1=1,h2=1;
	for (int i=n+1;i<=Maxm;i++)
	{
		x=(x*26+s[(i-1)%n+1]-'a')%mo1;
		y=(y*26+s[(i-1)%n+1]-'a')%mo2;
		int u=x,v=y,p1=h1,p2=h2;
		h1=h1*26%mo1,h2=h2*26%mo2;
		for (int j=n;j>=1;j--)
		{
			p1=p1*26%mo1;u=(u+(s[j]-'a')*p1)%mo1;
			p2=p2*26%mo2;v=(v+(s[j]-'a')*p2)%mo2;
			if (check(u,v,i-j+1)) q[i-j+1].push_back(data(u,v)),f[i]++;
		}
	}
	for (int i=2;i<=Maxm;i++)
		f[i]+=f[i-1];
}

int main()
{
	freopen("infstring.in","r",stdin);
	freopen("infstring.out","w",stdout);
	scanf("%d%d",&n,&m);
	scanf("%s",s+1);
	init();
	int x;
	while(m--)
	{
		scanf("%d",&x);
		printf("%I64d\n",f[x]);
	}
	return 0;
}
