#include <cstdio>
#include <cstdlib>
#include <ctime>

int main(){
	freopen("infstring.in","w",stdout);
	srand(time(0));
	int n=9234,m=100000;
	printf("%d %d\n",n,m);
	for(int i=1;i<=n;i++)putchar(rand()%26+'a');putchar('\n');
	for(int i=1;i<=m;i++)printf("%lld\n",1ll*rand()*rand()%100000+1);
	return 0;
}
