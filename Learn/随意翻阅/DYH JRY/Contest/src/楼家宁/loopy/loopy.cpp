#include <cstdio>
#include <string>
#include <cstring>
#include <cstdlib>
#include <ctime>
#define N 50
#define S 0
#define T N*N*2+2
#define inf 1<<30

using namespace std;

int n,A[N][N],Ans[N*N*N][2],p,pt[N*N*N][2],ptt,cnt,tt,ben[N][N][N][N],P[N][N],mx;

bool dfs(int x,int y,int lx,int ly){
	if(x==lx&&y==ly&&p){
		if(cnt==tt){
			printf("%d\n",p);
			for(int i=1;i<=p;i++) printf("%d %d\n",Ans[i][0],Ans[i][1]);
			exit(0);
		}
		if(cnt>mx){
			mx=cnt;
			ptt=p;
			memcpy(pt,Ans,sizeof(Ans));
		}
		return true;
		return false;
	}
	if(P[x][y])return false;
	P[x][y]=1;
	Ans[++p][0]=x;Ans[p][1]=y;
	//x+1
	if(x+1<=n&&(!ben[x+1][y][x][y])&&(y==n||(A[x][y]>0||A[x][y]==-1))&&(y==0||A[x][y-1]>0||A[x][y-1]==-1)){
		if(y!=n&&A[x][y]>0){
			A[x][y]--;
			if(A[x][y]==0) cnt++;
		}
		if(y!=0&&A[x][y-1]>0){
			A[x][y-1]--;
			if(A[x][y-1]==0) cnt++;
		}
		ben[x+1][y][x][y]=ben[x][y][x+1][y]=1;
		if(dfs(x+1,y,lx,ly))return true;
		ben[x+1][y][x][y]=ben[x][y][x+1][y]=0;
		if(y!=n&&A[x][y]>=0){
			if(A[x][y]==0) cnt--;
			A[x][y]++;
		}
		if(y!=0&&A[x][y-1]>=0){
			if(A[x][y-1]==0) cnt--;
			A[x][y-1]++;
		}
	}
	//x-1
	if(x-1>=0&&(!ben[x-1][y][x][y])&&(y==n||(A[x-1][y]>0||A[x-1][y]==-1))&&(y==0||A[x-1][y-1]>0||A[x-1][y-1]==-1)){
		if(y!=n&&A[x-1][y]>0){
			A[x-1][y]--;
			if(A[x-1][y]==0) cnt++;
		}
		if(y!=0&&A[x-1][y-1]>0){
			A[x-1][y-1]--;
			if(A[x-1][y-1]==0) cnt++;
		}
		ben[x-1][y][x][y]=ben[x][y][x-1][y]=1;
		if(dfs(x-1,y,lx,ly))return true;
		ben[x-1][y][x][y]=ben[x][y][x-1][y]=0;
		if(y!=n&&A[x-1][y]>=0){
			if(A[x-1][y]==0) cnt--;
			A[x-1][y]++;
		}
		if(y!=0&&A[x-1][y-1]>=0){
			if(A[x-1][y-1]==0) cnt--;
			A[x-1][y-1]++;
		}
	}
	//y+1
	if(y+1<=n&&(!ben[x][y+1][x][y])&&(x==n||(A[x][y]>0||A[x][y]==-1))&&(x==0||A[x-1][y]>0||A[x-1][y]==-1)){
		if(x!=n&&A[x][y]>0){
			A[x][y]--;
			if(A[x][y]==0) cnt++;
		}
		if(x!=0&&A[x-1][y]>0){
			A[x-1][y]--;
			if(A[x-1][y]==0) cnt++;
		}
		ben[x][y+1][x][y]=ben[x][y][x][y+1]=1;
		if(dfs(x,y+1,lx,ly))return true;
		ben[x][y+1][x][y]=ben[x][y][x][y+1]=0;
		if(x!=n&&A[x][y]>=0){
			if(A[x][y]==0) cnt--;
			A[x][y]++;
		}
		if(x!=0&&A[x-1][y]>=0){
			if(A[x-1][y]==0) cnt--;
			A[x-1][y]++;
		}
	}
	//y-1
	if(y-1>=0&&(!ben[x][y-1][x][y])&&(x==n||(A[x][y-1]>0||A[x][y-1]==-1))&&(x==0||A[x-1][y-1]>0||A[x-1][y-1]==-1)){
		if(x!=n&&A[x][y-1]>0){
			A[x][y-1]--;
			if(A[x][y-1]==0) cnt++;
		}
		if(x!=0&&A[x-1][y-1]>0){
			A[x-1][y-1]--;
			if(A[x-1][y-1]==0) cnt++;
		}
		ben[x][y][x][y-1]=ben[x][y-1][x][y]=1;
		if(dfs(x,y-1,lx,ly))return true;;
		ben[x][y][x][y-1]=ben[x][y-1][x][y]=0;
		if(x!=n&&A[x][y-1]>=0){
			if(A[x][y-1]==0) cnt--;
			A[x][y-1]++;
		}
		if(x!=0&&A[x-1][y-1]>=0){
			if(A[x-1][y-1]==0) cnt--;
			A[x-1][y-1]++;
		}
	}
	p--;P[x][y]=0;
	return false;
}

int main(){
	freopen("loopy.in","r",stdin);
	freopen("loopy.out","w",stdout);
	scanf("%d",&n);
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++){
			scanf("%d",&A[i][j]);
			if(A[i][j]>0) tt++;
		}
	dfs(1,0,1,0);
	printf("%d\n%d\n",cnt,ptt);
	for(int i=1;i<=ptt;i++) printf("%d %d\n",pt[i][0],pt[i][1]);
}
