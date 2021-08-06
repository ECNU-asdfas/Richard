/*
Trieͼ�������̣�
��1������Trie������֤���ڵ�һ����|��|�����ӡ�
��2����α���Trie�������׺�ڵ㣬�ڵ��ǣ�û��|��|�����ӵĶ�����в��ߡ�
��׺�ڵ�ļ��㣺
��1�������ĺ�׺�ڵ���������
��2������Trie���ڶ���Ľڵ�ĺ�׺���Ҳ�Ǹ���㡣
��3������ڵ�ĺ�׺�ڵ㣬���丸�ڵ�ĺ�׺�ڵ�������Ӧ״̬ת�ƵĽڵ㣨��������AC�Զ����ĵ������̣���
�ڵ��ǣ�
��1��������б�ǡ�
��2�����׺�ڵ��б�ǡ�
���ߣ�
�����׺�ڵ���Ӧ��״̬ת�������ǰ�ڵ�Ŀհס�
*/

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MaxL = 1000 + 10;
const int MaxC = 4;
const int MaxDFASize = 1000 + 10;

int N;
char Buf[MaxL];
int T[100];

int Size;
int Trie[MaxDFASize][MaxC], Illegal[MaxDFASize];
int Suffix[MaxDFASize];

void Insert()
{
    scanf("%s", &Buf);
    int i = 0;
    for (int j = 0; Buf[j]; j ++)
    {
        if (Trie[i][T[Buf[j]]] == -1)
        {
            Trie[i][T[Buf[j]]] = Size;
            Size ++;
        }
        i = Trie[i][T[Buf[j]]];
        if (Illegal[i])
            break;
    }
    Illegal[i] = 1;
}

int Q[MaxDFASize], Tail;

void TrieGraphGen()
{
    Tail = 0;
    for (int i = 0; i < MaxC; i ++)
        if (Trie[0][i] == -1)
            Trie[0][i] = 0;
        else
        {
            Q[Tail] = Trie[0][i];
            Tail ++;
            Suffix[Trie[0][i]] = 0;
        }

    for (int j = 0; j < Tail; j ++)
    {
        int i = Q[j];
        Illegal[i] |= Illegal[Suffix[i]];
        if (Illegal[i])
            continue;
        for (int k = 0; k < MaxC; k ++)
            if (Trie[i][k] != -1)
            {
                Q[Tail] = Trie[i][k];
                Tail ++;
                Suffix[Trie[i][k]] = Trie[Suffix[i]][k];
            }
            else
                Trie[i][k] = Trie[Suffix[i]][k];
    }
}

int DP[MaxL][MaxDFASize];

int main()
{
    T['A'] = 0;
    T['C'] = 1;
    T['G'] = 2;
    T['T'] = 3;
    
    int Case = 0;
    while (1)
    {
        Case ++;
        memset(Trie, -1, sizeof(Trie));
        memset(Illegal, 0, sizeof(Illegal));
        memset(Suffix, -1, sizeof(Suffix));
        memset(DP, 10, sizeof(DP));
        scanf("%d", &N);
        if (N == 0)
            break;
        Size = 1;
        for (int i = 0; i < N; i ++)
            Insert();
        TrieGraphGen();

        scanf("%s", &Buf);
        int L = strlen(Buf);
        int Inf = DP[0][0];
        for (int k = 0; k < MaxC; k ++)
            if (! Illegal[Trie[0][k]])
                DP[0][Trie[0][k]] = (T[Buf[0]] != k);
        for (int i = 0; i < L - 1; i ++)
            for (int j = 0; j < Size; j ++)
                if (DP[i][j] != Inf)
                    for (int k = 0; k < MaxC; k ++)
                        if (! Illegal[Trie[j][k]])
                            DP[i + 1][Trie[j][k]] = min(DP[i + 1][Trie[j][k]], DP[i][j] + (T[Buf[i + 1]] != k));

        int Ans = Inf;
        for (int j = 0; j < Size; j ++)
            if (! Illegal[j])
                Ans = min(Ans, DP[L - 1][j]);
        printf("Case %d: %d\n", Case, (Ans == Inf) ? -1 : Ans);
    }
    return 0;
}

