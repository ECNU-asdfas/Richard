#include<cstdio>
#include<cstdlib>
#include<algorithm>
using namespace std;

const int N=100005;

int vst[N*3];

inline bool check(int a,int b,int c){
  return a+b>c && a*a+b*b<c*c;
}

int main(){
  int a[3];
  freopen("obtuse.in","r",stdin);
  freopen("obtuse1.out","w",stdout);
  int n;
  scanf("%d",&n);
  freopen("obtuse.out","r",stdin);
  for (int i=1;i<=n;i++){
    scanf("%d%d%d",a,a+1,a+2);
    printf("%d %d %d\n",a[0],a[1],a[2]);
    sort(a+1,a+3);
    if (vst[a[0]]) printf("-1\n");
    if (vst[a[1]]) printf("-1\n");
    if (vst[a[2]]) printf("-1\n");
    if (!check(a[0],a[1],a[2])) printf("-1\n");
    vst[a[0]]=vst[a[1]]=vst[a[2]]=1;
  }
  return 0;
}
