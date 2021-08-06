#include <iostream>
#include <fstream>
#include <string>
#include <set>

using namespace std;

int main(void)
{
	ifstream cin("infstring.in");
	ofstream cout("infstring.out");
	
	string s;
	int n,q;
	
	cin>>n>>q>>s;
	for(int i=0;i<q;i++)
	{
		string temp;
		string::iterator l,r;
		set<string> t;
		int x;
		
		cin>>x;
		for(int j=0;j<=x/s.length();j++)
		{
			temp+=s;
		}
		
		l=temp.begin();
		r=temp.begin();
		
		for(l=temp.begin();l!=temp.begin()+1+x;l++)
		{
			for(r=l;r!=temp.begin()+1+x;r++)
			{
				if(r!=l)
				{
					t.insert(string(l,r));
				}
			}
		}
		
		cout<<t.size()<<endl;
	}

	return 0;
}

