#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;
int n,q;
char c;
inline void read(int&a)
{
	a=0;do c=getchar();while(c<'0'||c>'9');
	while(c<='9'&&c>='0')a=(a<<3)+(a<<1)+c-'0',c=getchar();
}
int ttt;
#define ll long long
struct Node
{
	ll lazy,sum;
	bool vis;
	int len,no;
	Node*ch[30],*last;
	Node(){no=ttt++;memset(ch,0,sizeof(ch));last=NULL;len=0;vis=false,lazy=sum=0;}
}*Root=new Node,*Last=Root;
ll S=0;
void Add(int c)
{
	Node *A=new Node,*tp;
	A->len=Last->len+1;
	for(tp=Last;tp&&!tp->ch[c];tp=tp->last)tp->ch[c]=A,A->sum+=tp->sum;
	if(!tp)
		A->last=Root,Last=A;
	else if(tp->ch[c]&&tp->ch[c]->len==tp->len+1)A->last=tp->ch[c],Last=A;
	else
	{
		Node *p=new Node,*q=tp->ch[c];
		*p=*q;
		q->last=A->last=p;
		p->len=tp->len+1;
		p->sum=0;
		for(tp;tp&&tp->ch[c]==q;tp=tp->last)tp->ch[c]=p,q->sum-=tp->sum,p->sum+=tp->sum;
		Last=A;
	}
	S+=Last->sum;
};
int A[300001];
ll Sum[1000001];


void out(ll a)
{
	if(a==0){putchar('0');return;}
	if(a<0){putchar('-');a=-a;}
	if(a>9)out(a/10);
	putchar('0'+a%10);
}
ll max(ll x,ll y){return x>y?x:y;}
int main()
{
	freopen("infstring.in","r",stdin);
	freopen("infstring.out","w",stdout);
	Root->sum=1;
	int n,q;
	read(n),read(q);
	for(int i=1;i<=n;i++)
	{
		do c=getchar();while(c<'a'||c>'z');
		Add(A[i]=(c-'a'));
		Sum[i]=S;
	}
	
//	printf("%d\n",S);
//	return 0;
	for(int i=n+1;i<=2*n;i++)
	{
		Add(A[i-n]);
		Sum[i]=S;
	}
	for(int i=2*n+1;i<=3*n;i++)
	{
		Add(A[i-2*n]);
		Sum[i]=S;
	}
	ll DS=S;
	for(int i=3*n+1;i<=4*n;i++)
	{
		Add(A[i-3*n]);
		Sum[i]=S;
	}
	DS=S-DS;
	for(int i=1;i<=q;i++)
	{
		int x;
		if(i==94)
			i++,i--;
		scanf("%d",&x);
		ll ans;
		if(x<=4*n)
			ans=Sum[x];
		else
		{
			ans=
				Sum[3*n+((x-3*n)%(n))];
			x-=3*n+((x-3*n)%(n));
			ans+=DS*(x/n);
		}
		if(ans<0)
			ans++,ans--;
		out(ans);
		puts("");
	}
	return 0;
}
