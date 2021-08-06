#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int MaxN = 131072;
const int MaxLogN = 19;


int N;
char Str[MaxN];
int SA[MaxN], Rank[MaxN], Height[MaxN];
int Cur[MaxN][2];
int E[MaxN], Next[MaxN], Node[MaxN];

bool Cmp(const int &A, const int &B)
{
	return Str[A] < Str[B];
}

void SAContruction(char *Str)
{
	N = strlen(Str) + 1;
	for (int i = 0; i < N; i ++)
		SA[i] = i;
	sort(SA, SA + N, Cmp);
	Rank[SA[0]] = 0;
	for (int i = 1; i < N; i ++)
		Rank[SA[i]] = (Str[SA[i]] > Str[SA[i - 1]]) ? i : Rank[SA[i - 1]];
	
	for (int L = 1; ; L <<= 1)
	{
		for (int i = 0; i < N; i ++)
		{
			Cur[i][0] = Rank[i];
			Cur[i][1] = (i + L < N) ? Rank[i + L] : 0;
		}
		memset(Node, -1, sizeof(Node));
		for (int i = 0; i < N; i ++)
		{
			E[i] = i;
			Next[i] = Node[Cur[i][1]];
			Node[Cur[i][1]] = i;
		}
		int n = 0;
		for (int i = N; i >= 0; i --)
			for (int t = Node[i]; t != -1; t = Next[t])
				SA[n ++] = E[t];
		memset(Node, -1, sizeof(Node));
		for (int i = 0; i < N; i ++)
		{
			E[i] = SA[i];
			Next[i] = Node[Cur[SA[i]][0]];
			Node[Cur[SA[i]][0]] = i;
		}
		n = 0;
		for (int i = 0; i <= N; i ++)
			for (int t = Node[i]; t != -1; t = Next[t])
				SA[n ++] = E[t];
		Rank[SA[0]] = 0;
		int Indep = 1;
		for (int i = 1; i < N; i ++)
			if (Cur[SA[i]][0] == Cur[SA[i - 1]][0] && Cur[SA[i]][1] == Cur[SA[i - 1]][1])
			{
				Rank[SA[i]] = Rank[SA[i - 1]];
				Indep = 0;
			}
			else
				Rank[SA[i]] = i;
		if (Indep)
			break;
	}
	int H = 0;
	for (int i = 0; i < N; i ++)
		if (Rank[i] >= 1)
		{
			if (H > 0)
				H --;
			int j = SA[Rank[i] - 1];
			while (i + H < N && j + H < N && Str[i + H] == Str[j + H])
				H ++;
			Height[Rank[i]] = H;
		}
		else
			H = Height[Rank[i]] = 0;
	N --;
}

int Log2[MaxN];
int F[MaxLogN][MaxN];

void RMQPreprocess()
{
	Log2[1] = 0;
	for (int i = 2; i <= N; i ++)
		Log2[i] = Log2[i - 1] + (i & (i - 1) == 0);
	for (int i = 1; i <= N; i ++)
		F[0][i] = Height[i];
	for (int i = 1; i <= Log2[N]; i ++)
		for (int j = 1; j < N - (1 << i); j ++)
			F[i][j] = min(F[i - 1][j] + F[i - 1][j + (1 << (i - 1))]);
}

int RMQ(int i, int j)
{
	int k = Log2[j - i + 1];
	return min(F[k][i], F[k][j - (1 << k) + 1]);
}

int main()
{
	scanf("%s", &Str);
	SAConstruction(Str);
	RMQPreprocess();
	
	return 0;
}
