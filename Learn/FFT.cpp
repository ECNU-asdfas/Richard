//By Richard
#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <ctime>
#define rep(x,y,z) for (int x=(y);(x)<=(z);(x)++)
#define per(x,y,z) for (int x=(y);(x)>=(z);(x)--)
#define log2(x) (31-__builtin_clz(x))
#define mod (int)(1e9+7)
#define inf 0x3f3f3f3f
#define cls(x) memset(x,0,sizeof(x))
#ifdef DEBUG
#define debugdo(X) X
#define debugndo(X)
#define debugout(X) cout<<(#X)<<"="<<(X)<<endl
#else
#define debugdo(X)
#define debugndo(X) X
#define debugout(X)
#endif // debug
#ifdef ONLINE_JUDGE
#define debugdo(X)
#define debugndo(X)
#define debugout(X)
#endif
#define putarray(x,n) rep(iiii,1,n) printf("%d ",x[iiii])
#define mp make_pair
using namespace std;
typedef pair<int,int> pairs;
typedef long long LL;
/////////////////////read3.0////////////////////////////////////
template <typename T>
inline void read(T &x){char ch;x=0;bool flag=false;ch=getchar();while (ch>'9'||ch<'0') {ch=getchar();if (ch=='-') flag=true;}while ((ch<='9'&&ch>='0')){x=x*10+ch-'0';ch=getchar();}if (flag) x*=-1;}
template <typename T>
inline void read(T &x,T &y){read(x);read(y);}
/////////////////variables&functions////////////////////
#define N 1048576
const double pi=3.141592653589793238462643383279502832793169399375105820974944592307816;
struct cp
{
	double x,y;
	cp(double x=0,double y=0):x(x),y(y){}
	cp operator+(cp c){return cp(x+c.x,y+c.y);}
	cp operator-(cp c){return cp(x-c.x,y-c.y);}
	cp operator*(cp c){return cp(x*c.x-y*c.y,x*c.y+y*c.x);}
	cp operator/(int c){return cp(x/c,y/c);}
}A[N],B[N];
int n,m,l,r[N];
void swap(cp &a,cp &b){cp t=a;a=b;b=t;}
void FFT(cp *a,int n,int op)
{
	for (int i=0;i<n;i++) if (i<r[i]) swap(a[i],a[r[i]]);
	for (int i=1;i<n;i<<=1)
	{
		cp wn(cos(pi/i),sin(pi/i)*op);
		for (int j=0;j<n;j+=(i<<1))
		{
			cp w(1,0);
			for (int k=0;k<i;++k,w=w*wn)
			{
				cp x=a[j+k],y=a[i+j+k]*w;
				a[j+k]=x+y; 
				a[i+j+k]=x-y;
			}
		}
	}
	if (op==-1) for (int i=0;i<n;i++) a[i]=a[i]/n;
}
int main()
{
	scanf("%d%d",&n,&m);
	for (int i=0,x;i<n;i++)scanf("%d",&x),A[i].x=x;
	for (int i=0,x;i<m;i++)scanf("%d",&x),B[i].x=x;
	for (m+=n-2,n=1,l=0;n<=m;n<<=1,++l);
	for (int i=0;i<n;i++) r[i]=(r[i>>1]>>1)|((i&1)<<(l-1));
	// for (int i=0;i<n;i++) printf("%d %d\n",i,r[i]);
	FFT(A,n,1); FFT(B,n,1);
	for (int i=0;i<n;i++) A[i]=A[i]*B[i];
	FFT(A,n,-1);
	for (int i=0;i<=m;i++)printf("%d ",(int)A[i].x);
	return 0;
}