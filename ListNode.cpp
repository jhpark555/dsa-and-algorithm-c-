#include <iostream>


using namespace std;

template<typename Object>
class ConstListItr;

template<typename Object>
class ListItr;

template<typename Object>
class list;


template<typename Object>
class ListNode
{
    Object data;
    ListNode *prev;
    ListNode *next;

    ListNode( const Object &d =Object(), ListNode *p=NULL, ListNode *n=NULL)
     : data( d), prev( p), next(p)  {}
    
    friend class ConstListItr<Object>;
    friend class ListItr<Object>;
    friend class list<Object>;
};

template<typename Object>
class list
{
    public:
        typedef ListItr<Object> iterator;
        typedef ConstListItr<Object> const_iterator;

        list();
        ~list();

        list(const list &rhs);
        const list& operator=( const list &rhs);

        iterator begin();
        const_iterator begin() const;

        iterator end();
        const_iterator end() const;

        int size() const;
        bool empty() const;

        Object &front();
        const Object &front() const;

        Object &back();
        const Object &back() const;

        void push_front( const Object &x);
        void push_back( const Object &x);
        void pop_front() ;
        void pop_back();

        iterator insert( iterator itr, const Object &x);
        iterator erase( iterator itr);
        iterator erase( iterator start, iterator end);

        friend class ConstListItr<Object>;
        friend class ListItr<Object>;

    private:
        typedef ListNode<Object> node;
        int theSize;
        node *head;
        node *tail;

        void init();
        void makeEmpty();
};

template <class Object>
class ConstListItr
{
  public:
    ConstListItr( );
    virtual ~ConstListItr( ) { }

    virtual const Object & operator* ( ) const;
    
    ConstListItr & operator++ ( );
    ConstListItr operator++ ( int );

    ConstListItr & operator-- ( );
    ConstListItr operator-- ( int );
        
    bool operator== ( const ConstListItr & rhs ) const;
    bool operator!= ( const ConstListItr & rhs ) const;

  protected:
    typedef ListNode<Object> node;

    node *head;
    node *current;

    friend class list<Object>;
    void assertIsInitialized( ) const;
    void assertIsValid( ) const;
    void assertCanAdvance( ) const;
    void assertCanRetreat( ) const;
    Object & retrieve( ) const;

    ConstListItr( const list<Object> & source, node *p );
};


template <class Object>
class ListItr : public ConstListItr<Object>
{
  public:
    ListItr( );

    Object & operator* ( );
    const Object & operator* ( ) const;
    
    ListItr & operator++ ( );
    ListItr operator++ ( int );

    ListItr & operator-- ( );
    ListItr operator-- ( int );

  protected:
    typedef ListNode<Object> node;
    friend class list<Object>;

    ListItr( const list<Object> & source, node *p );
};

template<typename Object>
list<Object>::list()
{ 
    init(); 
}

template<typename Object>
void list<Object>::init()
{
    theSize=0;
    head= new node;
    tail =new node;
    head->next=tail;
    tail->prev=head;
}
template<typename Object>
list<Object>::~list()
{
    makeEmpty();
    delete head;
    delete tail;
}
template<typename Object>
void list<Object>::makeEmpty()
{
    while(!empty())
        pop_front();
}
template<typename Object>
list<Object>::list(const list<Object> &rhs)
{
    init();
    *this=rhs;
}
template <class Object>
const list<Object> & list<Object>::operator= ( const list & rhs )
{
    if( this == &rhs )
        return *this;
    makeEmpty( );
    for( const_iterator itr = rhs.begin( ); itr != rhs.end( ); ++itr )
        push_back( *itr );
    return *this;
}

template<typename Object>
typename list<Object>::iterator list<Object>::begin()
{
    iterator itr(*this, head);
    return ++itr;
}
template<typename Object>
typename list<Object>::const_iterator list<Object>::begin() const
{
    const_iterator itr(*this, head);
    return ++itr;
}
template<typename Object>
typename list<Object>::iterator list<Object>::end()
{
    return iterator(*this,tail);
}
template<typename Object>
typename list<Object>::const_iterator list<Object>::end() const
{
    return const_iterator(*this, tail);
}
template<typename Object>
int list<Object>::size() const
{
    return theSize;
}
template<typename Object>
bool list<Object>::empty() const
{
    return size()==0;
}
template<typename Object>
Object & list<Object>::front()
{
    return *begin();
}
template<typename Object>
const Object & list<Object>::front() const
{
    return *begin();
}
template<typename Object>
Object &list<Object>::back()
{
    return *--end();
}
template<typename Object>
const Object &list<Object>::back() const
{
    return *--end();
}
template<typename Object>
void list<Object>::push_front(const Object &x)
{
    insert(begin(),x);
}
template<typename Object>
void list<Object>::push_back(const Object &x)
{
    insert(end(), x);
}
template<typename Object>
void list<Object>::pop_front()
{
    erase(begin());
}
template<typename Object>
void list<Object>::pop_back()
{
    erase( --end());
}
template<typename Object>
typename list<Object>::iterator
list<Object>::insert( iterator itr, const Object &x)
{
    //itr.assertIsValid();
    //if(itr.head!= head)  throw IteratorMismatchException( );

    node *p= itr.current;
    p->prev->next=new node(x, p->prev,p);
    p->prev=p->prev->next;
    theSize++;
    return iterator(*itr, p->prev);
}
template<typename Object>
typename list<Object>::iterator
list<Object>::erase(iterator itr)
{
    itr.assertIsValid();
   // if(itr==end) throw IteratorOutOfBoundsException();
    //if(itr.head!=head) throw IteratorMismatchException( );

    node *p=itr.current;
    iterator retVal(*this,p->next);
    p->prev->next=p->next;
    p->next->prev=p->prev;
    delete p;
    theSize--;
    return retVal;
}
template<typename Object>
typename list<Object>::iterator
list<Object>::erase(iterator from, iterator to)
{
    for(iterator itr=from;itr!=to; )
        itr=erase(itr);
    return to;
}

// Public constructor for const_iterator.
template <class Object>
ConstListItr<Object>::ConstListItr( ) : head( NULL ), current( NULL )
{
}


// Throws an exception if this iterator is obviously
// uninitialized. Otherwise, returns safely.
template <class Object>
void ConstListItr<Object>::assertIsInitialized( ) const
{
    //if( head == NULL || current == NULL )
     //   throw IteratorUninitializedException( "list iterator" );
}


// Throws an exception if the current position is
// not somewhere in the range from begin to end, inclusive.
// Otherwise, returns safely.
template <class Object>
void ConstListItr<Object>::assertIsValid( ) const
{
    //assertIsInitialized( );
    //if( current == head )
    //    throw IteratorOutOfBoundsException( "At position prior to begin( ) in list" );
}


// Protected helper in const_iterator that returns the object
// stored at the current position. Can be called by all
// three versions of operator* without any type conversions.
template <class Object>
Object & ConstListItr<Object>::retrieve( ) const
{
    //assertIsValid( );
    //if( current->next == NULL )
     //   throw IteratorOutOfBoundsException( "Cannot perform *end( ) in list" );

    return current->data;
}


// Return the object stored at the current position.
// For const_iterator, this is an accessor with a
// const reference return type.
template <class Object>
const Object & ConstListItr<Object>::operator* ( ) const
{
    return this->retrieve( );
}


// Throws an exception if operator++ cannot be safely applied
// to the current position. Otherwise, returns safely.
template <class Object>
void ConstListItr<Object>::assertCanAdvance( ) const
{
    //assertIsInitialized( );
    //if( current->next == NULL )
    //    throw IteratorOutOfBoundsException( "Cannot perform ++end( ) in list" );
}


// Throws an exception if operator-- cannot be safely applied
// to the current position. Otherwise, returns safely.
template <class Object>
void ConstListItr<Object>::assertCanRetreat( ) const
{
    //assertIsValid( );
    //if( current->prev == head )
     //   throw IteratorOutOfBoundsException( "Cannot perform --begin( ) in list" );
}


template <class Object>
ConstListItr<Object> & ConstListItr<Object>::operator++ ( )
{
    assertCanAdvance( );
    current = current->next;
    return *this;
}


template <class Object>
ConstListItr<Object> ConstListItr<Object>::operator++ ( int )
{
    ConstListItr<Object> old = *this;
    ++( *this );
    return old;
}


template <class Object>
ConstListItr<Object> & ConstListItr<Object>::operator-- ( )
{
    assertCanRetreat( );
    current = current->prev;
    return *this;
}


template <class Object>
ConstListItr<Object> ConstListItr<Object>::operator-- ( int )
{
    ConstListItr<Object> old = *this;
    --( *this );
    return old;
}



template <class Object>
bool ConstListItr<Object>::operator== ( const ConstListItr & rhs ) const
{
    return current == rhs.current;
}


template <class Object>
bool ConstListItr<Object>::operator!= ( const ConstListItr & rhs ) const
{
    return !( *this == rhs );
}


// Protected constructor for const_iterator.
// Expects the list that owns the iterator and a
// pointer that represents the current position.
template <class Object>
ConstListItr<Object>::ConstListItr( const list<Object> & source, node *p )
  : head( source.head ), current( p )
{
}


// Public constructor for iterator.
// Calls the base-class constructor.
// Must be provided because the private constructor
// is written; otherwise zero-parameter constructor
// would be disabled.
template <class Object>
ListItr<Object>::ListItr( )
{
}


// Return the object stored at the current position.
// For iterator, there is an accessor with a
// const reference return type and a mutator with
// a reference return type. The accessor is shown first.
template <class Object>
const Object & ListItr<Object>::operator* ( ) const
{
    return ConstListItr<Object>::operator*( );
}


template <class Object>
Object & ListItr<Object>::operator* ( )
{
    return this->retrieve( );
}


template <class Object>
ListItr<Object> & ListItr<Object>::operator++ ( )
{
    this->assertCanAdvance( );
    this->current = this->current->next;
    return *this;
}


template <class Object>
ListItr<Object> ListItr<Object>::operator++ ( int )
{
    ListItr<Object> old = *this;
    ++( *this );
    return old;
}


template <class Object>
ListItr<Object> & ListItr<Object>::operator-- ( )
{
    this->assertCanRetreat( );
    this->current = this->current->prev;
    return *this;
}


template <class Object>
ListItr<Object> ListItr<Object>::operator-- ( int )
{
    ListItr<Object> old = *this;
    --( *this );
    return old;
}


// Protected constructor for iterator.
// Expects the list that owns the iterator and a
// pointer that represents the current position.
template <class Object>
ListItr<Object>::ListItr( const list<Object> & source, node *p )
  : ConstListItr<Object>( source, p )
{
}

int main()
{
    list<int> theList;
    list<int>::iterator p = theList.begin( );

    for(int i=0;i<10;i++)
        theList.insert(p,i);

   // while(!L.empty())
     //   cout<<L.pop_front() <<" ";

}