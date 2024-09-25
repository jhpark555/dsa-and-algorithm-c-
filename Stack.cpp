#include <iostream>
#include <vector>

using namespace std;

template<typename Object>
class Stack
{
    public:
        Stack();

        bool isEmpty() const;
        const Object &top() const;

        void makeEmpty();
        Object &pop() ;
        void push(const Object &x);

    private:
        vector<Object> theArray;
        int     topOfStack;

};

template<typename Object>
Stack<Object>::Stack() : theArray(1)
{
    topOfStack =-1;
}

template<typename Object>
bool Stack<Object>::isEmpty() const
{ 
    return topOfStack ==-1; 
}

template<typename Object>
void Stack<Object>:: makeEmpty()
{ topOfStack =-1; }

template<typename Object>
void Stack<Object>::push(const Object &x)
{
    if(topOfStack==theArray.size()-1)
        theArray.resize(theArray.size()* 2 +1);
    theArray[++topOfStack]=x;
}

template<typename Object>
const Object & Stack<Object>::top() const
{
    if( isEmpty())
        cout<<"Empty"<<endl;
    return theArray[topOfStack];
}

template<typename Object>
Object & Stack<Object>::pop()
{
    return theArray[topOfStack--];
}

int main()
{
    Stack<int> s;

     for( int i = 0; i < 10; i++ )
        s.push( i );

    while( !s.isEmpty( ) )
        cout << s.pop( )  << " ";
    return 0;
}