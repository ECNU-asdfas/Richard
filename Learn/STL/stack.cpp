#include<iostream>
#include<stack>
using namespace std;
stack <int> S;

int main()
{
    while (S.size() != 0) S.pop();
    S.push(1);
    cout << S.top() << endl;
    S.pop();
}
