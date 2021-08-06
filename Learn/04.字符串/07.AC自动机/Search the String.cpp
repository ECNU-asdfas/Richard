#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

const int MaxLen = 100000 + 10;
const int MaxQ = 100000 + 10;
const int MaxSize = 600000 + 10;
const int MaxC = 26 + 1;

int N;
char S[MaxLen];
int TrieNodes;
int Next[MaxSize][MaxC], Fail[MaxSize], Len[MaxSize];
vector <int> Link[MaxSize], LinkN[MaxSize];
int Ans[MaxSize], AnsN[MaxSize], LastCmp[MaxSize];
int QAns[MaxQ];

void InsertString(char *Str, int QNum, int Type)
{
	int Cur = 0;
	for (int i = 0; Str[i]; i ++)
	{
		if (Next[Cur][Str[i] - 'a'] == -1)
			Next[Cur][Str[i] - 'a'] = TrieNodes ++;
		Cur = Next[Cur][Str[i] - 'a'];
	}
	if (Type == 0)
		Link[Cur].push_back(QNum);
	else
		LinkN[Cur].push_back(QNum);
	Len[Cur] = strlen(Str);
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

char Buf[10];

void Work()
{
	TrieNodes = 1; // 0 is root
	memset(Next, -1, sizeof(Next));
	scanf("%d", &N);
	for (int i = 0; i < N; i ++)
	{
		int Type;
		scanf("%d%s", &Type, &Buf);
		InsertString(Buf, i, Type);
	}
	Build_AC_DFA();
	
	memset(LastCmp, -1, sizeof(LastCmp));
	memset(Ans, 0, sizeof(Ans));
	memset(AnsN, 0, sizeof(AnsN));
	int Ptr = 0;
	for (int i = 0; S[i]; i ++)
	{
		while (Next[Ptr][S[i] - 'a'] == -1)
			Ptr = Fail[Ptr];
		Ptr = Next[Ptr][S[i] - 'a'];
		int t = Ptr;
		while (t)
		{
			Ans[t] ++;
			if (i - LastCmp[t] >= Len[t])
			{
				AnsN[t] ++;
				LastCmp[t] = i;
			}
			t = Fail[t];
		}
	}
	
	for (int i = 0; i < TrieNodes; i ++)
	{
		for (int j = 0; j < Link[i].size(); j ++)
			QAns[Link[i][j]] = Ans[i];
		for (int j = 0; j < LinkN[i].size(); j ++)
			QAns[LinkN[i][j]] = AnsN[i];
	}
	
	for (int i = 0; i < N; i ++)
		printf("%d\n", QAns[i]);
	
	for (int i = 0; i <= TrieNodes; i ++)
	{
		Link[i].clear();
		LinkN[i].clear();
	}
}

int main()
{
	int Cases = 0;
	while (scanf("%s", &S) != EOF)
	{
		printf("Case %d\n", ++ Cases);
		Work();
		printf("\n");
	}
	return 0;
}
