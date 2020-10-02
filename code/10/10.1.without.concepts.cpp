#include <list>
#include <algorithm>
using namespace std;
int main() {
    list<int> l;
    list<int>::iterator i;
    l.push_back(10);
    l.push_back(2);
    l.push_back(13);
    l.push_back(56);
    l.push_back(7);
    l.push_back(3);
    l.sort(); //You can use sort() function for sorting the list.
    cout<<"The Elements after sorting are:"<<endl;
    for(i =l.begin();i!=l.end();i++)
    {
    	cout<<*i<<endl;
	}
    return 0;
}
