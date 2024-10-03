#include <iostream>
#include <list>

using namespace std;

template<typename Object>
class LList;

template<typename Object>
class LListItr;

template<typename Object>
class LListNode
{
    LListNode( const Object & theElement =Object(), LListNode *n=NULL)
        : element(theElement), next(n)   {}
    Object element;
    LListNode *next;

    friend class LList<Object>;
    friend class LListItr<Object>;
};

template<typename Object>
class LListItr
{
    public:
        LListItr() : current(NULL) {}
        bool isValid() const
        { return current!=NULL; }
        void advance()
        { if(isValid()) current=current->next; }
        const Object &retrieve() const
        { return current->element; }

    private:
        LListNode<Object> *current;
        LListItr(LListNode<Object> *theNode)
          : current(theNode)   {}

        friend class LList<Object>;
};

template<typename Object>
class LList
{
    public:
        LList();
        LList(const LList &rhs);
        ~LList();

        bool isEmpty() const;
        void makeEmpty();
        LListItr<Object> zeroth() const;
        LListItr<Object> first() const;
        void insert(const Object &x,const LListItr<Object> &p);
        LListItr<Object> find(const Object & x) const;
        LListItr<Object> findPrevious( const Object &x) const;
        void remove(const Object &x);

        const LList & operator=(const LList &rhs);

    private:
        LListNode<Object> *header;

};

template<typename Object>
LList<Object>::LList()
{
    header = new LListNode<Object>;
}
// Make the list logically empty.
template <class Object>
void LList<Object>::makeEmpty( )
{
    while( !isEmpty( ) )
        remove( first( ).retrieve( ) );
}

// Destructor.
template <class Object>
LList<Object>::~LList( )
{
    makeEmpty( );
    delete header;
}
template<typename Object>
bool LList<Object>::isEmpty() const
{
    return header->next ==NULL;
}
template<typename Object>
LListItr<Object> LList<Object>::zeroth() const
{
    return LListItr<Object>(header) ;
}
template<typename Object>
LListItr<Object> LList<Object>::first() const
{
    return LListItr<Object>(header->next);
}
template<typename Object>
void printList(const LList<Object> &theList)
{
    if(theList.isEmpty())
        cout<<"Empty list"<<endl;
    else
    {
        LListItr<Object> itr=theList.first();
        for(; itr.isValid(); itr.advance() )
            cout<< itr.retrieve() << " ";
    }
    cout<<endl;
}
template<typename Object>
LListItr<Object> LList<Object>::find(const Object &x) const
{
    LListNode<Object> *p= header->next;
    while( p!=NULL && p->element !=x)
        p=p->next;
    return LListItr<Object>(p) ;

}
template<typename Object>
void LList<Object>::remove(const Object &x)
{
    LListNode<Object> *p=findPrevious(x).current;

    if(p->next!= NULL)
    {
        LListNode<Object> *oldNode = p->next;
        p->next=p->next->next;
        delete oldNode;
    }
}
template<typename Object>
LListItr<Object> LList<Object>::findPrevious(const Object &x) const
{
    LListNode<Object> *p=header;
    while( p->next !=NULL && p->next->element!=x)
        p=p->next;
    return LListItr<Object>(p);
}
template<typename Object>
void LList<Object>::insert(const Object &x, const LListItr<Object> &p)
{
    if(p.current !=NULL)
        p.current->next=new LListNode<Object>( x, p.current->next);
}

int main()
{
    LList<int> theList;
    LListItr<int> theItr=theList.zeroth();

    for(int i=0;i<10;i++)
        theList.insert(i,theItr);

    printList(theList);


}