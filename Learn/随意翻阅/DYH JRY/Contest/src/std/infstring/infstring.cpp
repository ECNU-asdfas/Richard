#include <algorithm>
#include <cstdio>
#include <map>
#include <vector>
using namespace std;
#define rep(i,a,n) for (int i=a;i<n;i++)
#define per(i,a,n) for (int i=n-1;i>=a;i--)
#define pb push_back
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define SZ(x) ((int)(x).size())
#define fi first
#define se second
typedef vector<int> VI;
typedef long long ll;
typedef pair<int,int> PII;
const ll mod=1000000007;
ll powmod(ll a,ll b) {ll res=1;a%=mod;for(;b;b>>=1){if(b&1)res=res*a%mod;a=a*a%mod;}return res;}
// head

const int N=301000;
int rk[N][22],tot,l,n,q,x;
ll ans[N];
char s[N];
pair<PII,int> pos[N];
map<int,int> st;
void buildSA() {
	rep(i,1,l+1) rk[i][0]=s[i-1]-'a'+1;
	rep(j,1,20) {
		rep(i,1,l+1) pos[i]=mp(mp(rk[i][j-1],rk[max(i-(1<<(j-1)),0)][j-1]),i);
		sort(pos+1,pos+l+1);
		int cnt=1;
		rep(i,1,l+1) {
			rk[pos[i].se][j]=cnt;
			cnt+=(pos[i].fi!=pos[i+1].fi);
		}
	}
}
int LCP(int u,int v) {
	int l=0;
	per(j,0,20) if (rk[u][j]==rk[v][j]) {
		l+=(1<<j);
		u=max(0,u-(1<<j)); v=max(0,v-(1<<j));
	}
	return l;
}
int main() {
	freopen("infstring.in","r",stdin);
	freopen("infstring.out","w",stdout);
	scanf("%d%d",&n,&q);
	scanf("%s",s);
	l=3*n;
	int cur=0;
	rep(i,0,n) s[i+n]=s[i],s[i+2*n]=s[i];
	buildSA();
	rep(i,1,l+1) {
		ans[i]=ans[i-1]+i;
		map<int,int>::iterator it=st.lower_bound(rk[i][19]);
		if (it!=st.end()) ans[i]-=LCP(it->se,i);
		if (it!=st.begin()) {
			map<int,int>::iterator pit=it; --pit;
			ans[i]-=LCP(pit->se,i);
			if (it!=st.end()) ans[i]+=LCP(pit->se,it->se);
		}
		st[rk[i][19]]=i;
	}
	rep(i,0,q) {
		scanf("%d",&x);
		if (x<=l) printf("%I64d\n",ans[x]);
		else {
			int r=(x-1)%n+1;
			printf("%I64d\n",ans[r+n]+(x-r-n)/n*(ans[r+2*n]-ans[r+n]));
		}
	}
}
