#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9') {if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9') {x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
int n,a[100005][4];
bool used[300005],get=0;
void dfs(int now){
	if (now>n){
		for (int i=1;i<=n;i++)
			printf ("%d %d %d\n",a[i][1],a[i][2],a[i][3]);
		get=1;
		return ;
	}
	for (int i=2;i<3*n;i++){
		if (used[i]) continue;
		a[now][1]=i;
		for (int k=3*n+1;k>i+1;k--){
			if (used[k]) continue;
			for (int j=k-1;j>i&&k<i+j;j--){
				if (i*i+j*j>=k*k||used[j]) continue;
				a[now][2]=j;a[now][3]=k;
				used[a[now][1]]=used[a[now][2]]=used[a[now][3]]=1;
				dfs(now+1);
				if (get) return ;
				used[a[now][1]]=used[a[now][2]]=used[a[now][3]]=0;
			}
		}
		return ;
	}
}
int main(){
	freopen ("obtuse.in","r",stdin);
	freopen ("obtuse.out","w",stdout);
	n=read();
	dfs(1);
	return 0;
}
