#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <cstring>
using namespace std;
bool flag=0;
int n,Next[100005],pre[100005],head;
int a[100005][4];
void dfs(int k,int p)
{
    if (k>n)
    {
        flag=1;
        return;
    }
    if (flag) return;
    if (flag) return;
    for (int i=head;i;i=Next[i])
    {
        if (flag) return;
        if (p==2)
        {
            if (i==head) {head=Next[head];a[k][2]=i;dfs(k,p+1);head=i;}
            else {Next[pre[i]]=Next[i];pre[Next[i]]=pre[i];a[k][2]=i;dfs(k,p+1);Next[pre[i]]=i;pre[Next[i]]=i;}
            continue;
        }
        if (flag) return;
        if (p==3)
        {
            if (a[k][1]+a[k][2]<=i || a[k][1]*a[k][1]+a[k][2]*a[k][2]>=i*i) continue;
            if (i==head) {head=Next[head];a[k][3]=i;dfs(k+1,2);head=i;}
            else {Next[pre[i]]=Next[i];pre[Next[i]]=pre[i];a[k][3]=i;dfs(k+1,2);Next[pre[i]]=i;pre[Next[i]]=i;}
            continue;
        }
        if (flag) return;
    }
    return;
}
int main()
{
    freopen("obtuse.in","r",stdin);
    freopen("obtuse.out","w",stdout);
    cin>>n;
    if (n>50) {cout<<-1<<endl;return 0;}
    head=n+2;
    for (int i=n+2;i<3*n+1;++i) Next[i]=i+1;
    for (int i=n+3;i<=3*n+1;++i) pre[i]=i-1;
    for (int i=1;i<=n;++i) a[i][0]=1,a[i][1]=i+1;
    dfs(1,2);
    if (!flag) {printf("-1\n");return 0;}
    for (int i=1;i<=n;++i) printf("%d %d %d\n",a[i][1],a[i][2],a[i][3]);
    return 0;
}
