#include <cstdio>
#include <cstring>
#include <cstdlib>

const int MaxN = 50000 * 2 + 10;
const int MaxQ = 75000 * 2 + 10;

int N, nQ;
int E[MaxN], Cost[MaxN], NextE[MaxN], NodeE[MaxN], Es;
int Q[MaxQ], QID[MaxQ], NextQ[MaxQ], NodeQ[MaxQ], Qs;
int QA[MaxN], QB[MaxN], Ans[MaxN];

int P[MaxN], Dist[MaxN], Used[MaxN], Stack[MaxN], StackSize, Cur[MaxN];
int Fa[MaxN];

int GetRoot(int i)
{
	int Root = i;
	while (Fa[Root] != Root)
		Root = Fa[Root];
	while (Fa[i] != i)
	{
		int t = Fa[i];
		Fa[i] = Root;
		i = t;
	}
	return Root;
}

void Merge(int i, int j) // i -> j
{
	Fa[i] = GetRoot(j);
}

void LCA(int Root)
{
	Fa[Root] = Root;
	Dist[Root] = 0;
	P[Root] = -100;
	StackSize = 0;
	Stack[++ StackSize] = Root;
	Cur[StackSize] = NodeE[Root];
	while (StackSize)
	{
		int i = Stack[StackSize];
		int j = Cur[StackSize];
		if (j != -1)
		{
			if (E[j] == P[i])
			{
				Cur[StackSize] = NextE[j];
				continue;
			}
			Dist[E[j]] = Dist[i] + Cost[j];
			P[E[j]] = i;
			Fa[E[j]] = E[j];
			Stack[++ StackSize] = E[j];
			Cur[StackSize] = NodeE[E[j]];
			Cur[StackSize - 1] = NextE[j];
		}
		else
		{
			Used[i] = 1;
			for (int k = NodeQ[i]; k != -1; k = NextQ[k])
				if (Used[Q[k]])
					Ans[QID[k]] = GetRoot(Q[k]);
			if (i != Root)
				Merge(i, P[i]);
			StackSize --;
		}
	}
}

int main()
{
	scanf("%d", &N);
	int A, B, C;
	Es = Qs = 0;
	memset(NodeE, -1, sizeof(NodeE));
	memset(NodeQ, -1, sizeof(NodeQ));
	for (int i = 0; i < N - 1; i ++)
	{
		scanf("%d%d%d", &A, &B, &C);

		E[Es] = B;
		Cost[Es] = C;
		NextE[Es] = NodeE[A];
		NodeE[A] = Es ++;
		
		E[Es] = A;
		Cost[Es] = C;
		NextE[Es] = NodeE[B];
		NodeE[B] = Es ++;
	}
	
	scanf("%d", &nQ);
	for (int i = 0; i < nQ; i ++)
	{
		scanf("%d%d", &A, &B);

		Q[Qs] = B;
		QID[Qs] = i;
		NextQ[Qs] = NodeQ[A];
		NodeQ[A] = Qs ++;

		Q[Qs] = A;
		QID[Qs] = i;
		NextQ[Qs] = NodeQ[B];
		NodeQ[B] = Qs ++;
		
		QA[i] = A;
		QB[i] = B;
	}
	
	LCA(0);
	for (int i = 0; i < nQ; i ++)
		printf("%d\n", Dist[QA[i]] + Dist[QB[i]] - Dist[Ans[i]] * 2);
	return 0;
}
