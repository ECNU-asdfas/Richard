#include<cstdio>
#include<cstdlib>
using namespace std;
const int maxn=35;
struct rec
         {
         	int x,y;
		 }ans[maxn*maxn];
int a[maxn][maxn],now[maxn][maxn],n,sta,tot;
bool vis[maxn][maxn];
bool check(int x,int y)
{
	return x>=0 && x<=n && y>=0 && y<=n && !vis[x][y];
}
void walk(int step,int x,int y)
{
	if (x==ans[1].x && y==ans[1].y)
	    {
	    	int i;
	    	for (i=1,printf("%d\n",step-2);i<step-1;++i) printf("%d %d\n",ans[i].x,ans[i].y);
	    	fclose(stdin);fclose(stdout);exit(0);
		}
	if (check(x-1,y)) vis[ans[step].x=x-1][ans[step].y=y]=true,walk(step+1,x-1,y);
	if (check(x,y-1)) vis[ans[step].x=x][ans[step].y=y-1]=true,walk(step+1,x,y-1);
	if (check(x,y+1)) vis[ans[step].x=x][ans[step].y=y+1]=true,walk(step+1,x,y+1);
	if (check(x+1,y)) vis[ans[step].x=x+1][ans[step].y=y]=true,walk(step+1,x+1,y);
	vis[x][y]=false;
}
void dfs(int step,int x,int y)
{
	if (step>2 && x==ans[1].x && y==ans[1].y)
	    {
	    	if (tot==0)
	    	    {
	    	    	int i;
	    	    	for (i=1,printf("%d\n",step-2);i<step-1;++i) printf("%d %d\n",ans[i].x,ans[i].y);
	    	    	fclose(stdin);fclose(stdout);exit(0);
				}
			vis[x][y]=false;return;
		}
	if ((double)1.68*tot<sta) {walk(step,x,y);return;}
	if (check(x-1,y) && (a[x][y]<0 || now[x][y]<a[x][y]) && (a[x][y+1]<0 || now[x][y+1]<a[x][y+1]))
	    {
	    	if (++now[x][y]==a[x][y]) --tot;
	    	if (++now[x][y+1]==a[x][y+1]) --tot;
	    	vis[ans[step].x=x-1][ans[step].y=y]=true;dfs(step+1,x-1,y);
	    	if (--now[x][y]==a[x][y]-1) ++tot;
	    	if (--now[x][y+1]==a[x][y+1]-1) ++tot;
		}
	if (check(x,y-1) && (a[x][y]<0 || now[x][y]<a[x][y]) && (a[x+1][y]<0 || now[x+1][y]<a[x+1][y]))
	    {
	    	if (++now[x][y]==a[x][y]) --tot;
	    	if (++now[x+1][y]==a[x+1][y]) --tot;
	    	vis[ans[step].x=x][ans[step].y=y-1]=true;dfs(step+1,x,y-1);
	    	if (--now[x][y]==a[x][y]-1) ++tot;
	    	if (--now[x+1][y]==a[x+1][y]-1) ++tot;
		}
	if (check(x,y+1) && (a[x][y+1]<0 || now[x][y+1]<a[x][y+1]) && (a[x+1][y+1]<0 || now[x+1][y+1]<a[x+1][y+1]))
	    {
	    	if (++now[x][y+1]==a[x][y+1]) --tot;
	    	if (++now[x+1][y+1]==a[x+1][y+1]) --tot;
	    	vis[ans[step].x=x][ans[step].y=y+1]=true;dfs(step+1,x,y+1);
	    	if (--now[x][y+1]==a[x][y+1]-1) ++tot;
	    	if (--now[x+1][y+1]==a[x+1][y+1]-1) ++tot;
		}
	if (check(x+1,y) && (a[x+1][y]<0 || now[x+1][y]<a[x+1][y]) && (a[x+1][y+1]<0 || now[x+1][y+1]<a[x+1][y+1]))
	    {
	    	if (++now[x+1][y]==a[x+1][y]) --tot;
	    	if (++now[x+1][y+1]==a[x+1][y+1]) --tot;
	    	vis[ans[step].x=x+1][ans[step].y=y]=true;dfs(step+1,x+1,y);
	    	if (--now[x+1][y]==a[x+1][y]-1) ++tot;
	    	if (--now[x+1][y+1]==a[x+1][y+1]-1) ++tot;
		}
	vis[x][y]=false;
}
int main()
{
	freopen("loopy.in","r",stdin);
	freopen("loopy.out","w",stdout);
	int i,j;
	for (i=1,scanf("%d",&n);i<=n;++i)
	  for (j=1;j<=n;++j)
	    {
	    	scanf("%d",&a[i][j]);
	    	if (a[i][j]>=0) ++tot;
	    	if (a[i][j]==3) ans[1].x=i-1,ans[1].y=j-1;
		}
	for (i=1;i<=n;++i) a[0][i]=a[n+1][i]=a[i][0]=a[i][n+1]=-1;
	sta=tot;dfs(2,ans[1].x,ans[1].y);
}
