#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <string>
#define N 300010

using namespace std;

typedef long long ll;

int n,m;
char A[N];
ll Ans[N],nAns;

inline void reaD(int &x){
	char Ch=getchar();x=0;
	for(;Ch>'9'||Ch<'0';Ch=getchar());
	for(;Ch>='0'&&Ch<='9';x=x*10+Ch-'0',Ch=getchar());
}

inline void reaD(char *x){
	char Ch=getchar();int len=0;
	for(;Ch>'z'||Ch<'a';Ch=getchar());
	for(;Ch>='a'&&Ch<='z';x[++len]=Ch,Ch=getchar());
}

struct Asking{
	int ct,g;
}B[N];

inline bool cmp(const Asking &a,const Asking &b){return a.ct<b.ct;}

int w[30],wt;

inline void Pt(ll x){
	if(!x){putchar(48);putchar('\n');return;}
	while(x)w[++wt]=x%10,x/=10;
	for(;wt;wt--)putchar(w[wt]+48);putchar('\n');
}

struct SAM_{
	int fail[N],next[N][26],stp[N],p,cnt;
	SAM_(){cnt=1;p=1;}
	void add(int x){
		int np=++cnt;stp[np]=stp[p]+1;
		while(p&&!next[p][x])
			next[p][x]=np,p=fail[p];
		if(!p)fail[np]=1;
		else{
			int q=next[p][x];
			if(stp[p]+1==stp[q]) fail[np]=q;
			else{
				int nq=++cnt;stp[nq]=stp[p]+1;
				memcpy(next[nq],next[q],sizeof(next[q]));
				fail[nq]=fail[q];
				fail[q]=fail[np]=nq;
				while(next[p][x]==q) next[p][x]=nq,p=fail[p];
			}
		}
		nAns+=stp[np]-stp[fail[np]];
		p=np;
	}
}SAM;

int main(){
	freopen("infstring.in","r",stdin);
	freopen("infstring1.out","w",stdout);
	reaD(n);reaD(m);reaD(A);
	for(int i=1;i<=m;i++)reaD(B[i].ct),B[i].g=i;
	sort(B+1,B+1+m,cmp);
	int p=1,j=1;
	for(int i=1;p<=m;i++,j++){
		if(i>n)i=1;
		SAM.add(A[i]-'a');
		while(j==B[p].ct&&p<=m)Ans[B[p++].g]=nAns;
	}
	for(int i=1;i<=m;i++) Pt(Ans[i]);
	return 0;
}
