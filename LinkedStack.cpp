#include <iostream>

using namespace std;

template<typename Object>
class Stack
{
    public:
        Stack() :topOfStack(NULL) {}
        Stack(const Stack &rhs);
        ~Stack() { makeEmpty(); }

        bool isEmpty() const 
        { return topOfStack==NULL; }
        const Object &top() const;

        void makeEmpty();
        void pop();
        void push(const Object &x);
        Object topAndPop();

        const Stack &operator=(const Stack &rhs);

    private:
        struct ListNode
        {
            Object element;
            ListNode *next;

            ListNode(const Object &theElement,ListNode *n=NULL)
                : element(theElement), next(n) {}
        };
        ListNode *topOfStack;
};
template<typename Object>
const Stack<Object> &
Stack<Object>::operator=(const Stack<Object> &rhs)
{
    if(this !=rhs)
    {
        makeEmpty();
        if(rhs.isEmpty()) return *this;

        ListNode *curr= rhs.topOfStack;
        ListNode *ptr =new ListNode(curr->element);
        topOfStack =ptr;

        for(curr=curr->next; curr!=NULL; curr=curr->next)
            ptr=ptr->next= new ListNode(curr->element);
    }

    return *this;
}
template<typename Object>
Stack<Object>::Stack(const Stack<Object> &rhs)
{
    topOfStack=NULL;
    *this=rhs;
}
template<typename Object>
void Stack<Object>::push( const Object &x)
{
    topOfStack = new ListNode(x,topOfStack);
}
template<typename Object>
void Stack<Object>::pop()
{
    ListNode *oldTop=topOfStack;
    topOfStack=topOfStack->next;
    delete oldTop;
}
template<typename Object>
const Object &Stack<Object>::top() const
{
    return topOfStack->element;
}

template<typename Object>
void Stack<Object>::makeEmpty()
{
    while(!isEmpty())
        pop();
}

int main()
{
    Stack<int> s;
    for(int i=0;i<10;i++)
    s.push(i);

    while(!s.isEmpty())
    {
        cout<<s.top() <<" ";
        s.pop();
       
    }

    return 0;
}