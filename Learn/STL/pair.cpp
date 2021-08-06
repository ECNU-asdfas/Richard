#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
using namespace std;
pair < int, int > Point;

int main()
{
    Point = make_pair(1, 2);
    cout << Point.first << " " << Point.second << endl;
}