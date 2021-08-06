#include<set>
#include<map>
#include<queue>
#include<cmath>
#include<string>
#include<cstdio>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
#define rep(i,a,b) for (int i=a; i<=b; i++)
#define per(i,a,b) for (int i=a; i>=b; i--)
using namespace std;
typedef long long LL;

inline int read() {
    int x=0,f=1; char ch=getchar();
    while (!(ch>='0'&&ch<='9')) {if (ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9') {x=x*10+(ch-'0'); ch=getchar();}
    return x*f;
}

const int N = 100005;

int n;
LL a[N],b[N],c[N];

int main() {

    #ifndef ONLINE_JUDGE
        freopen("obtuse.in","r",stdin);
        freopen("obtuse.out","w",stdout);
    #endif

	n=read();
	if (n==1) printf("2 3 4\n");
	else if (n==2) printf("2 4 5\n3 6 7\n");
	else if (n==3) printf("2 9 10\n3 6 7\n4 5 8\n");
	else if (n==4) printf("2 3 4\n5 7 11\n6 9 12\n8 10 13\n");
	else if (n==5) printf("2 3 4\n5 6 8\n7 12 14\n9 13 16\n10 11 15\n");
	else if (n==6) printf("2 3 4\n5 6 8\n7 10 16\n9 14 17\n11 15 19\n12 13 18\n");
	else if (n==7) printf("2 3 4\n5 6 8\n7 9 14\n10 16 19\n11 17 21\n12 18 22\n13 15 20\n");
	else if (n==8) printf("2 3 4\n5 6 8\n7 9 12\n10 13 21\n11 20 23\n14 19 24\n15 16 22\n17 18 25\n");
	else if (n==9) printf("2 3 4\n5 6 8\n7 9 12\n10 11 18\n13 20 24\n14 23 27\n15 21 26\n16 19 25\n17 22 28\n");
	else if (n==10) printf("2 3 4\n5 6 8\n7 9 12\n10 11 15\n13 19 26\n14 23 27\n16 24 29\n17 21 28\n18 25 31\n20 22 30\n");
	else if (n==11) printf("2 3 4\n5 6 8\n7 9 12\n10 11 15\n13 14 25\n16 24 29\n17 27 32\n18 23 30\n19 28 34\n20 26 33\n21 22 31\n");
	else if (n==12) printf("2 36 37\n3 34 35\n4 32 33\n5 30 31\n6 28 29\n7 26 27\n8 23 25\n9 22 24\n10 16 19\n11 14 18\n12 17 21\n13 15 20\n");
	else if (n==13) printf("2 39 40\n3 37 38\n4 35 36\n5 33 34\n6 31 32\n7 29 30\n8 26 28\n9 25 27\n10 20 24\n11 18 22\n12 14 19\n13 16 21\n15 17 23\n");
	else if (n==14) printf("2 42 43\n3 40 41\n4 38 39\n5 36 37\n6 34 35\n7 32 33\n8 29 31\n9 28 30\n10 25 27\n11 21 24\n12 19 23\n13 15 20\n14 16 22\n17 18 26\n");
	else if (n==15) printf("2 45 46\n3 43 44\n4 41 42\n5 39 40\n6 37 38\n7 35 36\n8 33 34\n9 30 32\n10 29 31\n11 25 28\n12 22 26\n13 16 21\n14 19 24\n15 17 23\n18 20 27\n");
	else if (n==16) printf("2 48 49\n3 46 47\n4 44 45\n5 42 43\n6 40 41\n7 38 39\n8 36 37\n9 33 35\n10 32 34\n11 28 31\n12 27 30\n13 21 25\n14 19 24\n15 17 23\n16 20 26\n18 22 29\n");
	else if (n==17) printf("2 51 52\n3 49 50\n4 47 48\n5 45 46\n6 43 44\n7 41 42\n8 39 40\n9 36 38\n10 35 37\n11 32 34\n12 30 33\n13 25 31\n14 23 27\n15 21 26\n16 17 24\n18 22 29\n19 20 28\n");
	else if (n==18) printf("2 54 55\n3 52 53\n4 50 51\n5 48 49\n6 46 47\n7 44 45\n8 42 43\n9 39 41\n10 38 40\n11 35 37\n12 33 36\n13 31 34\n14 26 30\n15 24 29\n16 21 27\n17 18 25\n19 20 28\n22 23 32\n");
	else if (n==19) printf("2 57 58\n3 55 56\n4 53 54\n5 51 52\n6 49 50\n7 47 48\n8 45 46\n9 43 44\n10 40 42\n11 39 41\n12 36 38\n13 34 37\n14 32 35\n15 26 31\n16 24 29\n17 22 28\n18 20 27\n19 23 30\n21 25 33\n");
	else if (n==20) printf("2 60 61\n3 58 59\n4 56 57\n5 54 55\n6 52 53\n7 50 51\n8 48 49\n9 46 47\n10 43 45\n11 42 44\n12 39 41\n13 37 40\n14 35 38\n15 31 36\n16 24 29\n17 27 32\n18 21 28\n19 26 33\n20 22 30\n23 25 34\n");
	else printf("-1\n");

    return 0;
}

