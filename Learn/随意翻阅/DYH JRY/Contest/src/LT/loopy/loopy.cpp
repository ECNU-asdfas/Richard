#include<cstring>
#include<vector>
#include<cstdio>
#include<cstdlib>
using namespace std;



int A[101][101];
int B[101][101];

#define x first
#define y second
vector<pair<int,int> >Rot,Ans;
int T=-1;
int n;


int Com()
{
	int OK=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			B[i][j]=0;	
	for(int i=0;i<Rot.size()-1;i++)
	{
		if(Rot[i].x==Rot[i+1].x)
			B[Rot[i].x][Rot[i].y]++,
			B[Rot[i].x+1][Rot[i].y]++;		
		if(Rot[i].y==Rot[i+1].y)
			B[Rot[i].x][Rot[i].y+1]++,
			B[Rot[i].x][Rot[i].y]++;		
	}
	for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++)
	if(A[i][j]!=-1&&A[i][j]==B[i][j])OK++;
	if(T<OK)
		T=OK,Ans=Rot;
}
bool v[31][31];
void Find(int x,int y,int f)
{
	v[x][y]=1;
	if(f==1&&x==y==0)return;
	Find()
}

int main()
{
	scanf("%d",&n);
	int o=0;
	for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++)
	{
		scanf("%d",A[i]+j);
		if(A[i][j]!=-1)o++;
	}
	while(o>T*4)
		memset(v,0,sizeof(v)),Rot.clear(),Find(0,0,0);
	return 0;
}
