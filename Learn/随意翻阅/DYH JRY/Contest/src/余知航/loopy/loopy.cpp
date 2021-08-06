#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <cstring>
using namespace std;
bool FLAG=0;
int dx[5],dy[5],sx,sy;
int m=0,flag[1005][1005],a[1005][1005],flag1[31][31][31][31];
int n;
struct node
{
    int x,y;
}ans[1000005];
int d=0;
void dfs(int x,int y,int tot)
{
    if (tot==0 && x==sx && y==sy)
    {
        FLAG=1;
        cout<<m<<endl;
        for (int i=1;i<=m;++i) printf("%d %d\n",ans[i].x,ans[i].y);
        return;
    }
    if (FLAG) return;
    for (int i=1;i<=4;++i)
    {
        if (FLAG) return;
        int xx=x+dx[i],yy=y+dy[i];
        if (xx<0 || yy<0 || xx>n || yy>n) continue;
        if (flag1[x][y][xx][yy] || flag[xx][yy]) continue;
        if (i==1)
        {
            if (a[x][y+1]!=0 && a[x][y]!=0)
            {
                if (flag[xx][yy]) continue;
                flag[xx][yy]=1;
                ans[++m]={xx,yy};
                int res=0;
                if (a[x][y+1]!=-1) --a[x][y+1],++res;
                if (a[x][y]!=-1) --a[x][y],++res;
                flag1[x][y][xx][yy]=flag1[xx][yy][x][y]=1;
                dfs(xx,yy,tot-res);
                --m;
                flag1[x][y][xx][yy]=flag1[xx][yy][x][y]=0;
                if (a[x][y+1]!=-1) ++a[x][y+1];
                if (a[x][y]!=-1) ++a[x][y];
                flag[xx][yy]=0;
            }
        }
        if (i==2)
        {
            if (a[x+1][y]!=0 && a[x+1][y+1]!=0)
            {
                if (flag[xx][yy]) continue;
                flag[xx][yy]=1;
                ans[++m]={xx,yy};
                int res=0;
                if (a[x+1][y+1]!=-1) --a[x+1][y+1],++res;
                if (a[x+1][y]!=-1) --a[x+1][y],++res;
                flag1[x][y][xx][yy]=flag1[xx][yy][x][y]=1;
                dfs(xx,yy,tot-res);
                --m;
                flag1[x][y][xx][yy]=flag1[xx][yy][x][y]=0;
                if (a[x+1][y+1]!=-1) ++a[x+1][y+1];
                if (a[x+1][y]!=-1) ++a[x+1][y];
                flag[xx][yy]=0;
            }
        }
        if (i==3)
        {
            if (a[x+1][y]!=0 && a[x][y]!=0)
            {
                if (flag[xx][yy]) continue;
                flag[xx][yy]=1;
                ans[++m]={xx,yy};
                int res=0;
                if (a[x+1][y]!=-1) --a[x+1][y],++res;
                if (a[x][y]!=-1) --a[x][y],++res;
                flag1[x][y][xx][yy]=flag1[xx][yy][x][y]=1;
                dfs(xx,yy,tot-res);
                --m;
                flag1[x][y][xx][yy]=flag1[xx][yy][x][y]=0;
                if (a[x+1][y]!=-1) ++a[x+1][y];
                if (a[x][y]!=-1) ++a[x][y];
                flag[xx][yy]=0;
            }
        }
        if (i==4)
        {
            if (a[x+1][y+1]!=0 && a[x][y+1]!=0)
            {
                if (flag[xx][yy]) continue;
                flag[xx][yy]=1;
                ans[++m]={xx,yy};
                int res=0;
                if (a[x+1][y+1]!=-1) --a[x+1][y+1],++res;
                if (a[x][y+1]!=-1) --a[x][y+1],++res;
                flag1[x][y][xx][yy]=flag1[xx][yy][x][y]=1;
                dfs(xx,yy,tot-res);
                --m;
                flag1[x][y][xx][yy]=flag1[xx][yy][x][y]=0;
                if (a[x+1][y+1]!=-1) ++a[x+1][y+1];
                if (a[x][y+1]!=-1) ++a[x][y+1];
                flag[xx][yy]=0;
            }
        }
    }
}
int main()
{
    freopen("loopy.in","r",stdin);
    freopen("loopy.out","w",stdout);
    cin>>n;
    sx=-1,sy=-1;
    int tot=0;
    for (int i=0;i<=n+1;++i) for (int j=0;j<=n+1;++j) a[i][j]=-1;
    for (int i=1;i<=n;++i)
        for (int j=1;j<=n;++j)
        {
            scanf("%d",&a[i][j]);
            if (a[i][j]!=-1) tot+=a[i][j];
            if (a[i][j]==3 && sx<0 && sy<0) sx=i,sy=j;
        }
    if (sx==-1 && sy==-1) sx=0,sy=0;
    dx[1]=-1;dx[2]=1;dx[3]=0;dx[4]=0;
    dy[1]=0;dy[2]=0;dy[3]=-1;dy[4]=1;
    dfs(sx,sy,tot);
    return 0;
}
