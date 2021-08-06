#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;

struct Point
{
    int x, y;

    Point()
    {
    }

    Point(int _x, int _y) : x(_x), y(_y)
    {
    }
} P[100];

inline bool operator<(const Point& _x, const Point& _y)
{
    if (_x.x < _y.x) return 1;
    else if (_x.x == _y.x && _x.y < _y.y) return 1;
    else return 0;
}

int main()
{
    for (int i = 1; i <= 10; i++)
        P[i] = Point(10 - i, 10 - i);
    sort(P + 1, P + 1 + 10);
    for (int i = 1; i <= 10; i++)
        printf("%d %d\n", P[i].x, P[i].y);
    return 0;
}