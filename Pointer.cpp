#include <iostream>

using namespace std;

template<typename Object>
class Cref
{
    public:
        Cref(): obj(NULL) {}
        explicit Cref(const Object &x) : obj( &x) {}

        const Object &get() const
        { if(isNull() ) cout<<"NULL"; /*throw NullPointerException(); */else return *obj; }

        bool isNull() const
        { return obj ==NULL; }

    private:
        const Object *obj;
};

template<typename Comparable>
class Pointer
{
    public:
        explicit Pointer(Comparable *rhs=NULL) : pointee(rhs) {}

        bool operator<(const Pointer &rhs ) const
        { return *pointee< *rhs.pointee;}
        operator Comparable *() const
        { return pointee; }
        Comparable *get() const
        { return pointee; }

    private:
        Comparable *pointee;
};

// Program that illustrates ambiguities that can develop with
// dual-direction implicit type conversions.
bool operator!= ( const Pointer<int> & lhs, const Pointer<int> & rhs )
{
    return lhs < rhs || rhs < lhs;
}

// Class that wraps a local pointer variable.
template <typename  Object>
class AutoPointer
{
  public:
    explicit AutoPointer( Object *rhs = NULL )
      : isOwner( rhs != NULL ), pointee( rhs ) { }
    AutoPointer( AutoPointer & rhs ) : isOwner( rhs.isOwner )
      { pointee = rhs.release( ); }

    ~AutoPointer( )
      { free( ); }

    const AutoPointer & operator= ( AutoPointer & rhs )
    {
        if( this != &rhs )
        {
            Object *other = rhs.get( );
            if( other != pointee )        // Different pointees, so
            {
                free( );                  // Give up current pointer
                isOwner = rhs.isOwner;    // Assume ownership
            }
            else if( rhs.isOwner )        // Same pointers
                isOwner = true;           // If rhs owned it, now I do
            pointee = rhs.release( );     // Copy pointee, rhs gives up ownership
        }
        return *this;
    }

    Object & operator* ( ) const
      { return *get( ); }
    Object * operator->( ) const
      { return get( ); }

    Object * get( ) const
      { return pointee; }
    Object * release( )
      { isOwner = false; return pointee; }

  private:
    Object *pointee;
    bool isOwner;

    void free( )
      { if( isOwner ) delete pointee; }
};

// Test program: Use an Integer class with a noisy destructor.

struct Integer
{
   Integer( int a ) : x( a ) { }

   ~Integer( ) { cout << "DESTRUCT " << x << endl; }

   int x;
};


int main( )
{
    int *p = new int( 3 );
    Pointer<int> q( new int( 4 ) );
    if( q != p ) { // Compare pointed-at objects???
        cout << "q and p are different" << endl;
    }


    AutoPointer<Integer> p1( new Integer( 3 ) );
    AutoPointer<Integer> p2 = p1;
    AutoPointer<Integer> p3;

    cout << (*p1).x << " " << (*p2).x << endl;
    p3 = p1;
    cout << p1->x << " " << p2->x << " " << p3->x << endl;
    // 3 is owned by p2.

    AutoPointer<Integer> p4( new Integer( 4 ) );
    cout << p1->x << " " << p2->x << " " << p3->x << " " << p4->x << endl;
    p2 = p4;

    cout << "3 is no longer owned! p1 and p3 are stale!!!" << endl;
    cout << p2->x << " " << p4->x << endl;

    return 0;
}