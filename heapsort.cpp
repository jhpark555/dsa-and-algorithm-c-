#include <iostream>
#include <vector>

using namespace std;

template<typename Comparable>
void percDown( vector<Comparable> &a, int i,int n);

template<typename Comparable>
void heapsort( vector<Comparable> & a)
{
    for(int i=a.size()/2-1; i>=0; --i)
        percDown(a,i,a.size());
    for(int j=a.size()-1 ; j>0; --j)
    {
        swap(a[0],a[j]);
        percDown(a,0,j);
    }
}
int leftChild(int i)
{
    return 2*i+1;
}
template<typename Comparable>
void percDown( vector<Comparable> &a, int i,int n)
{
    int child;
    Comparable tmp;

    for(tmp =move(a[i]); leftChild(i)< n; i=child)
    {
        child = leftChild(i);
        if(child!=n-1 && a[child]< a[child+1])
            ++child;
        //printf("*tmp=%d child=%d \n",tmp,a[child]);
        if(tmp< a[child])
            a[i]=move(a[child]);
        else
            break;
    }
    a[i]=move(tmp);
}

int main()
{
    vector<int> a={97,53,59,26,41,58,31};
    heapsort(a);

    for(int i=0;i<a.size(); i++)
       cout<< a[i]<<" ";
    return 0;
}