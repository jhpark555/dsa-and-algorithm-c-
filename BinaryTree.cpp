#include <iostream>
#include <vector>

using namespace std;

template<typename Object>
class TreeIterator;


template<typename Object>
class BinaryNode
{
    public:
        BinaryNode(const Object & theELement=Object(),
            BinaryNode *lt=NULL, BinaryNode *rt=NULL);

        static int size(BinaryNode *t);
        static int height(BinaryNode *t);

        void printPostOrder() const;
        void printInOrder() const;
        void printPreOrder() const;

        BinaryNode *duplicate() const;

    public:
        Object element;
        BinaryNode *left;
        BinaryNode *right;
};

template<typename Object>
class BinaryTree
{
    public:
        BinaryTree( ) : root( NULL ) { }
        BinaryTree( const Object & rootItem )
        : root( new Node( rootItem ) ) { }
        BinaryTree( const BinaryTree & rhs )
        : root( NULL ) { *this = rhs; }

        ~BinaryTree()
        { makeEmpty(); }
        const BinaryTree &operator=( const BinaryTree &rhs );

        void printPreOrder() const
            { if(root !=NULL) root->printPreOrder();}
        void printInOrder() const
            { if(root!=NULL) root->printInOrder(); }
        void printPostOrder() const
            { if(root!=NULL) root->printPostOrder(); }
        void makeEmpty()
            { makeEmpty(root); }
        bool isEmpty() const
            { return root==NULL; }
        int size() const
            { return Node::size(root); }
        int height() const
            { return Node::height(root); }
        void merge( const Object &rootItem, BinaryTree &t1, BinaryTree &t2);

    private:
        typedef BinaryNode<Object> Node;
        Node *root;

        friend class TreeIterator<Object>;
        void makeEmpty( Node * &t);

};

template<typename Object>
const BinaryTree<Object> &
BinaryTree<Object>::operator=(const BinaryTree<Object> &rhs)
{
    if(this !=&rhs)
    {
        makeEmpty();
        if(rhs.root!= NULL)
            root =rhs.root->duplicate();
    }

    return *this;
}

template<typename Object>
void BinaryTree<Object>::merge( const Object &rootItem,
    BinaryTree<Object> &t1, BinaryTree<Object> &t2)
{
    if(t1.root ==t2.root && t1.root !=NULL)
    {
        cerr<<"Cannot merge a tree with itself"<<endl;
        return;
    }

    Node *oldRoot =root;

    root = new Node( rootItem, t1.root, t2.root);

    if(this !=&t1 && this !=&t2)
        makeEmpty(oldRoot);
    
    if(this !=&t1)
        t1.root =NULL;
    if(this!=&t2)
        t2.root=NULL;
}

template<typename Object>
BinaryNode<Object> *BinaryNode<Object>::duplicate() const
{
    BinaryNode<Object> *root= new BinaryNode<Object>(element);

    if(left !=NULL) root->left=left->duplicate();
    if(right !=NULL) root->right =right->duplicate(); 

    return root;
}
template<typename Object>
void BinaryTree<Object>::makeEmpty(BinaryNode<Object> * &t)
{
    if( t!= NULL)
    {
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
        t=NULL;
    }
}
template<typename Object>
int BinaryNode<Object>::size(BinaryNode<Object> *t)
{
    if(t ==NULL)
        return 0;
    else
        return 1+size(t->left)+size(t->right);
    
}
template<typename Object>
int BinaryNode<Object>::height(BinaryNode<Object> *t)
{
    if(t==NULL) 
        return -1;
    else 
        return 1+ max(height(t->left),height(t->right));
}

template<typename Object>
void BinaryNode<Object>::printPreOrder() const
{
    cout<< element <<endl;
    if(left!=NULL)
        left->printPreOrder();
    if(right!=NULL)
        right->printPreOrder();
}
template<typename Object>
void BinaryNode<Object>::printPostOrder() const
{
    if(left!=NULL)
        left->printPostOrder();
    if(right!=NULL)
        right->printPostOrder();
    cout<< element<< endl;
}

template<typename Object>
void BinaryNode<Object>::printInOrder() const
{
    if(left!=NULL)
        left->printInOrder();
    cout<<element <<endl;
    if(right!=NULL)
        right->printInOrder();
}


template <class Object>
class Stack
{
  public:
    Stack( );
    Stack( const Stack & rhs );
    ~Stack( );

    bool isEmpty( ) const;
    const Object & top( ) const;

    void makeEmpty( );
    void pop( );
    void push( const Object & x );
    Object topAndPop( );

    const Stack & operator=( const Stack & rhs );

  private:
    struct ListNode
    {
        Object    element;
        ListNode *next;

        ListNode( const Object & theElement, ListNode * n = NULL )
          : element( theElement ), next( n ) { }
    };

    ListNode *topOfStack;
};

// Construct the stack.
template <class Object>
Stack<Object>::Stack( )
{
    topOfStack = NULL;
}

// Copy constructor.
template <class Object>
Stack<Object>::Stack( const Stack<Object> & rhs )
{
    topOfStack = NULL;
    *this = rhs;
}

// Destructor.
template <class Object>
Stack<Object>::~Stack( )
{
    makeEmpty( );
}

// Test if the stack is logically empty.
// Return true if empty, false, otherwise.
template <class Object>
bool Stack<Object>::isEmpty( ) const
{
    return topOfStack == NULL;
}

// Make the stack logically empty.
template <class Object>
void Stack<Object>::makeEmpty( )
{
    while( !isEmpty( ) )
        pop( );
}

// Return the most recently inserted item in the stack.
// or throw an UnderflowException if empty.
template <class Object>
const Object & Stack<Object>::top( ) const
{
    return topOfStack->element;
}

// Remove the most recently inserted item from the stack.
// Throw Underflow if the stack is empty.
template <class Object>
void Stack<Object>::pop( )
{

    ListNode *oldTop = topOfStack;
    topOfStack = topOfStack->next;
    delete oldTop;
}

// Return and remove the most recently inserted item
// from the stack.
template <class Object>
Object Stack<Object>::topAndPop( )
{
    Object topItem = top( );
    pop( );
    return topItem;
}

// Insert x into the stack.
template <class Object>
void Stack<Object>::push( const Object & x )
{
    topOfStack = new ListNode( x, topOfStack );
}

// Deep copy.
template <class Object>
const Stack<Object> & Stack<Object>::operator=( const Stack<Object> & rhs )
{
    if( this != &rhs )
    {
        makeEmpty( );
        if( rhs.isEmpty( ) )
            return *this;

        ListNode *rptr = rhs.topOfStack;
        ListNode *ptr  = new ListNode( rptr->element );
        topOfStack = ptr;

        for( rptr = rptr->next; rptr != NULL; rptr = rptr->next )
            ptr = ptr->next = new ListNode( rptr->element );
    }
    return *this;
}


template<typename Object>
class TreeIterator
{
    public:
        TreeIterator( const BinaryTree<Object> &theTree)
            :root (theTree.root), current(NULL) {}
        virtual ~TreeIterator() {}

        virtual void first() =0;   
        bool isValid() const 
        { return current!=NULL; }
        const Object &retrieve() const;
        virtual void advance() =0;

    public:
        const BinaryNode<Object> *root;
        const BinaryNode<Object> *current;

};

template<typename Object>
const Object & TreeIterator<Object>::retrieve() const
{
    return current->element;
}

template<typename Object>
struct StNode
{
    const BinaryNode<Object> *node;
    int timesPopped;
    StNode( const BinaryNode<Object> *n=0 )
     : node (n), timesPopped (0)   {}
};


template <class Object>
class PreOrder: public TreeIterator<Object>
{
  public:
    PreOrder( const BinaryTree<Object> & theTree );
    ~PreOrder( ) { }

    void first( );
    void advance( );
  protected:
    Stack< const BinaryNode<Object> * > s;
};


////////// POSTORDER

template<typename Object>
class PostOrder: public TreeIterator<Object>
{
    public:
        PostOrder( const BinaryTree<Object> &theTree);
        ~PostOrder() {}
        void first();
        void advance();
    protected:
        Stack<StNode<Object>> s;
};


template <class Object>
class InOrder : public PostOrder<Object>
{
    // Accept PostOrder construction and default destruction.

  public:
    InOrder( const BinaryTree<Object> & theTree )
      : PostOrder<Object>( theTree ) { }
    void advance( );
};

template<typename Object>
PostOrder<Object>::PostOrder(const BinaryTree<Object> &theTree)
: TreeIterator<Object>(theTree)
{
    s.push(StNode<Object>(this->root));
}
template<typename Object>
void PostOrder<Object>::first()
{
    s.makeEmpty();
    if(this->root !=NULL)
    {
        s.push(StNode<Object>(this->root));
        advance();
    }
}
template<typename Object>
void PostOrder<Object>::advance()
{
    if(s.isEmpty())
    {
        this->current= NULL;
        return;
    }
    StNode <Object> cnode;
    for(;;)
    {
        cnode =s.topAndPop();
        if( ++cnode.timesPopped == 3 )
        {
            this->current = cnode.node;
            return;
        }

        s.push( cnode );
        if( cnode.timesPopped == 1 )
        {
            if( cnode.node->left != NULL )
                s.push( StNode<Object>( cnode.node->left ) );
        }
        else  // cnode.timesPopped == 2
        {
            if( cnode.node->right != NULL )
                s.push( StNode<Object>( cnode.node->right ) );
        }
                
    }
}

//////////// PREORDER
// Constructor.
template <class Object>
PreOrder<Object>::PreOrder( const BinaryTree<Object> & theTree )
  : TreeIterator<Object>( theTree )
{
    s.push( this->root );
}
// Set the current position to the first.
template <class Object>
void PreOrder<Object>::first( )
{
    s.makeEmpty( );
    if( this->root != NULL )
    {
        s.push( this->root );
        advance( );
    }
}
template <class Object>
void PreOrder<Object>::advance( )
{
    if( s.isEmpty( ) )
    {
        this->current = NULL;
        return;
    }

    this->current = s.topAndPop( );
    if( this->current->right != NULL )
        s.push( this->current->right );
    if( this->current->left != NULL )
        s.push( this->current->left );
}

////////// INORDER

// Advance to the next position.
// Throw BadIterator exception if the iteration has been
// exhausted prior to the call.
template <class Object>
void InOrder<Object>::advance( )
{

    if( this->s.isEmpty( ) )
    {
        this->current = NULL;
        return;
    }

    StNode<Object> cnode;

    for( ; ; )
    {
        cnode = this->s.topAndPop( );
    
        if( ++cnode.timesPopped == 2 )
        {
            this->current = cnode.node;
            if( cnode.node->right != NULL )
                this->s.push( StNode<Object>( cnode.node->right ) );
            return;
        }
    
          // First time through
        this->s.push( cnode );
        if( cnode.node->left != NULL )
            this->s.push( StNode<Object>( cnode.node->left ) );
    }
}


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
    //if(isEmpty()) return -1;

    currentSize--;

    Object frontitem = theArray[front];
    increment(front);

    return frontitem;
}

template<typename Object>
const Object & Queue<Object>:: getFront() const
{
    //if(isEmpty()) return -1;

    return theArray[front];
}

template<typename Object>
void Queue<Object>::makeEmpty()
{
    currentSize =0;
    front =0;
    back = theArray.size() -1;
}


template <class Object>
class LevelOrder : public TreeIterator<Object>
{
  public:
    LevelOrder( const BinaryTree<Object> & theTree );
    ~LevelOrder( ) { }

    void first( );
    void advance( );

  private:
    Queue< const BinaryNode<Object> * > q;
};

////////// LEVEL ORDER

// Constructor.
template <class Object>
LevelOrder<Object>::LevelOrder( const BinaryTree<Object> & theTree )
  : TreeIterator<Object>( theTree )
{
    q.enqueue( this->root );
}

// Set the this->current position to the first.
template <class Object>
void LevelOrder<Object>::first( )
{
    q.makeEmpty( );
    if( this->root != NULL )
    {
        q.enqueue( this->root );
        advance( );
    }
}

// Advance to the next position.
// Throw BadIterator exception if the iteration has been
// exhausted prior to the call.
template <class Object>
void LevelOrder<Object>::advance( )
{
    if( q.isEmpty( ) )
    {
        this->current = NULL;
        return;
    }

    this->current = q.getFront( );
    q.dequeue( );

    if( this->current->left != NULL )
        q.enqueue( this->current->left );
    if( this->current->right != NULL )
        q.enqueue( this->current->right );
}
template <class Object>
void testItr( TreeIterator<Object> & itr )
{
   // try
   // {
        for( itr.first( ); itr.isValid( ); itr.advance( ) )
            cout << itr.retrieve( ) << "*";
        cout << endl;
   // }
   // catch( BadIterator & e )
    //  { cout << e.toString( ) << endl; }
}
int main( )
{
    BinaryTree<int> t1( 1 );
    BinaryTree<int> t3( 3 );
    BinaryTree<int> t5( 5 );
    BinaryTree<int> t7( 7 );
    BinaryTree<int> t2;
    BinaryTree<int> t4;
    BinaryTree<int> t6;

    t2.merge( 2, t1, t3 );
    t6.merge( 6, t5, t7 );
    t4.merge( 4, t2, t6 );

    cout << "t4 should be perfect 1-7; t2 empty" << endl;
    cout << "----------------" << endl;
    cout << "t4 -- in, post, pre, twice each, level once" << endl;
    InOrder<int> i4( t4 );
    PostOrder<int> po4( t4 );
    PreOrder<int> pr4( t4 );
    LevelOrder<int> l4( t4 );
    t4.printInOrder( ); testItr( i4 );
    cout << "----------------" << endl;
    t4.printPostOrder( ); testItr( po4 );
    cout << "----------------" << endl;
    t4.printPreOrder( ); testItr( pr4 );
    cout << "----------------" << endl;
    testItr( l4 );
    cout << "----------------" << endl;


    return 0;
}