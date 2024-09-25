#include <iostream>
#include <vector>

using namespace std;

template<typename Object>
class VectorIterator;

template<typename Object>
class MyVector: public vector<Object>
{
    public:
        explicit MyVector(int size=0)
        : vector<Object>(size) {}

        VectorIterator<Object> getIterator() const
        { return VectorIterator<Object> (this); }
};

template<typename Object>
class VectorIterator
{
    public:
        VectorIterator(const MyVector<Object> *v):
        owner(v), count(0) {}

        bool hasNext() const
        { return count !=owner->size();}
        const Object &next()
        { return (*owner)[count++]; }

    private:
        const MyVector<Object> *owner;
        int count;

};

int main()
{
    MyVector<int> v;

    v.push_back(3);
    v.push_back(2);
    cout<<"Vector contents: "<< endl;

    VectorIterator<int> itr= v.getIterator();
    while(itr.hasNext() )
        cout<<itr.next() <<endl;

    return 0;
}