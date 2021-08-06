#include <cstdlib>
#include <cmath>
#include <fstream>
#include <iostream>
#include <algorithm>
using namespace std;
#define rep(i,a,n) for (int i=a;i<n;i++)
ifstream fin,fout,fstd;
ofstream fres;
const int N=35;
int n,cnum,sat,m,per[N][N],vis[N][N],edge[N][N];
int x[N*N],y[N*N];
void Return(int p,string s) {
	if (cnum==sat) fres<<1<<endl;
	else if (sat*20>=cnum*19) fres<<0.7<<endl;
	else if (sat*20>=cnum*16) fres<<0.5<<endl;
	else if (sat*20>=cnum*14) fres<<0.4<<endl;
	else if (sat*20>=cnum*12) fres<<0.3<<endl;
	else if (sat*20>=cnum*8) fres<<0.2<<endl;
	else if (sat*20>=cnum*4) fres<<0.1<<endl;
	else fres<<0<<endl;
	fres<<s<<endl;
	exit(0);
}
int	main(int args,char** argv) {
	ios::sync_with_stdio(0);
	fin.open(argv[1]);
	fstd.open(argv[2]);
	fout.open(argv[3]);
	fres.open(argv[4]);
	fin>>n;
	cnum=0;
	rep(i,1,n+1) rep(j,1,n+1) {
		fin>>per[i][j];
		if (per[i][j]!=-1) cnum++;
	}
	fout>>m;
	rep(i,0,m) {
		fout>>x[i]>>y[i];
		if (x[i]<0||x[i]>n||y[i]<0||y[i]>n||vis[x[i]][y[i]]) {
			Return(0,"not a cycle");
		}
		vis[x[i]][y[i]]=1;
	}
	rep(i,0,m) {
		int dis=abs(x[i]-x[(i+1)%m])+abs(y[i]-y[(i+1)%m]);
		if (dis!=1) {
			Return(0,"not a cycle");
		}
	}
	rep(i,0,m) {
		int px=x[i],py=y[i],qx=x[(i+1)%m],qy=y[(i+1)%m];
		if (px==qx) {
			if (py>qy) swap(py,qy);
			edge[px+1][py+1]++;
			edge[px][py+1]++;
		} else {
			if (px>qx) swap(px,qx);
			edge[px+1][py+1]++;
			edge[px+1][py]++;
		}
	}
	sat=0;
	rep(i,1,n+1) rep(j,1,n+1) if (per[i][j]==edge[i][j]) sat++;
	Return(sat,"");
}
