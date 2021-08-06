#include<iostream>
#include<queue>
using namespace std;
priority_queue < int, vector<int>, greater<int> > Heap; //big top

int main()
{
    while (Heap.size() != 0) Heap.pop();
    Heap.push(1);
    printf("%d\n", Heap.top());
    Heap.push(10);
    printf("%d\n", Heap.top());
    Heap.push(3);
    Heap.pop();
    printf("%d\n", Heap.top());
    return 0;
}