#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
struct node{
	int x,y,z;
	node(){}
	node(int x,int y,int z):x(x),y(y),z(z){}
}ans[20][20];
int n,i;
int main()
{
	freopen("obtuse.in","r",stdin);
	freopen("obtuse.out","w",stdout);
ans[1][1]=node(2,3,4);
ans[2][1]=node(2,4,5);ans[2][2]=node(3,6,7);
ans[3][1]=node(2,4,5);ans[3][2]=node(3,8,9);ans[3][3]=node(6,7,10);
ans[4][1]=node(2,3,4);ans[4][2]=node(5,7,11);ans[4][3]=node(6,9,12);ans[4][4]=node(8,10,13);
ans[5][1]=node(2,3,4);ans[5][2]=node(5,6,10);ans[5][3]=node(7,11,14);ans[5][4]=node(8,12,15);ans[5][5]=node(9,13,16);
ans[6][1]=node(2,3,4);ans[6][2]=node(5,6,10);ans[6][3]=node(7,11,17);ans[6][4]=node(8,13,16);ans[6][5]=node(9,15,18);ans[6][6]=node(12,14,19);
ans[7][1]=node(2,3,4);ans[7][2]=node(5,6,10);ans[7][3]=node(7,8,14);ans[7][4]=node(9,16,19);ans[7][5]=node(11,17,21);ans[7][6]=node(12,18,22);ans[7][7]=node(13,15,20);
ans[8][1]=node(2,3,4);ans[8][2]=node(5,6,10);ans[8][3]=node(7,8,14);ans[8][4]=node(9,13,21);ans[8][5]=node(11,18,22);ans[8][6]=node(12,20,24);ans[8][7]=node(15,17,23);ans[8][8]=node(16,19,25);
ans[9][1]=node(2,3,4);ans[9][2]=node(5,6,10);ans[9][3]=node(7,8,14);ans[9][4]=node(9,11,19);ans[9][5]=node(12,20,24);ans[9][6]=node(13,22,26);ans[9][7]=node(15,23,28);ans[9][8]=node(16,21,27);ans[9][9]=node(17,18,25);
ans[10][1]=node(2,3,4);ans[10][2]=node(5,6,10);ans[10][3]=node(7,8,14);ans[10][4]=node(9,11,19);ans[10][5]=node(12,15,26);ans[10][6]=node(13,23,27);ans[10][7]=node(16,24,29);ans[10][8]=node(17,21,28);ans[10][9]=node(18,25,31);ans[10][10]=node(20,22,30);
ans[11][1]=node(2,3,4);ans[11][2]=node(5,6,10);ans[11][3]=node(7,8,14);ans[11][4]=node(9,11,19);ans[11][5]=node(12,13,24);ans[11][6]=node(15,23,29);ans[11][7]=node(16,25,30);ans[11][8]=node(17,27,32);ans[11][9]=node(18,28,34);ans[11][10]=node(20,26,33);ans[11][11]=node(21,22,31);
ans[12][1]=node(2,3,4);ans[12][2]=node(5,6,10);ans[12][3]=node(7,8,14);ans[12][4]=node(9,11,19);ans[12][5]=node(12,13,24);ans[12][6]=node(15,16,30);ans[12][7]=node(17,28,33);ans[12][8]=node(18,26,32);ans[12][9]=node(20,31,37);ans[12][10]=node(21,29,36);ans[12][11]=node(22,27,35);ans[12][12]=node(23,25,34);
ans[13][1]=node(2,3,4);ans[13][2]=node(5,6,10);ans[13][3]=node(7,8,14);ans[13][4]=node(9,11,19);ans[13][5]=node(12,13,24);ans[13][6]=node(15,16,30);ans[13][7]=node(17,25,34);ans[13][8]=node(18,31,37);ans[13][9]=node(20,32,38);ans[13][10]=node(21,29,36);ans[13][11]=node(22,33,40);ans[13][12]=node(23,26,35);ans[13][13]=node(27,28,39);
scanf("%d",&n);
for(i=1;i<=n;i++)printf("%d %d %d\n",ans[n][i].x,ans[n][i].y,ans[n][i].z);
}
