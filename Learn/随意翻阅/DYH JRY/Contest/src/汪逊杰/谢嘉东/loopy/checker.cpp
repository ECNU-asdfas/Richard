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

int n,m,a[50][50],b[50][50];

int main()
{
	freopen("loopy1.in","r",stdin);
	cin>>n;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
			cin>>a[i][j];
	fclose(stdin);
	freopen("loopy1.out","r",stdin);
	freopen("result.txt","w",stdout);
	cin>>m;
	int p,q,x,y;
	cin>>p>>q;
	int X=p,Y=q;
	for (int i=2;i<=m;i++)
	{
		cin>>x>>y;
		if (x==p+1)
		{
			if(y!=q) {cout<<"Sure£¿"<<endl; return 0;} 
			b[x][y+1]++;
			b[x][y]++;
		}
		else if (x==p-1)
		{
			if(y!=q) {cout<<"Sure£¿"<<endl; return 0;} 
			b[x+1][y]++;
			b[x+1][y+1]++;
		}
		else if (y==q+1)
		{
			if(x!=p) {cout<<"Sure£¿"<<endl; return 0;} 
			b[x][y]++;
			b[x+1][y]++;
		}
		else
		{
			if(x!=p) {cout<<"Sure£¿"<<endl; return 0;} 
			b[x][y+1]++;
			b[x+1][y+1]++;
		}
		p=x,q=y;
	}
	x=X,y=Y;
	if (x==p+1)
		{
			if(y!=q) {cout<<"Sure£¿"<<endl; return 0;} 
			b[x][y+1]++;
			b[x][y]++;
		}
		else if (x==p-1)
		{
			if(y!=q) {cout<<"Sure£¿"<<endl; return 0;} 
			b[x+1][y]++;
			b[x+1][y+1]++;
		}
		else if (y==q+1)
		{
			if(x!=p) {cout<<"Sure£¿"<<endl; return 0;} 
			b[x][y]++;
			b[x+1][y]++;
		}
		else
		{
			if(x!=p) {cout<<"Sure£¿"<<endl; return 0;} 
			b[x][y+1]++;
			b[x+1][y+1]++;
		}
	int ans=0,w=0;
	for (int i=1;i<=n;i++)
	{
		for (int j=1;j<=n;j++)
			if (a[i][j]!=-1)
			{
				w++;
				if (a[i][j]==b[i][j]) ans++;
				cout<<b[i][j]<<" "; 
			}
			else cout<<b[i][j]<<" ";
		cout<<endl;
		}
	if (ans==w) cout<<10<<endl;
	else if (((double)(ans)/(double)w)>=0.95) cout<<7<<endl;
	else if (((double)(ans)/(double)w)>=0.8) cout<<5<<endl;
	else if (((double)(ans)/(double)w)>=0.7) cout<<4<<endl;
	else if (((double)(ans)/(double)w)>=0.6) cout<<3<<endl;
	else if (((double)(ans)/(double)w)>=0.4) cout<<2<<endl;
	else cout<<"SB!"<<endl;
	return 0;
}
