#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <cstring>
using namespace std;
int num,to[2000005],Next[2000005],head[2000005],a[2000005],f[2000005];
int n,Q,tsize,root;
char st[1000005];
void add(int x,int y)
{
    ++num;
    to[num]=y;
    Next[num]=head[x];
    head[x]=num;
}
int main()
{
    freopen("infstring.in","r",stdin);
    freopen("infstring.out","w",stdout);
    cin>>n>>Q;
    scanf("%s",st);
    for (int i=n;i<n+n;++i) st[i]=st[i-n];
    st[n+n]=st[0];
    tsize=0;
    for (int i=0;i<=n+n;++i)
    {
        root=0;
        int j=i;
        while (j>=0)
        {
            int flag=0;
            for (int k=head[root];k;k=Next[k]) if (a[to[k]]==st[j]) {flag=to[k];break;}
            if (!flag) {flag=++tsize;add(root,tsize);a[tsize]=st[j];}
            root=flag;
            --j;
        }
        f[i+1]=tsize;
    }
    long long tot=(long long)(f[n+n+1]-f[n+1]);
    for (int i=1;i<=Q;++i)
    {
        int x;
        scanf("%d",&x);
        if (x<=n+n)
        {
            printf("%d\n",f[x]);
            continue;
        }
        int t=x%n;
        if (t==0) t=n;
        t+=n;
        printf("%I64d\n",tot*((x-t)/n)+f[t]);
    }
    return 0;
}
