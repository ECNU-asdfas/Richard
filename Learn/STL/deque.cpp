#include<iostream>
#include<algorithm> 
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<deque>
using namespace std;
deque < int > P;

int main()
{
    for (int i = 1; i <= 6; i++)
    {
        P.push_back(i);
        P.push_front(i + 100);
    }
    for (int i = 0; i < P.size(); i++)
        cout << P[i] << endl;
}