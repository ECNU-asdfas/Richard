#include<cstdio>
#include<cstdlib>
#include<ctime>
using namespace std;

int main(){
  srand(time(0));
  //freopen("t.in","r",stdin);
  freopen("obtuse.in","w",stdout);
  int n=rand()*rand()%20000+10000;
  printf("%d\n",n);
}
