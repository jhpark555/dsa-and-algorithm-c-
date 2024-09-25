#include <iostream>
#include <vector>

using namespace std;

#if 0
template<typename Comparable>
void insertionSort(vector<Comparable> & a)
{
    for(int p=1;p< a.size(); ++p)
    {
        Comparable tmp=move(a[p]);

        int j;
        for( j=p; j>0 && tmp< a[j-1]; --j)
            a[j]=move(a[j-1]);
        a[j]=move(tmp);
    }
}
#endif
template<typename Iterator, typename Comparator>
void insertionSort(const Iterator& begin, const Iterator &end, Comparator lessThan)
{
    if(begin==end) return;

    Iterator j;

    for(Iterator p=begin+1; p!=end; ++p)
    {
        auto tmp= move(*p);
        for(j =p; j!=begin && lessThan(tmp,*(j-1));--j)
            *j=move(*(j-1));
        *j=move(tmp);
    }
}


template<typename Iterator>
void insertionSort( const Iterator &begin, const Iterator &end)
{
    insertionSort(begin,end,less<decltype(*begin)>{});
}

template<typename Comparable>
void Shellsort(vector<Comparable> &a)
{
    for(int gap=a.size()/2; gap> 0; gap /=2)
    {
        for( int i=gap; i<a.size(); i++)
        {
            Comparable tmp=move(a[i]);
            int j=i;

            for(; j>=gap && tmp< a[j-gap]; j -=gap)
                a[j]=move(a[j-gap]);
            a[j]=move(tmp);
        }
    }
}

int main()
{
    vector<int> a={9,8,7,6,5,4,3,2,1};

    //insertionSort(a);
    //insertionSort(begin(a),end(a));
    Shellsort(a);

    for(int i=0;i<a.size();i++)
        cout<<a[i]<<" ";

    return 0;
}