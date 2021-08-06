#include <cstdio>
#include <set>

const int modulo[2] = {1000000007,1000000009};

struct compare_t
{
	bool operator()(int a,int b);
};

std::set<int,compare_t> set;

int n,q;
char string[200020];
int hash[200020][2];
int power[200020][2];
long long result[200020];

int lcp(int a,int b)
{
	int l = 0;
	int r;
	int m = 0;
	int answer = 0;
	
	if(a > b)
		std::swap(a,b);
	r = n - b + 1;
	
	while(l <= r)
	{
		m = (l + r) >> 1;
		if((hash[a + m - 1][0] - 1ll * hash[a - 1][0] * power[m][0] % modulo[0] + modulo[0]) % modulo[0] == (hash[b + m - 1][0] - 1ll * hash[b - 1][0] * power[m][0] % modulo[0] + modulo[0]) % modulo[0] && 
			(hash[a + m - 1][1] - 1ll * hash[a - 1][1] * power[m][1] % modulo[1] + modulo[1]) % modulo[1] == (hash[b + m - 1][1] - 1ll * hash[b - 1][1] * power[m][1] % modulo[1] + modulo[1]) % modulo[1]){
			answer = m;
			l = m + 1;
		}else{
			r = m - 1;
		}
	}
	
	return answer;
}

bool compare_t::operator()(int a,int b)
{
	int k = lcp(a,b);
	return string[a + k] < string[b + k];
}

int main(void)
{
	int x;
	int i;
	std::set<int>::iterator it,it1,it2;
	
	freopen("infstring.in","r",stdin);
	freopen("infstring.out","w",stdout);
	
	scanf("%d %d",&n,&q);
	scanf("%s",string + 1);
	
	for(i = 1;n - i + 1 > i;++i)
		std::swap(string[i],string[n - i + 1]);
	
	for(i = 1;i <= n;++i)
		hash[i][0] = (1ll * 27 * hash[i - 1][0] + string[i] - 'a' + 1) % modulo[0],
		hash[i][1] = (1ll * 27 * hash[i - 1][1] + string[i] - 'a' + 1) % modulo[1];
	
	n <<= 1;
	power[0][0] = power[0][1] = 1;
	for(i = 1;i <= n;++i)
		power[i][0] = 1ll * power[i - 1][0] * 27 % modulo[0],power[i][1] = 1ll * power[i - 1][1] * 27 % modulo[1];
	n >>= 1;
	
	for(i = 1;i < n;++i)
	{
		// 1 ~ n - i == i + 1 ~ n
		if(n % i)
			continue;
		if(hash[n - i][0] != (hash[n][0] - 1ll * hash[i][0] * power[n - i][0] % modulo[0] + modulo[0]) % modulo[0])
			continue;
		if(hash[n - i][1] != (hash[n][1] - 1ll * hash[i][1] * power[n - i][1] % modulo[1] + modulo[1]) % modulo[1])
			continue;
		break;
	}
	n = i;
	
	for(i = 1;i <= n;++i)
		string[i + n] = string[i];
	n <<= 1;
	string[n + 1] = 0;
	
	for(i = 1;i <= n;++i)
		hash[i][0] = (1ll * 27 * hash[i - 1][0] + string[i] - 'a' + 1) % modulo[0],
		hash[i][1] = (1ll * 27 * hash[i - 1][1] + string[i] - 'a' + 1) % modulo[1];
	
	for(i = n;i >= 1;--i)
	{
		it = it1 = it2 = set.insert(i).first;
		if(it == set.begin()){
			result[i] = result[i + 1] + n - i + 1;
		}else{
			--it1;
			result[i] = result[i + 1] + n - i + 1 - lcp(i,*it1);
		}
		
		++it2;
		if(it2 == set.end())
			continue;
		
		result[i] -= lcp(i,*it2);
		if(it != set.begin())
			result[i] += lcp(*it1,*it2);
	}
	
	while(q--)
	{
		scanf("%d",&x);
		
		if(x <= n){
			printf("%I64d\n",result[n - x + 1]);
			continue;
		}
		
		printf("%I64d\n",result[1] + 1ll * (x - n) * (n >> 1));
	}
	
	return 0;
}
