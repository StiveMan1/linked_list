#include <bits/stdc++.h>
#include <ctime>

#include "list.h"

using namespace std;

template<class T>
void s_list<T>::show() const {
    node<T> *now = this->first;
    for (size_t i = 0; i < _size; i++) {
        cout<<now->data<<" ";
        now = now->next;
    }
    cout<<endl;
}

int main() {
    srand(time(0));

    s_list<int> first;
    int size = rand() % 30;
    for (int i = 0; i < size; i++)
        first.add_to_head(rand() % 10 * 10 + rand() % 10);

    first.show();

    first.delete_from_head();
    first.delete_from_tail();
    first.show();
//
//    s_list<int> second;
//    size = rand() % 20;
//    for (int i = 0; i < size; i++)
//    	second.add_to_head(rand() % 10);
//    second.show();
//
//    second.add_to_tail(rand() % 10);
//    second.show();

//    s_list<int> third(second);
//    third.show();

//    s_list<int> fourth;
//    fourth = first;
//    fourth.show();

//    first.sort();
//    first.show();

//    first.reverse();
//    first.show();

//    size = first.size();
//    for (int i = 0; i < size; i++) {
//    	int value = first[i];
//    	cout << value << " ";
//    }
//    cout << endl;

//    first.delete_at(3);
//    first.show();

//    first.insert_at(4, 10);
//    first.show();

//    first.delete_all();
//    first.show();

//    first.splice(third);
//    first.show();
    //first.splice(fourth);
    //first.show();

//    size_t result = first.find(10);
//    if (result != 0)
//    	cout << "The number ten is in position: " << result << endl;
//    else
//    	cout << "Numbers ten not found" << endl;
//
//    first.find_and_replace(10, 1000);
//
//    for (auto it = first.begin(); it != first.end(); ++it)
//    	cout << *it << " ";

    return 0;
}