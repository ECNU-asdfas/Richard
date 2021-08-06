#include<iostream>
#include<map>
#include<string>
using namespace std;
map < string, int > Hash;
map < string, int > ::const_iterator pos;

int main()
{
    Hash.clear();
    Hash.insert(make_pair("aaa", 123));
    Hash.insert(make_pair("bbb", 222));
    cout << Hash["aaa"] << endl;
    //Find
    //Case1
    cout << Hash.count("aaa") << endl;
    //Case2
    pos = Hash.find("ccc");
    if (pos != Hash.end()) cout << "Find Succed" << endl;
    else cout << "Find Failed" << endl;
    //Remove
    Hash.erase("aaa");
    if (Hash.count("aaa"))
        cout << Hash["aaa"] << endl;
    else cout << "No aaa" << endl;
    return 0;
}
