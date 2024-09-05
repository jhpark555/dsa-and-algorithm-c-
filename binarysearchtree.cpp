#include <iostream>
#include <algorithm>

using namespace std;

template<typename Comparable>
class BinarySearchTree
{
    public:
        BinarySearchTree() : root{nullptr}{}
        BinarySearchTree( const BinarySearchTree& rhs): root{nullptr}
        {
            root=clone(rhs.root);
        }
        BinarySearchTree(BinarySearchTree &&rhs): root{rhs.root}
        {
            rhs.root=nullptr;
        }
        ~BinarySearchTree()
        {
            makeEmpty();
        }

        BinarySearchTree &operator=(const BinarySearchTree &rhs)
        {
            BinarySearchTree copy=rhs;
            swap(*this,copy);
            return *this;
        }
        BinarySearchTree &operator=(BinarySearchTree &&rhs)
        {
            swap(root,rhs.root);
            return *this;
        }

        const Comparable &findMin() const
        {
            return findMin(root)->element;
        }
        const Comparable &findMax() const
        {
            return findMax(root)->element;
        }
        bool contains(const Comparable &x) const
        {
            return contains(x,root);
        }
        bool isEmpty() const
        {
            return root==nullptr;
        }
        void printTree(ostream &out= cout) const
        {
            if(isEmpty()) out<<"Empty Tree"<<endl;
            else
              printTree(root,out);
        }

        void makeEmpty()
        {
            makeEmpty(root);
        }
        void insert(const Comparable &x)
        {
            insert(x,root);
        }
        void insert(Comparable &&x)
        {
            insert( move(x),root);
        }
        void remove(const Comparable &x )
        {
            remove(x,root);
        }        

    private:
        struct BinaryNode{
            Comparable element;
            BinaryNode *left;
            BinaryNode *right;

            BinaryNode(const Comparable & theElement,BinaryNode *lt,
            BinaryNode *rt): element{theElement},left{lt},right{rt}{}
            BinaryNode( Comparable && theElement,BinaryNode *lt,
            BinaryNode *rt): element{move(theElement)},left{lt},right{rt}{}
        };

        BinaryNode *root;

        void insert(const Comparable &x, BinaryNode *&t)
        {
            if(t == nullptr) 
                t= new BinaryNode{x,nullptr,nullptr};
            else if( x< t->element)
                insert(x,t->left);
            else if(x> t->element)
                insert(x,t->right);
            else
                ; //do nothing.
        }
        void insert(Comparable &&x,BinaryNode *&t)
        {
            if(t == nullptr) 
                t= new BinaryNode{move(x),nullptr,nullptr};
            else if( x< t->element)
                insert(move(x),t->left);
            else if(x> t->element)
                insert(move(x),t->right);
            else
                ; //do nothing.
        }
        void remove(const Comparable& x,BinaryNode *&t)
        {
            if(t ==nullptr) return;
            if(x< t->element)
                remove(x,t->left);
            else if(x > t->element)
                remove(x,t->right);
            else if( t->left !=nullptr && t->right !=nullptr)
            {
                t->element= findMin(t->right)->element;
                remove(t->element,t->right);
            }
            else     //one of children is null
            {
                BinaryNode *oldNode=t;
                t=(t->left !=nullptr)? t->left:t->right;
                delete oldNode;
            }
        }
        BinaryNode *findMin(BinaryNode *t) const
        {
            if(t==nullptr) return nullptr;
            if(t->left==nullptr)
                return t;
            return findMin(t->left);
        }
        BinaryNode *findMax(BinaryNode *t) const
        {
            if(t!=nullptr)
                while( t->right!=nullptr) t=t->right;
            return t;
        }
        bool contains(const Comparable &x, BinaryNode *t) const
        {
            #if 0
            if(t==nullptr) return false;
            else if(x<t->element) 
                return contains(x,t->left);
            else if(x> t->element)
                return contains(x,t->right);
            else 
                return true;    //match
            #else
            while(t!=nullptr)
            {
                if(x<t->element) t=t->left;
                else if( x> t->element) t=t->right;
                else
                    return true;
            }
                return false;
            #endif
        }
        void makeEmpty(BinaryNode *&t)
        {
            if(t!=nullptr)
            {
                makeEmpty(t->left);
                makeEmpty(t->right);
                delete t;
            }
            t=nullptr;
        }
        void printTree(BinaryNode *t,ostream &out)const
        {
            if(t!=nullptr)
            {
                printTree(t->left,out);
                out<<t->element<<endl;
                printTree(t->right,out);
            }
        }
        BinaryNode *clone(BinaryNode *t) const
        {
            if(t==nullptr) return nullptr;
            else
                return new BinaryNode{ t->element,clone(t->left),clone(t->right)};
        }

};

int main()
{
    BinarySearchTree<int> t;
    int NUMS = 10;//400000;
    int i;
    const int GAP= 1;//3711;
    cout << "Checking... (no more output means success)" << endl;

    for( i = GAP; i != 0; i = ( i + GAP ) % NUMS )
        t.insert( i );

     t.printTree( );

    for( i = 1; i < NUMS; i+= 2 )
        t.remove( i );

    if( NUMS < 40 )
        t.printTree( );
    if( t.findMin( ) != 2 || t.findMax( ) != NUMS - 2 )
        cout << "FindMin or FindMax error!" << endl;

    for( i = 2; i < NUMS; i+=2 )
        if( !t.contains( i ) )
            cout << "Find error1!" << endl;

    for( i = 1; i < NUMS; i+=2 )
    {
        if( t.contains( i ) )
            cout << "Find error2!" << endl;
    }

#if 1
    BinarySearchTree<int> t2;
    t2 = t;

    for( i = 2; i < NUMS; i+=2 )
        if( !t2.contains( i ) )
            cout << "Find error1!" << endl;

    for( i = 1; i < NUMS; i+=2 )
    {
        if( t2.contains( i ) )
            cout << "Find error2!" << endl;
    }

    cout << "Finished testing" << endl;

#endif

    return 0;

}
