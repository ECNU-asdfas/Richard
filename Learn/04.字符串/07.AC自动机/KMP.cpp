#include <cstdio>
#include <cstring>

const int MaxN = 1000000 + 10;

int WLen;
char W[MaxN], T[MaxN];
int Pi[MaxN];

int main()
{
	int Cases;
	scanf("%d", &Cases);
	while (Cases --)
	{
		scanf("%s%s", &W, &T);
		Pi[0] = 0;
		int j = 0;
		int WLen = strlen(W);
		// Pi[i] 表示  [i - Pi[i] + 1, i] == [0, Pi[i] - 1]
		// 自我匹配 
		for (int i = 1; W[i]; i ++)
		{
			/*
			a b a b a c b
			0 0 1 2 3 ?
			*/
			while (j != 0 && W[i] != W[j])
				j = Pi[j - 1];
			if (W[i] == W[j])
				j ++;
			Pi[i] = j;
		}
		j = 0;
		int Ans = 0;
		for (int i = 0; T[i]; i ++)
		{
			while (j != 0 && T[i] != W[j])
				j = Pi[j - 1];
			if (T[i] == W[j])
				j ++;
			if (j == WLen)
			{
				Ans ++;
				j = Pi[j - 1]; // 跳往上一个失配指针 
			}
		}
		printf("%d\n", Ans);
	}
	return 0;
}
