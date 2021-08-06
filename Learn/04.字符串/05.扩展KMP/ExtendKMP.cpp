#include <cstdio>
#include <cstring>
#include <cstdlib>
char s[1000010], t[1000010], c;
int extend[1000001], nxt[1000001], m, n, a, p;
int main()
{
	c = getchar();
	m = 0;
	while(c != '\n' && c != '\r')
	{
		s[++m] = c;
		c = getchar();
	}
	s[m + 1] = 1;
	c = getchar();
	n = 0;
	while(c != '\n' && c != '\r')
	{
		t[++n] = c;
		c = getchar();
	}
	t[n + 1] = 2;
	//Get Next array
	nxt[1] = n;
	for(int i = 1; ; ++i)
		if(t[i] != t[i + 1])
		{
			nxt[2] = i - 1;
			break;
		}
	a = 2;
	for(int i = 2; i < n; ++i)
	{
		p = a + nxt[a] - 1;
		int L = nxt[i - a + 2];
		if(i + L < p) nxt[i + 1] = L;
		else
		{
			for(int j = 1; ;j++)
			{
				if(t[p + j] != t[p - i + j])
				{
					nxt[i + 1] = p - i + j - 1;
					if(a + nxt[a] < i + 1 + nxt[i + 1])
						a = i + 1;
					break;
				}
			}
		}
	}
	//Get Extend array
	for(int i = 1; ;++i)
		if(s[i] != t[i])
		{
			extend[1] = i - 1, a = 1;
			break;
		}
	for(int i = 1; i < m; ++i)
	{
		p = a + extend[a] - 1;
		int L = nxt[i - a + 2];
		if(i + L < p) extend[i + 1] = L;
		else
		{
			for(int j = 1; ;j++)
			{
				if(s[p + j] != t[p - i + j])
				{
					extend[i + 1] = p - i + j - 1;
					if(a + extend[a] < i + 1 + extend[i + 1])
						a = i + 1;
					break;
				}
			}
		}
	}
	int Ans = 0;
	for(int i = 1; i <= m; ++i)
		if(extend[i] == n)
			++Ans;
	printf("%d\n", Ans);
	return 0; 
}
