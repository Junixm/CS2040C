#include "linkedlist.h"

using namespace std;

int main()
{
    cout << "Test\n";
    List<int> list1 = { 1, 2, 3 };
    cout << list1.to_string() << endl;
    List<int> list2 = list1;
    list2.pop_head();
    cout << list2.to_string() << endl;
    list2.push_head(10);
    cout << list2.to_string() << endl;
}