#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<ctime>
using namespace std;
typedef long long ll;

const int N=300005;

int n;
int a[N],b[N],c[N];

#define sqr(x) ((ll)(x)*(x))

inline bool check(int i){
  int r=0; bool d;
  if (b[i]>c[i]) swap(b[i],c[i]),r=1;
  d=(a[i]+b[i]>c[i] && sqr(a[i])+sqr(b[i])<sqr(c[i]));
  if (r) swap(b[i],c[i]);
  return d;
}

int main(){
  srand(10086);
  freopen("obtuse.in","r",stdin);
  freopen("obtuse.out","w",stdout);
  scanf("%d",&n);
  for (int i=1;i<=n;i++)
    a[i]=i+1,b[i]=n+2*i,c[i]=n+2*i+1;
  for (int p=n;p;p--){
    if (check(p)) continue;
    while (1){
      int x=rand()%p+1;
      swap(c[x],b[p]);
      if (check(x) && check(p)) break;
      swap(c[x],b[p]);
    }
  }
  /*while (1){
    int p=0;
    for (int i=n;i;i--)
      if (!check(i))
	p=i;
    if (!p) break;
    while (1){
      int x=rand()%n+1,d=ran();
      swap(c[x],b[p]);
      if (check(x) && check(p)) break;
      swap(c[x],b[p]);
    }
    }*/
  for (int i=1;i<=n;i++)
    printf("%d %d %d\n",a[i],b[i],c[i]);
  return 0;
}
