#include <cstdio>
#include <cstdlib>
#include <ctime>

int main()
{
	freopen("infstring.in","w",stdout);srand(time(0));
	int n=rand()%1000+1,q=rand()%1+100000;
	printf("%d %d\n",n,q);
	for (int i=1;i<=n;i++)
		putchar('a'+rand()%26);
	putchar('\n');
	for (int i=1;i<=q;i++)
		printf("%d\n",i);
}
