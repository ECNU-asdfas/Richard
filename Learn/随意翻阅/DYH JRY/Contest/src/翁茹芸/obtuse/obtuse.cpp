#include<cstdio>
#include<algorithm>
#include<cstdlib>
#include<ctime>
int n;
int answer[100010][3];
bool check(int x){
	int a=answer[x][0];
	int b=answer[x][1];
	int c=answer[x][2];
	return(a+b>c&&a+c>b&&b+c>a)&&(1ll*a*a+1ll*b*b<1ll*c*c||1ll*a*a+1ll*c*c<1ll*b*b||1ll*b*b+1ll*c*c<1ll*a*a);
}
bool work(int i,int j){
	int p,q;
	for(p=0;p<2;++p){
		for(q=0;q<2;++q){
			std::swap(answer[j][p],answer[i][q]);
			if(check(j)&&check(i))
				return true;
			if((rand()%2)&&check(j))
				return false;
			std::swap(answer[j][p],answer[i][q]);
		}
	}
	
	return false;
}
int main(void){
	int i,j,k;
	int p,q;
	int x,y;	
	freopen("obtuse.in","r",stdin);
	freopen("obtuse.out","w",stdout);	
	scanf("%d",&n);srand(987654321);answer[0][0]=2;answer[0][1]=3;answer[0][2]=4;
	j=0;
	for(i=1;i<n;++i){
		answer[i][0]=3*i+2;answer[i][1]=3*i+3;answer[i][2]=3*i+4;
		if(check(i))
		continue;
		while(true)	{
			for(x=j,y=j;x>=0||y<i;--x,++y){
				if(x>=0&&work(i,x)){
					j=x;
					goto next;}
				if(y<i&&work(i,y)){
					j=y;
					goto next;
				}
			}
		}
next:;
	}	
	for(i=0;i<n;++i)
		printf("%d%d%d\n",answer[i][0],answer[i][1],answer[i][2]);return 0;
}
