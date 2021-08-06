#include <cstdio>
#define N 300010

int n,cnt,V[N];
struct Ans_{
	int a,b,c;
}Ans[N];

int S(int x){
	if(x>n/3) return true;
	for(int i=1;i<=n;i++)if(!V[i])
		for(int j=i+1;j<=n;j++)if(!V[j])
			for(int k=j+1;k<i+j+1&&k<=n;k++)
				if(!V[k]&&(i+1)*(i+1)+(j+1)*(j+1)<(k+1)*(k+1)){
					Ans[++cnt]=(Ans_){i+1,j+1,k+1};
					V[i]=V[j]=V[k]=1;
					if(S(x+1))return true;
					V[i]=V[j]=V[k]=0;
					cnt--;
				}
	return false;
}

int main(){
	freopen("obtuse.in","r",stdin);
	freopen("obtuse.out","w",stdout);
	scanf("%d",&n);n*=3;
	S(1);
	for(int i=1;i<=cnt;i++) printf("%d %d %d\n",Ans[i].a,Ans[i].b,Ans[i].c);
	return 0;
}
