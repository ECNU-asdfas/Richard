#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<iostream>
#include<cstring>
using namespace std;


int main()
{

	srand(time(0));
	freopen("infstring.in","w",stdout);
	int n=100000,q=100000;
	printf("%d %d\n",n,q);
	while(n--)
	{
		printf("%c",'a'+rand()%26);
	}
	puts("");
	while(q--)
	{
		printf("%d\n",1+(rand()*1ll*rand()%(int)1e9));
	}

}
