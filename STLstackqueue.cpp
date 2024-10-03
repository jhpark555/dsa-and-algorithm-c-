#include <iostream>
#include <vector>
#include <list>

using namespace std;

template< typename Object>
class stack: private list<Object>
{
    public:
        int size() const 
        {
            return list<Object>::size();
        }
        bool empty() const
        { return list<Object>::empty(); }
        Object &top()
        { return list<Object>::back() ;}
        const Object &top() const
        { return list<Object>::back(); }
        void push(const Object &x)
        { list<Object>::push_back(x); }
        void pop()
        {  list<Object>::pop_back(); }

};

int main()
{
    stack<int> s;

    for(int i=0;i<10;i++)
        s.push(i);

    for(int i=0;i<10;i++){
        cout<<s.top() <<" ";
        s.pop();
    }

}