#include <cstdio>
#include <cstring>

const int MaxN = 50 + 10; 
const int MaxM = 100 + 10;
const int MaxWordLen = 12;
const int MaxSize = MaxM * MaxWordLen;
const int MaxC = 26;

int N, M;
int TrieNodes;
int Next[MaxSize][MaxC], Cost[MaxSize], Fail[MaxSize];
int Value[MaxM];
char Str[MaxM][MaxWordLen];
int DP[MaxN][MaxSize], Prev[MaxN][MaxSize], Char[MaxN][MaxSize];

void InsertString(char *Str, int _Cost)
{
	int Cur = 0;
	for (int i = 0; Str[i]; i ++)
	{
		if (Next[Cur][Str[i] - 'a'] == -1)
			Next[Cur][Str[i] - 'a'] = TrieNodes ++;
		Cur = Next[Cur][Str[i] - 'a'];
	}
	Cost[Cur] += _Cost;
}

int Q[MaxSize];

void Init()
{
	scanf("%d%d", &N, &M);
	TrieNodes = 1; // 0 is root
	memset(Next, -1, sizeof(Next));
	memset(Cost, 0, sizeof(Cost));
	for (int i = 0; i < M; i ++)
	{
		scanf("%s", &Str[i]);
		int Len = strlen(Str[i]);
		for (int j = 0; j < Len / 2; j ++)
		{
			char t = Str[i][j];
			Str[i][j] = Str[i][Len - 1 - j];
			Str[i][Len - 1 - j] = t;
		}
	}
	for (int i = 0; i < M; i ++)
	{
		scanf("%d", &Value[i]);
		InsertString(Str[i], Value[i]);
	}
}

void Build_AC_DFA()
{
	/*
		构建AC自动机
		1. 对于根节点，如果它的儿子是空，那么把它的这个儿子指向自己
		2. 根节点儿子的失败指针指向根
		3. 对于i，i的儿子的失败指针通过i的失败指针一直寻找，直到某个位置有所对应的儿子，或者到根为止 
	*/
	
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
				Cost[k] += Cost[Fail[k]];
				Q[Tail ++] = k;
			}
	}
}

int Qx[MaxN * MaxSize], Qy[MaxN * MaxSize];
int InQueue[MaxN][MaxSize];

int Compare(int i, int j, int Ch, int New) // Rev(DP[i][j] + Ch) < Rev(DP[i + 1][New])
{
	if (Ch != Char[i + 1][New])
		return Ch < Char[i + 1][New];
	New = Prev[i + 1][New];
	for (; i > 0; i --)
	{
		if (Char[i][j] != Char[i][New])
			return Char[i][j] < Char[i][New];
		New = Prev[i][New];
		j = Prev[i][j];
	}
	return 0;
}

void Work()
{
	int Tail = 1;
	Qx[0] = 0;
	Qy[0] = 0;
	memset(DP, -1, sizeof(DP));
	memset(InQueue, 0, sizeof(InQueue));
	DP[0][0] = 0;
	for (int Cur = 0; Cur < Tail; Cur ++)
	{
		int i = Qx[Cur];
		int j = Qy[Cur];
		if (i == N)
			continue;
		for (int k = 0; k < MaxC; k ++)
		{
			int New = j;
			while (Next[New][k] == -1)
				New = Fail[New];
			New = Next[New][k];
			if (DP[i + 1][New] == -1 || DP[i + 1][New] < DP[i][j] + Cost[New] || 
				(DP[i + 1][New] == DP[i][j] + Cost[New] && Compare(i, j, k, New)))
			{
				if (! InQueue[i + 1][New])
				{
					Qx[Tail] = i + 1;
					Qy[Tail ++] = New;
					InQueue[i + 1][New] = 1;
				}
				DP[i + 1][New] = DP[i][j] + Cost[New];
				Prev[i + 1][New] = j;
				Char[i + 1][New] = k;
			}
		}
	}
	
	int Ans = 0, Now = 0, Len = 0;
	for (int i = 1; i <= N; i ++)
		for (int j = 0; j < TrieNodes; j ++)
			if (DP[i][j] > Ans || (DP[i][j] == Ans && i == Len && Compare(i - 1, Prev[i][j], Char[i][j], Now)))
			{
				Ans = DP[i][j];
				Now = j;
				Len = i;
			}
	while (Len > 0)
	{
		printf("%c", Char[Len][Now] + 97);
		Now = Prev[Len --][Now];
	}
	printf("\n");
}

int main()
{
	int Cases;
	scanf("%d", &Cases);
	while (Cases --)
	{
		Init();
		Build_AC_DFA();
		Work();
	}
	return 0;
}
