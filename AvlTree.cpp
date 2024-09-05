#include <algorithm>
#include <iostream>

using namespace std;

template<typename Comparable>
class AvlTree
{
    public:
        AvlTree(): root{nullptr}
        {}
        AvlTree(const AvlTree &rhs): root{nullptr}
        {
            root = clone(rhs.root);
        }
        AvlTree(AvlTree&& rhs): root{nullptr}
        {
            rhs.root=nullptr;
        }
        ~AvlTree()
        {
            makeEmpty();
        }
        AvlTree & operator=(const AvlTree &rhs)
        {
            AvlTree copy=rhs;
            swap(*this,copy);
            return *this;
        }
        AvlTree &operator=( AvlTree &&rhs)
        {
            swap(root,rhs.root);
            return *this;
        }
        const Comparable& findMin() const
        {
            return findMin(root)->element;
        }
        const Comparable findMax() const
        {
            return findMax(root)->element;
        }
        bool contains(const Comparable& x) const
        {
            return contains(x,root);
        }
        bool isEmpty() const
        {
            return root==nullptr;
        }
        void printTree() const
        {
            if(isEmpty()) cout<<"Empty "<<endl;
            else printTree(root);
        }
        void makeEmpty()
        {
            makeEmpty(root);
        }
        void insert(const Comparable& x)
        {
            insert(x,root);
        }
        void insert(Comparable &&x)
        {
            insert(move(x),root);
        }
        void remove(const Comparable& x)
        {
            remove(x,root);
        }
    private:
        struct AvlNode
        {
            Comparable element;
            AvlNode *left;
            AvlNode *right;
            int height;
            AvlNode(const Comparable &ele,AvlNode *lt,AvlNode*rt,int h=0):
            element{ele},left{lt},right{rt},height{h}{}
            AvlNode(Comparable &&ele,AvlNode *lt,AvlNode*rt,int h=0):
            element{move(ele)},left{lt},right{rt},height{h}{}
        };
        AvlNode *root;
        void insert(const Comparable &x, AvlNode * &t)
        {
            if(t==nullptr) 
                t= new AvlNode{x,nullptr,nullptr};
            else if(x< t->element)
                insert(x,t->left);
            else if(x>t->element)
                insert(x,t->right);
            
            balance(t);
        }

        void remove(const Comparable& x, AvlNode* &t)
        {
            if(t==nullptr) return;

            if(x< t->element)
                remove(x,t->left);
            else if (x> t->element)
                remove(x,t->right);
            else if (t->left !=nullptr && t->right!=nullptr)
            {
                t->element= findMin(t->right)->element;
                remove(t->element,t->right);
            }
            else
            {
                AvlNode *oldNode=t;
                t=( t->left!=nullptr)? t->left:t->right;
                delete oldNode;
            }
            balance(t);
        }
        static const int ALLOWED_IMBALANCE =1;

        void balance(AvlNode * &t)
        {
            if( t==nullptr) return;

            if(height(t->left)-height(t->right) > ALLOWED_IMBALANCE)   //>1
            {
                if(height(t->left->left)>= height(t->left->right))
                    rotateWithLeftChild(t);   //rotate right
                else    
                    doubleWithLeftChild(t);   //rotate left->right 
            }
            else if(height(t->right)-height(t->left)> ALLOWED_IMBALANCE)
            {
                if(height(t->right->right)>=height(t->right->left))
                    rotateWithRightChild(t);     // totate left
                else 
                    doubleWithRightChild(t);    //rotate right left
            }

            t->height=max(height(t->left),height(t->right)) +1;
        }

        AvlNode *findMin(AvlNode *t) const
        {
            if(t==nullptr) return nullptr;
            if(t->left==nullptr)  return t;

            return findMin(t->left);
        }
        AvlNode* findMax(AvlNode *t) const
        {
            if(t!=nullptr)
                while(t->right!=nullptr)
                    t=t->right;
            return t;
        }
        bool contains(const Comparable &x,AvlNode *t) const
        {
        #if 0
            if(t==nullptr) return false;
            else if( x< t->element)
                return contains(x,t->left);
            else if( x> t->element)
                return contains(x,t->right);
            else 
                true;
        #else
            while(t!=nullptr)
            {
                if(x< t->element) t=t->left;
                else if(x> t->element) t= t->right;
                else 
                    return true;
            }
            return false;
        #endif
        }

        void makeEmpty(AvlNode *&t)
        {
            if(t!=nullptr)
            {
                makeEmpty(t->left);
                makeEmpty(t->right);
                delete t;
            }
            t=nullptr;
        }

        void printTree(AvlNode *t) const
        {
            if(t!=nullptr)
            {
                printTree(t->left);
                cout<< t->element<<" ";
                printTree(t->right);
            }
        }
        AvlNode *clone(AvlNode *t) const
        {
            if(t==nullptr) return nullptr;
            else 
                return new AvlNode{t->element,clone(t->left),clone(t->right),
                t->height};
        }
        int height(AvlNode *t) const
        {
            return t==nullptr ? -1:t->height;
        }
        int max(int lhs,int rhs) const
        {
            return lhs> rhs? lhs:rhs;
        }

        void rotateWithLeftChild(AvlNode * &k2)
        {
            AvlNode *k1=k2->left;
            k2->left=k1->right;
            k1->right= k2;
            k2->height=max(height(k2->left), height(k2->right)) +1;
            k1->height=max(height(k1->left), k2->height)+1;
            k2=k1;      //new root k2->k1
        }
        void rotateWithRightChild(AvlNode *&k1)
        {
            AvlNode *k2= k1->right;
            k1->right=k2->left;
            k2->left=k1;
            k1->height= max(height(k1->left),height(k1->right))+1;
            k2->height =max(height(k2->left), k1->height) +1;
            k1=k2;    //new root
        }
        void doubleWithLeftChild(AvlNode * & k3)
        {
            rotateWithRightChild(k3->left);
            rotateWithLeftChild(k3);
        }
        void doubleWithRightChild(AvlNode *&k1)
        {
            rotateWithLeftChild(k1->right);
            rotateWithRightChild(k1);
        }
};

int main()
{
    AvlTree<int> t;
        int NUMS = 10;//2000000;
    const int GAP  =   1;//37;
    int i;

    cout << "Checking... (no more output means success)" << endl;

    for( i = GAP; i != 0; i = ( i + GAP ) % NUMS )
        t.insert( i );
    t.remove( 0 );
    for( i = 1; i < NUMS; i += 2 )
        t.remove( i );

    if( NUMS < 40 )
        t.printTree( );
    if( t.findMin( ) != 2 || t.findMax( ) != NUMS - 2 )
        cout << "FindMin or FindMax error!" << endl;

    for( i = 2; i < NUMS; i += 2 )
        if( !t.contains( i ) )
            cout << "Find error1!" << endl;

    for( i = 1; i < NUMS; i += 2 )
    {
        if( t.contains( i )  )
            cout << "Find error2!" << endl;
    }

    AvlTree<int> t2;
    t2 = t;

    for( i = 2; i < NUMS; i += 2 )
        if( !t2.contains( i ) )
            cout << "Find error1!" << endl;

    for( i = 1; i < NUMS; i += 2 )
    {
        if( t2.contains( i ) )
            cout << "Find error2!" << endl;
    }

    cout << "\nEnd of test..." << endl;
    return 0;

}