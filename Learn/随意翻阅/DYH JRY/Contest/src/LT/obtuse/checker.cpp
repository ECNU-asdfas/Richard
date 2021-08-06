#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
using namespace std;


struct Node
{
	int l,r;
	int M;
}T[1000001];
void Build(int place,int l,int r)
{
	T[place].l=l,T[place].r=r;
	if(r!=1)T[place].M=r;
	else T[place].M=-1;
	if(l^r)
		Build(place<<1,l,l+r>>1),Build(place<<1|1,(l+r>>1)+1,r);
}
int Max(int&a,int b){return a<b?a=b:a;}
int Query(int place,int l,int r)
{
	if(T[place].l>=l&&T[place].r<=r)return T[place].M;
	int mid=T[place<<1].r,M=-1;
	if(mid>=l)Max(M,Query(place<<1,l,r));
	if(mid<r)Max(M,Query(place<<1|1,l,r));
	return M;
}
void Modify(int place,int l)
{
	if(T[place].l==T[place].r){T[place].M=-1;return;}
	int mid=T[place<<1].r;
	if(mid>=l)Modify(place<<1,l);
	else Modify(place<<1|1,l);
	T[place].M=-1;
	Max(T[place].M,T[place<<1].M);
	Max(T[place].M,T[place<<1|1].M);
}
#define sqr(x) ((x)*1ll*(x))
bool Solve(int n)
{
	Build(1,1,n);
	freopen("checker.out","w",stdout);
	while(T[1].M!=-1)
	{
		int C=Query(1,1,n);
		Modify(1,C);
		int B=Query(1,1,n);
		Modify(1,B);
		int T=(int)((1e-6)+sqrt(sqr(C)-sqr(B)));
		if(sqr(T)+sqr(B)!=sqr(C))T++;
		int A=Query(1,1,T-1);
		if(A==-1)
			{freopen("Con","w",stdout);
	return false;}
		Modify(1,A);
		printf("%d %d %d\n",A,B,C);
	}
	freopen("Con","w",stdout);
	return true;
}


int main()
{

	int i=1;
	while(i<=10000)
	{
		
		printf("%d :",i);
		bool t=Solve(3*i+1);
		if(!t)
			printf("WA"),system("pause");
		else printf("OK");
		puts("");
		i++;
	}
	return 0;
}
