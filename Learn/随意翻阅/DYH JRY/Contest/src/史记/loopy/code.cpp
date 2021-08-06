#include<bits/stdc++.h>
#define cls(a) memset(a,0,sizeof(a))
#define rg 
#define rep(i,x,y) for(rg int i=(x);i<=(y);++i)
#define per(i,x,y) for(rg int i=(x);i>=(y);--i)
using namespace std; 
const int N=30,V=2e7+1e5,M=1.1e8;
int n,a[N][N],dp[2][V],v,ans;
int issel(int p,int k){
	return (p>>k)&1;
}
int lft(int p){
	return (p<<1)&(v-1);
}
map<int,int> iid[N*N];
int tot_id,id_num[M];
int id(int x,int y){
	if(iid[x].count(y))return iid[x][y];
	iid[x][y]=++tot_id;
	id_num[tot_id]=y;
	return tot_id; 
}
struct Graph{
	int tot,to[M],head[M],next[M];
	void ins(int a,int b){to[++tot]=b;next[tot]=head[a];head[a]=tot;}
	bool sel[N][N];
	bool search(int x,int y){
		vis[x][y]=1;
		if(x>1&&!vis[x-1][y]&&sel[x-1][y])if(!search(x-1,y))return 0;
		if(x<n&&!vis[x+1][y]&&sel[x+1][y])if(!search(x+1,y))return 0;
		if(y>1&&!vis[x][y-1]&&sel[x][y-1])if(!search(x,y-1))return 0;
		if(y<n&&!vis[x][y+1]&&sel[x][y+1])if(!search(x,y+1))return 0;
		
		if(x>1&&y>1&&sel[x-1][y-1]&&!sel[x-1][y]&&!sel[x][y-1])return 0;
		if(x>1&&y<n&&sel[x-1][y+1]&&!sel[x-1][y]&&!sel[x][y+1])return 0;
		if(x<n&&y>1&&sel[x+1][y-1]&&!sel[x+1][y]&&!sel[x][y-1])return 0;
		if(x<n&&y<n&&sel[x+1][y+1]&&!sel[x+1][y]&&!sel[x][y+1])return 0;
		return 1;
	}
	bool vis[N][N];
	bool d0(int x,int y){
		vis[x][y]=1;
		bool flag=0;
		if(x==1)flag= 1;
		if(x==n)flag= 1;
		if(y==1)flag= 1;
		if(y==n)flag= 1;
		if(x>1&&!vis[x-1][y]&&!sel[x-1][y])if(d0(x-1,y))flag= 1;
		if(x<n&&!vis[x+1][y]&&!sel[x+1][y])if(d0(x+1,y))flag= 1;
		if(y>1&&!vis[x][y-1]&&!sel[x][y-1])if(d0(x,y-1))flag= 1;
		if(y<n&&!vis[x][y+1]&&!sel[x][y+1])if(d0(x,y+1))flag= 1;
		return flag;
	}
	bool check(){
		cls(vis);
		int cnt=0;
		rep(i,1,n)rep(j,1,n)if(!vis[i][j]&&sel[i][j]){
			if(cnt++)return 0;
			if(search(i,j)==0)return 0;
		}
		rep(i,1,n)rep(j,1,n)if(!vis[i][j]&&!sel[i][j]){
			if(!d0(i,j))return 0;
		}
		return 1;
	}
	int w[N][N][N][N];
	void travel(int x,int y,int px,int py,int sx,int sy){
		printf("%d %d\n",x,y);
		rep(i,0,n)rep(j,0,n)if(w[x][y][i][j])if(i!=px||j!=py){
			if(i==sx&&j==sy)return;
			travel(i,j,x,y,sx,sy);
			return;
		}
	}
	void output(){
		cls(w);
		int sx=0,sy=0;
		rep(i,1,n)rep(j,1,n){
			if(sel[i][j]!=sel[i][j+1])w[i-1][j][i][j]=w[i][j][i-1][j]=1,sx=i,sy=j;
			if(sel[i][j]!=sel[i][j-1])w[i-1][j-1][i][j-1]=w[i][j-1][i-1][j-1]=1,sx=i,sy=j-1;
			if(sel[i][j]!=sel[i+1][j])w[i][j-1][i][j]=w[i][j][i][j-1]=1,sx=i,sy=j;
			if(sel[i][j]!=sel[i-1][j])w[i-1][j-1][i-1][j]=w[i-1][j][i-1][j-1]=1,sx=i-1,sy=j-1;
		}
		travel(sx,sy,-1,-1,sx,sy);
	}
	void dfs(int k,int x,int y){
		if(k==1){
			assert(x==0);
			if(check()){
				++ans;
				rep(i,1,n){
					rep(j,1,n){
						printf("%d ",sel[i][j]);
					}
					puts("");
				}
				puts("");
				output();
			}
			return;
		}
		int nx=x,ny=y-1;
		if(ny==0)ny=n,--nx;
		for(int p=head[k];p;p=next[p]){
			sel[x][y]=id_num[k]&1;
			dfs(to[p],nx,ny);
		}
	}
}G;
int main(){
	freopen("loopy.in","r",stdin);freopen("loopy.out","w",stdout);
	scanf("%d",&n);v=1<<(n<<1);
	rep(i,1,n)rep(j,1,n)scanf("%d",&a[i][j]);
	rep(i,1,n)a[n+1][i]=-1;
	int x=0;
	dp[0][0]=1;
	rep(i,1,n+1){
		rep(j,1,n){
			x^=1;cls(dp[x]);
			rep(p,0,v-1)if(dp[x^1][p]){
				bool can[2];can[0]=can[1]=1;
				if(i==n+1)can[1]=0;
				if(j>1&&a[i][j-1]!=-1){
					int cnt=0;
					if(j>2){
						if(issel(p,0)!=issel(p,1))++cnt;
					}else{
						if(issel(p,0))++cnt;
					}
					if(i>1){
						if(issel(p,0)!=issel(p,n))++cnt;
					}else{
						if(issel(p,0))++cnt;
					}
					if(cnt>a[i][j-1])can[0]=can[1]=0;
					if(cnt==a[i][j-1])can[!issel(p,0)]=0;
					if(cnt+2<a[i][j-1])can[0]=can[1]=0;
				}
				if(i>1&&a[i-1][j]!=-1){
					int cnt=0;
					if(i>2){
						if(issel(p,n-1)!=issel(p,2*n-1))++cnt;
					}else{
						if(issel(p,n-1))++cnt;
					}
					if(j>1){
						if(issel(p,n-1)!=issel(p,n))++cnt;
					}else{
						if(issel(p,n-1))++cnt;
					}
					if(j<n){
						if(issel(p,n-1)!=issel(p,n-2))++cnt;
					}else{
						if(issel(p,n-1))++cnt;
					}
					if(cnt>a[i-1][j])can[0]=can[1]=0;
					if(cnt==a[i-1][j])can[!issel(p,n-1)]=0;
					if(cnt+1==a[i-1][j])can[issel(p,n-1)]=0;
					if(cnt+1<a[i-1][j])can[0]=can[1]=0;
				}
				rep(k,0,1)if(can[k]){
					dp[x][lft(p)|k]+=dp[x^1][p];
					G.ins(id((i-1)*n+j,lft(p)|k),id((i-1)*n+j-1,p));
				}
				//if(!can[0]&&!can[1])G.del(id((i-1)*n+j,p);
			}
		}
	}	
	cerr<<"169";
//	rep(i,0,v-1)if(dp[x][i])ans+=dp[x][i];
	rep(i,0,v-1)if(dp[x][i])G.dfs(id(n*(n+1),i),n+1,n);
//	printf("%d",ans);
	return 0;
}
