#include<cstdlib>
#include<iostream>
#include<cstring>
using namespace std;


char a[1001];

int main()
{
	freopen("infstring.in","r",stdin);
	freopen("e.out","w",stdout);
	int n,m;
	scanf("%d %d\n",&n,&m);
	scanf("%s",a+1);
	int cnt=0;
	for(int i=1;i<=n;i++)
		for(int j=i;j<=n;j++)
			{
				int f=false;
				for(int k=1;k<i;k++)
				{
					for(int t=0;t<=j-i;t++)
					if(a[k+t]!=a[i+t])goto D;		
					f=true;
					goto ED;
					D:continue;	
				}
				ED:
				if(!f)cnt++;
			}
		printf("%d\n",cnt);
	return 0;
}
