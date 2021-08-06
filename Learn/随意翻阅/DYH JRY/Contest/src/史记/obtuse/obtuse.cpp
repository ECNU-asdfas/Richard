#include<iostream>
#include<cstdio>
#include<cstdlib>
#define rg register
#define rep(i,x,y) for(rg int i=(x);i<=(y);++i)
#define per(i,x,y) for(rg int i=(x);i>=(y);--i)
using namespace std;
namespace sjj118{
	
typedef long long LL;
const int N=1e5+10;
int n,a[N][3],sel[N*3];
inline LL sqr(LL x){return x*x;}
bool flag;
void brute(int p){
	if(p==n+1){
		flag=1;
	}
	rep(i,2,3*n+1)if(!sel[i]){
		sel[i]=1;a[p][0]=i;
		int j=i;
		rep(j,i+1,3*n+1)if(!sel[j]){
			sel[j]=1;a[p][1]=j;
			rep(k,j+1,3*n+1)if(!sel[k]){
				if(i+j>k&&sqr(i)+sqr(j)<sqr(k)){
					sel[k]=1;a[p][2]=k;
					brute(p+1);
					if(flag)return;
					sel[k]=0;
				}
			}
			sel[j]=0;
		}
		sel[i]=0;
		break;
	}
}
void search(int p){
	if(p==n+1){
		flag=1;
	}
	rep(i,2,3*n+1)if(!sel[i]){
		bool flaa1=0;
		rep(pp1,i+1,3*n+1)if(!sel[pp1])flaa1=1;
		if(!flaa1)return;
		sel[i]=1;a[p][0]=i;
		int j=i;
		rep(tt1,0,8){
			while(sel[j])j=rand()%(3*n+1-i)+i+1;
			flaa1=0;
			rep(pp1,j+1,3*n+1)if(!sel[pp1])flaa1=1;
			if(!flaa1)break;
			sel[j]=1;a[p][1]=j;
			rep(tt2,0,8){
				int k=j;
				while(sel[k])k=rand()%(3*n+1-j)+j+1;
				if(i+j>k&&sqr(i)+sqr(j)<sqr(k)){
					sel[k]=1;a[p][2]=k;
					search(p+1);
					if(flag)return;
					sel[k]=0;
				}
			}
			sel[j]=0;
		}
		sel[i]=0;
		break;
	}
}
int main(){
	freopen("obtuse.in","r",stdin);freopen("obtuse.out","w",stdout);
	srand(20000107);
	scanf("%d",&n);
	if(n<=5){
		brute(1);
		rep(i,1,n)printf("%d %d %d\n",a[i][0],a[i][1],a[i][2]);
	}else{
		search(1);
		rep(i,1,n)printf("%d %d %d\n",a[i][0],a[i][1],a[i][2]);
	}
	return 0;
}
}
int main(){
	return sjj118::main();
}
