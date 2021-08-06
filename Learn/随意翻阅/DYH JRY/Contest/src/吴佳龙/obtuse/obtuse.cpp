#include <iostream>
#include <fstream>
#include <cstring>
#include <algorithm>

#define checker(i,j,k) ((i)*(i)+(j)*(j)-(k)*(k))*((i)+(j)-(k))
#define change(i,j) ((i)^=(j),(j)^=(i),(i)^=(j))

using namespace std;

bool get[300030];
int ans[100005][2],check[100005];

int main(void)
{
	ifstream cin("obtuse.in");
	ofstream cout("obtuse.out");
	
	int n;
	
	cin>>n;
	if(n==1)
	{
		cout<<"2 3 4";
	}
	else if(n==2)
	{
		cout<<"2 5 7"<<endl<<"3 4 6";
	}
	else if(n==3)
	{
		cout<<"2 9 10"<<endl<<"3 6 7"<<endl<<"4 5 8";
	}
	else if(n==4)
	{
		cout<<"2 12 13"<<endl<<"3 9 11"<<endl<<"4 7 10"<<endl<<"5 6 8";
	}
	else if(n==5)
	{
		cout<<"2 15 16"<<endl<<"3 12 14"<<endl<<"4 10 13"<<endl<<"5 8 11"<<endl<<"6 7 9";
	}
	else if(n==6)
	{
		cout<<"2 18 19"<<endl<<"3 15 17"<<endl<<"4 13 16"<<endl<<"5 10 14"<<endl<<"6 9 12"<<endl<<"7 8 11"<<endl;
	}
	else if(n==7)
    {
        cout<<"2 21 22"<<endl<<"3 18 20"<<endl<<"4 16 19"<<endl<<"5 13 17"<<endl<<"6 11 15"<<endl<<"7 9 12"<<endl<<"8 10 14"<<endl;
    }    
	else if(n==8)
    {
        cout<<"2 24 25"<<endl<<"3 21 23"<<endl<<"4 19 22"<<endl<<"5 16 20"<<endl<<"6 13 18"<<endl<<"7 12 15"<<endl<<"8 11 17"<<endl<<"9 10 14"<<endl;
    }
	else if(n==9)
    {
        cout<<"2 27 28"<<endl<<"3 24 26"<<endl<<"4 22 25"<<endl<<"5 19 23"<<endl<<"6 16 21"<<endl<<"7 14 18"<<endl<<"8 13 20"<<endl<<"9 12 17"<<endl<<"10 11 15"<<endl;
    }
    else if(n==10)
    {
        cout<<"2 30 31"<<endl<<"3 27 29"<<endl<<"4 25 28"<<endl<<"5 22 26"<<endl<<"6 19 24"<<endl<<"7 16 21"<<endl<<"8 13 23"<<endl<<"9 15 20"<<endl<<"10 14 18"<<endl<<"11 12 17"<<endl;
    }
    else
    {
    	for(int i=2,pos=3*n+1;i<=n+1;i++)
    	{
    		while(get[pos])
    		{
    			pos--;
			}
			
			ans[i][1]=pos;
			get[pos]=true;
			get[i]=true;
			
			for(int j=max(pos-i+1,n+2);j<=3*n+1;j++)
			{
				if(!get[j])
				{
					ans[i][0]=j;
					get[j]=true;
					break;
				}
			}
		}
		
		for(int i=2;i<=n+1;i++)
		{
			check[i]=checker(i,ans[i][0],ans[i][1]);
		}
		
		for(int i=n+1;i>=2;i--)
		{
			if(check[i]>=0)
			{
				for(int j=i-1;j>=2;j--)
				{
					if(checker(j,ans[j][0],ans[i][1])<0)
					{
						change(ans[i][1],ans[j][1]);
						check[i]=checker(i,ans[i][0],ans[i][1]);
						check[j]=checker(j,ans[j][0],ans[j][1]);
					}
					if(check[i]<0)
					{
						break;
					}
				}
			}
		}
		
		bool cor=true;
			
		memset(get,0,sizeof(get));
		for(int i=2;i<=n+1;i++)
		{
			get[i]=true;
			get[ans[i][0]]=true;
			get[ans[i][1]]=true;
			if(check[i]>=0)
			{
				cor=false;
				cout<<"-1";
				break;
			}
		}
		
		for(int i=2;i<=3*n+1;i++)
		{
			if(!get[i])
			{
				cor=false;
				cout<<"-1";
				break;
			}
		}
		
		if(cor)
		{
			for(int i=2;i<=n+1;i++)
			{
				cout<<i<<" "<<ans[i][0]<<" "<<ans[i][1]<<endl;
			}
		}
	}
    
	return 0;
}
