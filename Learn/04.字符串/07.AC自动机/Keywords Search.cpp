// 需要动态开内存

#include <cstdio>
#include <cstring>

const int MaxC = 26;
const int MaxLen = 1000000 + 10;
const int MaxDFASize = 600000;

struct TTrieNode
{
	TTrieNode *Fail;
	TTrieNode *Next[MaxC];
	int Count;
	TTrieNode ()
	{
		Fail = 0;
		memset(Next, 0, sizeof(Next));
		Count = 0;
	}
};

int P;
char Buf[100], Str[MaxLen];
TTrieNode *Root;

void InsertString(char *S)
{
	TTrieNode *Ptr = Root;
	for (int i = 0; S[i]; i ++)
	{
		if (Ptr -> Next[S[i] - 'a'] == 0)
			Ptr -> Next[S[i] - 'a'] = new TTrieNode();
		Ptr = Ptr -> Next[S[i] - 'a'];
	}
	Ptr -> Count ++;
}

TTrieNode *Q[MaxDFASize];

void BuildDFA()
{
	int Tail = 0;
	Root -> Fail = Root;
	for (int j = 0; j < MaxC; j ++)
		if (Root -> Next[j] == 0)
			Root -> Next[j] = Root;
		else
		{
			Q[Tail] = Root -> Next[j];
			Q[Tail ++] -> Fail = Root;
		}
	
	for (int Cur = 0; Cur < Tail; Cur ++)
	{
		TTrieNode *i = Q[Cur];
		for (int j = 0; j < MaxC; j ++)
			if (i -> Next[j] != 0)
			{
				TTrieNode *k = i -> Fail;
				while (k -> Next[j] == 0)
					k = k -> Fail;
				k = k -> Next[j];
				Q[Tail] = i -> Next[j];
				//Q[Tail] -> Count += k -> Count;
				Q[Tail ++] -> Fail = k;
			}
	}
}

void Work()
{
	scanf("%d", &P);
	Root = new TTrieNode();
	for (int i = 0; i < P; i ++)
	{
		scanf("%s", &Buf);
		InsertString(Buf);
	}
	BuildDFA();
	scanf("%s", &Str);
	
	TTrieNode *Cur = Root;
	int Ans = 0;
	for (int i = 0; Str[i]; i ++)
	{
		int k = Str[i] - 'a';
		while (Cur -> Next[k] == 0)
			Cur = Cur -> Fail;
		Cur = Cur -> Next[k];
		TTrieNode *Tmp = Cur;
		while (Tmp -> Count != -1)
		{
			Ans += Tmp -> Count;
			Tmp -> Count = -1;
			Tmp = Tmp -> Fail;
		}
	}
	printf("%d\n", Ans);
}

int main()
{
	int Cases;
	scanf("%d", &Cases);
	while (Cases --)
		Work();
	return 0;
}
