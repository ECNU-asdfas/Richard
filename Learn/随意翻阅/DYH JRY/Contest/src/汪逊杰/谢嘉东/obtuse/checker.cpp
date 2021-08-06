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

int n,a[300010];

int main()
{
	freopen("obtuse.out","r",stdin);
	freopen("result.txt","w",stdout);
	int x,y,z;
	int Max=0; 
	while (cin>>x>>y>>z)
	{
		a[x]++;a[y]++;a[z]++;
		Max=max(Max,max(x,max(y,z)));
		if (x+y<=z) {cout<<"构不成三角形"<<endl;return 0;}
		if (x*x+y*y>=z*z) {cout<<"构不成dunjiao三角形"<<endl;cout<<x<<y<<z<<endl;return 0;}
	}
	if ((Max-1)%3!=0)  cout<<"shuziyouduaaaaa"<<endl;
	for (int i=2;i<=Max;i++)
		if (a[i]!=1) cout<<"shuziyoudu"<<endl;
	cout<<"wanmei"<<endl;
	return 0;
}
