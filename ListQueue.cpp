#include <iostream>
using namespace std;

template<typename Object>
class Queue
{
    public:
        Queue()
        { front=back=NULL; }
        Queue(const Queue &rhs);
        ~Queue()
        { makeEmpty(); }
        const Queue &operator=(const Queue &rhs);

        bool isEmpty() const
        { return front==NULL; }
        const Object &getFront() const;

        void makeEmpty();
        Object dequeue();
        void enqueue(const Object &x);
    private:
        struct ListNode
        {
            Object element;
            ListNode *next;

            ListNode(const Object & theElement, ListNode *n =NULL)
            : element(theElement), next( n)  {}

        };

        ListNode *front;
        ListNode *back;
};

template<typename Object>
Queue<Object>::Queue( const Queue<Object> &rhs)
{
    front=back=NULL;
    *this=rhs;
}
template<typename Object>
const Queue<Object> &
Queue<Object>::operator=(const Queue<Object> &rhs)
{
    if(this!=rhs)
    {
        makeEmpty();
        ListNode *rptr;
        for( rptr=rhs.front; rptr!=NULL; rptr=rptr->next)
            enqueue(rptr->element);
    }
    return *this;
}
template<typename Object>
void Queue<Object>::enqueue(const Object &x)
{    
    ListNode *newnode =new ListNode(x);
    if(isEmpty())
       back=front=newnode;
    else{
       back->next=newnode;
       back=newnode;
    }   
}
template<typename Object>
Object Queue<Object>::dequeue()
{
    Object frontItem= getFront();
    ListNode *old= front;
    front=front->next;
    delete old;
    return frontItem;
}
template<typename Object>
const Object &Queue<Object>::getFront() const
{
    return front->element;    
}
template<typename Object>
void Queue<Object>::makeEmpty()
{
    while(!isEmpty())
        dequeue();
}

int main()
{
    Queue<int> q;

    for(int i=0;i<10;i++)
        q.enqueue(i);

    while(!q.isEmpty())
        cout<<q.dequeue()<< " ";

    return 0;
}