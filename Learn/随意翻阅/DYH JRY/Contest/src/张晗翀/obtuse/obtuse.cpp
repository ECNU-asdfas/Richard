#include<cstdio>
#include<cstdlib>
#include<cmath>
using namespace std;
const int maxn=100010;
struct rec
         {
         	int x,y,z;
		 }a[maxn];
int n;
bool vis[maxn*3];
void dfs(int step,int x)
{
	if (step>n)
	    {
	    	int i;
	    	for (i=1;i<=n;++i) printf("%d %d %d\n",a[i].x,a[i].y,a[i].z);
	    	fclose(stdin);fclose(stdout);exit(0);
		}
	if (vis[x]) {dfs(step,x+1);return;}
	int i,j;
	for (i=x+1,a[step].x=x;x*x+i*i<=9*n*n;++i)
	  if (!vis[i])
	      {
	      	for (j=sqrt(x*x+i*i)+1,vis[a[step].y=i]=true;j<x+i && j<=3*n+1;++j)
	      	  if (!vis[j]) vis[a[step].z=j]=true,dfs(step+1,x+1),vis[j]=false;
	      	vis[i]=false;
		  }
}
int main()
{
	freopen("obtuse.in","r",stdin);
	freopen("obtuse.out","w",stdout);
	scanf("%d",&n);dfs(1,2);puts("-1");
	fclose(stdin);fclose(stdout);
	return 0;
}
