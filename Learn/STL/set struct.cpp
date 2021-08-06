#include<iostream>
#include<set>
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

};

struct op
{

    bool operator () (const Point &a, const Point & b)
    {
        return a.x < b.x || (a.x == b.x && a.y < b.y);
    }
};

set < Point, op > T;
set < Point > ::const_iterator pos;

int main()
{
    T.insert(Point(1, 1));
    T.insert(Point(-1, 1));
    T.insert(Point(100, 1));
    T.insert(Point(1, -1));
    for (pos = T.begin(); pos != T.end(); pos++)
        printf("%d %d\n", (*pos).x, (*pos).y);
    pos = T.upper_bound(Point(0, 0));
    printf("%d %d\n", (*pos).x, (*pos).y);
    return 0;
}
