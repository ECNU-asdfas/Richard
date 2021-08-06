#include<iostream>
#include<algorithm> 
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<vector>
using namespace std;
vector < int > P;
vector < int > ::const_iterator Pos;

int main()
{
    P.clear();
    for (int i = 1; i <= 6; i++)
        P.push_back(10 - i);
    for (int i = 0; i < P.size(); i++)
        cout << P[i] << endl;
    cout << endl;
    cout << "P.back()" << P.back() << endl;
    P.pop_back();
    cout << "P.back()" << P.back() << endl;
    cout << "P.front()" << P.front() << endl;
    if (P.empty()) cout << "Empty" << endl;
    else cout << "UnEmpty" << endl;
    sort(P.begin(), P.end());
    cout << endl;
    for (Pos = P.begin(); Pos != P.end(); Pos++)
        cout << *Pos << endl;
}