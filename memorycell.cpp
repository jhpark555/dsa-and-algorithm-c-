#include <iostream>

using namespace std;

template< class Object>
class MemoryCell
{
    public:
        explicit MemoryCell(const Object &initVal=Object() )
        : storedValue(initVal) {}

        const Object &read() const
        { return storedValue;}
        void write(const Object &x)
        { storedValue=x; }
    private:
        Object storedValue;

};

int main()
{
    MemoryCell<int> m;
    m.write(5);
    cout<<"Cell contents are "<<m.read() <<endl;

    return 0;
}