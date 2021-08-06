#include<iostream>
#include<queue>
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

inline bool operator<(const Point &_a, const Point &_b)
{
    return _a.x < _b.x || (_a.x == _b.x && _a.y < _b.y);
}

struct op
{

    inline bool operator() (const Point &_a, const Point & _b)
    {
        return _a.x > _b.x || (_a.x == _b.x && _a.y < _b.y);
    }
};
priority_queue < Point, vector<Point>, op > Heap; //small top
//priority_queue < Point  > Heap; //small top
int main()
{
    while (Heap.size() != 0) Heap.pop();
    Heap.push(Point(1, 1));
    printf("%d\n", Heap.top().x);
    Heap.push(Point(10, 1));
    printf("%d\n", Heap.top().x);
    Heap.push(Point(1, 3));
    Heap.pop();
    printf("%d\n", Heap.top().x);
    return 0;
}
