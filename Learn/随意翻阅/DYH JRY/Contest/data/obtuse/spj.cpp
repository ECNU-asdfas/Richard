#include <cstdlib>
#include <fstream>
#include <iostream>
#include <algorithm>
using namespace std;
#define rep(i,a,n) for (int i=a;i<n;i++)
const int N=301000;
int p[N],vis[N],n;
ifstream fin,fout,fstd;
ofstream fres;
void Return(int p,string s) {
	fres<<p<<endl;
	fres<<s<<endl;
	exit(0);
}
typedef long long ll;
bool check(ll a,ll b,ll c) {
	if (a>b) swap(a,b);
	if (a>c) swap(a,c);
	if (b>c) swap(b,c);
	if (a+b<=c) return 0;
	if (a*a+b*b>=c*c) return 0;
	return 1;
}
int	main(int args,char** argv) {
	ios::sync_with_stdio(0);
	fin.open(argv[1]);
	fstd.open(argv[2]);
	fout.open(argv[3]);
	fres.open(argv[4]);
	fin>>n;
	for (int i=0;i<3*n;i++) {
		fout>>p[i];
		if (p[i]<2||p[i]>3*n+1||vis[p[i]]) {
			Return(0,string("invalid partition"));
		}
		vis[p[i]]=1;
	}
	for (int i=0;i<n;i++) if (!check(p[3*i],p[3*i+1],p[3*i+2])) {
		Return(0,string("it is not an obtuse triangle"));
	}
	Return(1,string());
}
