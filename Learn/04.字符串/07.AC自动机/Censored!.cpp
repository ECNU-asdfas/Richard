#include <cstdio>
#include <cstring>

const int Base = 1000000000;

struct TBigInt
{
	int Data[12];
	int Len;
	
	TBigInt ()
	{
		Len = 0;
		memset(Data, 0, sizeof(Data));
	}
	
	void Output()
	{
		if (Len == 0)
		{
			printf("0");
			return;
		}
		printf("%d", Data[Len - 1]);
		for (int i = Len - 2; i >= 0; i --)
			printf("%09d", Data[i]);
	}
};

void Add(TBigInt &A, const TBigInt &B)
{
	for (int i = 0; i < B.Len; i ++)
		A.Data[i] += B.Data[i];
	if (B.Len > A.Len)
		A.Len = B.Len;
	for (int i = 0; i < A.Len; i ++)
		if (A.Data[i] >= Base)
		{
			A.Data[i] -= Base;
			A.Data[i + 1] ++;
		}
	if (A.Data[A.Len] != 0)
		A.Len ++;
}

const int MaxC = 50 + 1;
const int MaxLen = 50 + 1;
const int MaxStrLen = 10 + 1;
const int MaxWords = 10 + 1;
const int MaxDFASize = MaxStrLen * MaxWords;

int C, M, P;
int Trans[255];
char Buf[100];
int Next[MaxDFASize][MaxC], Fail[MaxDFASize], Invaild[MaxDFASize];
int DFASize;

void InsertString(char *S)
{
	int Ptr = 0;
	for (int i = 0; S[i]; i ++)
	{
		if (Next[Ptr][Trans[S[i] + 128]] == -1)
			Next[Ptr][Trans[S[i] + 128]] = DFASize ++;
		Ptr = Next[Ptr][Trans[S[i] + 128]];
	}
	Invaild[Ptr] = 1;
}

int Q[MaxDFASize];

void BuildDFA()
{
	int Tail = 0;
	for (int j = 0; j < C; j ++)
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
		for (int j = 0; j < C; j ++)
			if (Next[i][j] != -1)
			{
				int k = Fail[i];
				while (k != 0 && Next[k][j] == -1)
					k = Fail[k];
				k = Next[k][j]; // ÇÐ¼Ç 
				Q[Tail] = Next[i][j];
				Invaild[Next[i][j]] |= Invaild[k]; // For example, 0 is invaild, 10 is also invaild
				Fail[Q[Tail ++]] = k;
			}
	}
}

TBigInt DP[MaxLen][MaxDFASize];

int main()
{
	scanf("%d%d%d", &C, &M, &P);
	scanf("%s", &Buf);
	for (int i = 0; i < C; i ++)
		Trans[Buf[i] + 128] = i;
	
	memset(Next, -1, sizeof(Next));
	
	DFASize = 1;
	for (int i = 0; i < P; i ++)
	{
		scanf("%s", &Buf);
		InsertString(Buf);
	}
	
	BuildDFA();
	
	memset(DP, 0, sizeof(DP));
	DP[0][0].Len = 1;
	DP[0][0].Data[0] = 1;
	for (int i = 0; i < M; i ++)
		for (int j = 0; j < DFASize; j ++)
			for (int k = 0; k < C; k ++)
			{
				int Now = j;
				while (Now != 0 && Next[Now][k] == -1)
					Now = Fail[Now];
				Now = Next[Now][k];
				if (! Invaild[Now])
					Add(DP[i + 1][Now], DP[i][j]);
			}
	
	TBigInt Ans;
	for (int i = 0; i < DFASize; i ++)
		Add(Ans, DP[M][i]);
	Ans.Output();
	printf("\n");
	return 0;
}
