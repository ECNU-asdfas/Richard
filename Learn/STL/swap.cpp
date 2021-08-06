#include<iostream>
#include<algorithm>
using namespace std;

template < class T >
inline const T& swap(const T& _x, const T& _y)
{
    _x ^= _y, _y ^= _x, _x ^= _y;
    /*
     *T Swap_Tmp(_x);
     * _x=_y,_y=Tmp; 
     */
}

int main()
{
    double a, b;
    cin >> a >> b;
    cout << a << " " << b << endl;
    swap(a, b);
    cout << a << " " << b << endl;
}