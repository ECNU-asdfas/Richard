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
	while(T[1].M!=-1)
	{
		int C=Query(1,1,n);
		Modify(1,C);
		int B=Query(1,1,n);
		Modify(1,B);
		int T=sqrt(sqr(C)-sqr(B));
		if(sqr(T)+sqr(B)!=sqr(C))T++;
		int A=Query(1,1,T-1);
		if(A==-1)
			return false;
		Modify(1,A);
	}
	return true;
}


int main()
{
	freopen("obtuse.in","r",stdin);
	freopen("obtuse.out","w",stdout);
	int n;
	scanf("%d",&n);
	if(n==1)
	{
		puts("2 3 4");
		return 0;
	}
	if(n==2)
	{
		puts("2 4 5");
		puts("3 6 7");
		return 0;
	}
	if(n==3)
	{
		puts("2 9 10");
		puts("3 6 7");
		puts("4 5 8");
		return 0;	
	}
	if(n==4)
	{
		puts("2 12 13");
		puts("3 9 10");
		puts("4 6 8");
		puts("5 7 11");
		return 0;
	}
	if(n==5)
	{
		puts("2 15 16");
		puts("3 12 13");
		puts("4 9 10");
		puts("5 6 8");
		puts("7 11 14");
		return 0;
	}
	puts("-1");
	return 0;
}
