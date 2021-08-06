#include <cstdio>
#include <cstring>

const int MaxN = 10 + 1;
const int MaxL = 1000 + 10;
const int MaxDFASize = 80000 + 10;
const int Inf = 168430090;

int N, M;
int Trie[MaxDFASize][2], Fail[MaxDFASize], Illegal[MaxDFASize], TrieSize;
char Str[MaxN][MaxL];
char Buf[MaxDFASize];
int EndPoint[MaxN], n;

int Insert(char *Str, int _Illegal)
{
	int i = 0;
	for (int j = 0; Str[j]; j ++)
	{
		if (Trie[i][Str[j] - '0'] == -1)
			Trie[i][Str[j] - '0'] = TrieSize ++;
		i = Trie[i][Str[j] - '0'];
	}
	if (_Illegal)
		Illegal[i] = 1;
	return i;
}

int Q[MaxDFASize];

void DFAGen()
{
	int Tail = 0;
	Fail[0] = 0;
	for (int j = 0; j < 2; j ++)
		if (Trie[0][j] == -1)
			Trie[0][j] = 0;
		else
		{
			Q[Tail ++] = Trie[0][j];
			Fail[Trie[0][j]] = 0;
		}
	for (int Cur = 0; Cur < Tail; Cur ++)
	{
		int i = Q[Cur];
		for (int j = 0; j < 2; j ++)
			if (Trie[i][j] != -1)
			{
				int k = Fail[i];
				while (Trie[k][j] == -1)
					k = Fail[k];
				k = Trie[k][j];
				Q[Tail ++] = Trie[i][j];
				Fail[Trie[i][j]] = k;
				Illegal[Trie[i][j]] |= Illegal[k];
			}
	}
}

int Dist[MaxN][MaxDFASize];

void BFS(int Start, int Serial)
{
	memset(Dist[Serial], 10, sizeof(Dist[Serial]));
	Dist[Serial][Start] = 0;
	
	int Tail = 0;
	Q[Tail ++] = Start;
	for (int Cur = 0; Cur < Tail; Cur ++)
	{
		int i = Q[Cur];
		for (int j = 0; j < 2; j ++)
		{
			int k = i;
			while (Trie[k][j] == -1)
				k = Fail[k];
			k = Trie[k][j];
			if ((! Illegal[k]) && Dist[Serial][k] == Inf)
			{
				Dist[Serial][k] = Dist[Serial][i] + 1;
				Q[Tail ++] = k;
			}
		}
	}
}

int Pi[MaxL];

int KMP(char *A, char *B)
{
	Pi[0] = -1;
	int j = -1;
	for (int i = 1; A[i]; i ++)
	{
		while (j >= 0 && B[i] != B[j + 1])
			j = Pi[j];
		if (B[i] == B[j + 1])
			j ++;
		Pi[i] = j;
	}
	j = -1;
	for (int i = 0; A[i]; i ++)
	{
		while (j >= 0 && A[i] != B[j + 1])
			j = Pi[j];
		if (! B[j + 1])
			return 1;
		if (A[i] == B[j + 1])
			j ++;
	}
	return 0;
}

int DP[1 << MaxN][MaxN];

void Work()
{
	TrieSize = 1;
	memset(Trie, -1, sizeof(Trie));
	memset(Fail, -1, sizeof(Fail));
	memset(Illegal, 0, sizeof(Illegal));
	
	for (int i = 0; i < N; i ++)
		scanf("%s", &Str[i]);
	for (int i = 0; i < M; i ++)
	{
		scanf("%s", &Buf);
		Insert(Buf, 1);
	}
	n = 0;
	for (int i = 0; i < N; i ++)
	{
		int Available = 1;
		for (int j = 0; j < N; j ++)
			if (i != j && KMP(Str[j], Str[i]))
			{
				Available = 0;
				break;
			}
		if (Available)
			EndPoint[n ++] = Insert(Str[i], 0);
	}
	N = n;
	DFAGen();
	
	for (int i = 0; i < N; i ++)
		BFS(EndPoint[i], i);
	BFS(0, N);
	
	memset(DP, 10, sizeof(DP));
	for (int i = 0; i < N; i ++)
		DP[1 << i][i] = Dist[N][EndPoint[i]];
	for (int Set = 0; Set < (1 << N); Set ++)
		for (int i = 0; i < N; i ++)
			if (DP[Set][i] != Inf)
				for (int j = 0; j < N; j ++)
					if ((Set & (1 << j)) == 0)
						if (DP[Set | (1 << j)][j] > DP[Set][i] + Dist[i][EndPoint[j]])
							DP[Set | (1 << j)][j] = DP[Set][i] + Dist[i][EndPoint[j]];
	
	int Ans = 100000000;
	for (int i = 0; i < N; i ++)
		if (DP[(1 << N) - 1][i] < Ans)
			Ans = DP[(1 << N) - 1][i];
	printf("%d\n", Ans);
}

int main()
{
	while (1)
	{
		scanf("%d%d", &N, &M);
		if (N + M == 0)
			break;
		Work();
	}
	return 0;
}
