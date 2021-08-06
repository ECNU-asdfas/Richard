#include <bits/stdc++.h>

#define x first
#define y second
#define pb push_back
#define mp make_pair
#define vi vector<int>
#define pr pair<int,int>
#define Rep(i,a,b) for(int i=(int)(a);i<(int)(b);i++)
#define For(i,a,b) for(int i=(int)(a);i<=(int)(b);i++)
#define debug(x) {cout<<(#x)<<" "<<x<<endl;}

using namespace std;
typedef long long ll;
typedef unsigned long long ull;

const int N=200005,M=30,T=31,INF=9999999;
const ll P=48946513478743LL;

template<typename T>
inline void read(T& x,char s=getchar()) {
	x=0;
	while(s>'9'||s<'0') s=getchar();
	while(s<='9'&&s>='0') x=x*10+s-'0',s=getchar();
}

set<ll> s;

int ch[N*2][M];
ll _pow[N];
ll mx[N*2],fa[N*2];
ll preAns[N*2];
ll nosame=1;
int n,q,cnt=1,last=1;

ll calc(int x) {return mx[x]-mx[fa[x]];}

void insert(int x,int n) {
	ll tot=preAns[n-1];
	int p=last,np=last=++cnt;
	mx[np]=mx[p]+1;
//	cout<<mx[1]<<" "<<mx[2]<<endl;
	while (p && !ch[p][x]) ch[p][x]=np,p=fa[p];
	if (!p) {
		fa[np]=1,tot+=calc(np);
//		cout<<"C1: "<<calc(np)<<endl;
//		cout<<fa[np]<<" "<<mx[np]<<" "<<mx[fa[np]]<<endl;
	}
	else {
		int q=ch[p][x];
		if (mx[p]+1==mx[q]) fa[np]=q,tot+=calc(np);
		else {
			int nq=++cnt;mx[nq]=mx[p]+1;
			memcpy(ch[nq],ch[q],sizeof(ch[q]));
			fa[nq]=fa[q];tot+=calc(nq)-calc(q);
			fa[np]=fa[q]=nq;tot+=calc(np)+calc(q);
			while (p && ch[p][x]==q) ch[p][x]=nq,p=fa[p];
		}
	}
	preAns[n]=tot;
}
char c[N];

int main() {
	freopen("infstring.in","r",stdin);
	freopen("infstring.out","w",stdout);
//	cout<<P*T*T<<endl;
//	ll test=sqrt(P);
//	for(ll i=2;i<=test;i++) {
//		if(P%i==0) cout<<"NO"<<endl;
//	}
//	cout<<"End."<<endl;
	read(n),read(q);
	_pow[0]=1;
	for(int i=1;i<=n;i++) {
		c[i]=getchar();
		insert(c[i],i);
		_pow[i]=_pow[i-1]*T%P; 
	}
	for(int i=1;i<=n;i++) {
//		cout<<"-->"<<c[i]<<endl;
		insert(c[i],n+i);
	}
	
	ll now=0;
	for(int i=1;i<=n;i++) {
		now=(now*T+c[i]-'a')%P;
	}
	s.insert(now);
	
	for(int i=1;i<n;i++) {
		now=(now+P-(c[i]-'a')*_pow[n-1])%P;
		now=(now*T+c[i]-'a')%P;
		if(!s.count(now)) {
//			cout<<"insert: "<<i<<' '<<now<<endl;
			s.insert(now);
			nosame++;
		}
	}
	
	int x;
	for(int i=1;i<=q;i++) {
		read(x);
		if(x<=2*n) printf("%I64d\n",preAns[x]);
		else {
			ll ans=preAns[2*n];
			ans=ans+nosame*(x-2*n);
			printf("%I64d\n",ans);
		}
	}
	return 0;
}
/*
4 8
abaa
1
2
3
4
5
6
7
8
*/
