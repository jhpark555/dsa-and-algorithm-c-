#include <iostream>
#include <vector>

using namespace std;

class Rectangle
{
    public:
        Rectangle(int len=0, int wid=0)
        : length(len), width(wid) {}

        int getLength() const
        { return length;}

        int getWidth() const
        { return width;}

        void print(ostream &out=cout) const
        { out<< "Rectangle "<< getLength() <<" by " << getWidth();}

    private:
        int length;
        int width;

};

ostream &operator<<(ostream &out, const Rectangle &rhs)
{
    rhs.print(out);
    return out;
}
class LessThanByLength
{
    public:
        bool operator() (const Rectangle &lhs, const Rectangle &rhs) const
        { return lhs.getLength() < rhs.getLength();}
};
class LessThanByArea
{
    public:
        bool operator()(const Rectangle &lhs, const Rectangle &rhs) const
        { return lhs.getLength()*rhs.getWidth() <
          rhs.getLength()*rhs.getWidth();}
};

template<typename Object,typename Comparator>
const Object &findMax(const vector<Object>& a, Comparator func)
{
    int maxIndex=0;

    for( int i=0; i< a.size(); i++)
       if ( func(a[maxIndex],a[i]))
            maxIndex =i;

    return a[maxIndex];
}

int main()
{
    vector<Rectangle> a;

    a.push_back( Rectangle( 1, 10 ) );
    a.push_back( Rectangle( 10, 1 ) );
    a.push_back( Rectangle( 5, 5 ) );
    a.push_back( Rectangle( 4, 6 ) );

    cout << "Largest length:\n\t" << findMax( a, LessThanByLength( ) ) << endl;
    cout << "Largest area:\n\t" << findMax( a, LessThanByArea( ) ) << endl;

    return 0;
}



