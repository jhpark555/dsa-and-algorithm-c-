#include <iostream>
#include <vector>

using namespace std;

template< typename Object>
class Queue
{
    public:
        Queue();

        bool isEmpty() const;
        const Object &getFront() const;

        void makeEmpty() ;
        Object dequeue();
        void enqueue(const Object &x);

    private:
        vector<Object> theArray;
        int     currentSize;
        int     front;
        int     back;

        void increment(int &x) const;
        void doubleQueue();

};

template<typename Object>
void Queue<Object>::increment(int &x) const
{
    if(++x == theArray.size())
        x=0;
}

template<typename Object>
Queue<Object>::Queue() : theArray(1)
{
    makeEmpty();
}

template<typename Object>
bool Queue<Object>::isEmpty() const
{
    return currentSize==0;
}

template<typename Object>
void Queue<Object>:: enqueue(const Object &x)
{
    cout<<"Array size is " << theArray.size();
    if(currentSize ==theArray.size())
        doubleQueue();
    increment(back);
    theArray[back]=x;
    currentSize++;
}
template<typename Object>
void Queue<Object>::doubleQueue()
{
    theArray.resize(theArray.size() *2 +1 );
     cout<<" Double"<<endl;
    if( front !=0)
    {       
        for(int i=0; i< front; i++)
            theArray[i+currentSize]= theArray[i];
        back +=currentSize;
    }
} 
template<typename Object>
Object Queue<Object>::dequeue()
{
    if(isEmpty()) return -1;

    currentSize--;

    Object frontitem = theArray[front];
    increment(front);

    return frontitem;
}

template<typename Object>
const Object & Queue<Object>:: getFront() const
{
    if(isEmpty()) return -1;

    return theArray[front];
}

template<typename Object>
void Queue<Object>::makeEmpty()
{
    currentSize =0;
    front =0;
    back = theArray.size() -1;
}

int main()
{
    Queue<int> q;

    for(int i=0;i<10; i++)
        q.enqueue(i);
    
    for(int i=0;i<10;i++)
        cout<<q.dequeue() <<" ";

    return 0;
}