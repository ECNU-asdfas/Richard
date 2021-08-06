#include <cstdio>
#include <cstring>

const int MaxN = 150 + 10;
const int MaxC = 26;
const int MaxLen = 70 + 10;
const int MaxSize = MaxN * MaxLen;
const int MaxStringLen = 1000000 + 10;

int N;
char S[MaxN][MaxLen];
int Next[MaxSize][26], Fail[MaxSize], Rep[MaxSize], Count[MaxSize];
int Ans[MaxN];
int TrieNodes;
char Str[MaxStringLen];
int E[MaxSize], NextE[MaxSize], Node[MaxSize], nE;

void InsertString(char *Str, int Num)
{
	int Cur = 0;
	for (int i = 0; Str[i]; i ++)
	{
		if (Next[Cur][Str[i] - 'a'] == -1)
			Next[Cur][Str[i] - 'a'] = TrieNodes ++;
		Cur = Next[Cur][Str[i] - 'a'];
	}
	Rep[Cur] = Num;
}

int Q[MaxSize];

void Build_AC_DFA()
{
	int Tail = 0;
	for (int j = 0; j < MaxC; j ++)
		if (Next[0][j] == -1)
			Next[0][j] = 0;
		else
		{
			Q[Tail] = Next[0][j];
			Fail[Q[Tail ++]] = 0;
		}

	for (int Cur = 0; Cur < Tail; Cur ++)
	{
		int i = Q[Cur];
		for (int j = 0; j < MaxC; j ++)
			if (Next[i][j] != -1)
			{
				int k = Next[i][j];
				int Failure = Fail[i];
				while (Next[Failure][j] == -1)
					Failure = Fail[Failure];
				Fail[k] = Next[Failure][j];
				Q[Tail ++] = k;
			}
	}
}

void InsertEdge(int A, int B)
{
	E[nE] = B;
	NextE[nE] = Node[A];
	Node[A] = nE ++;
}

void Build_Graph()
{
	memset(Node, -1, sizeof(Node));
	nE = 0;
	for (int i = 1; i < TrieNodes; i ++)
		InsertEdge(Fail[i], i);
}

void DFS(int i)
{
	for (int j = Node[i]; j != -1; j = NextE[j])
	{
		DFS(E[j]);
		Count[i] += Count[E[j]];
	}
}

void Work()
{
	TrieNodes = 1; // 0 is root
	memset(Next, -1, sizeof(Next));
	memset(Rep, -1, sizeof(Rep));
	for (int i = 0; i < N; i ++)
	{
		scanf("%s", &S[i]);
		InsertString(S[i], i);
	}
	Build_AC_DFA();
	Build_Graph();
	scanf("%s", &Str);
	int Cur = 0;
	memset(Count, 0, sizeof(Count));
	for (int i = 0; Str[i]; i ++)
	{
		while (Next[Cur][Str[i] - 'a'] == -1)
			Cur = Fail[Cur];
		Cur = Next[Cur][Str[i] - 'a'];
		Count[Cur] ++;
	}
	DFS(0);
	memset(Ans, 0, sizeof(Ans));
	for (int i = 0; i < TrieNodes; i ++)
		if (Rep[i] != -1)
			Ans[Rep[i]] = Count[i];
	int MaxAns = 0;
	for (int i = 0; i < N; i ++)
		if (Ans[i] > MaxAns)
			MaxAns = Ans[i];
	printf("%d\n", MaxAns);
	for (int i = 0; i < N; i ++)
		if (Ans[i] == MaxAns)
			printf("%s\n", S[i]);
}

int main()
{
	while (1)
	{
		scanf("%d", &N);
		if (N == 0)
			break;
		Work();
	}
	return 0;
}

/*
2
aba
bab
ababababac
6
beta
alpha
haha
delta
dede
tata
dedeltalphahahahototatalpha
0
*/