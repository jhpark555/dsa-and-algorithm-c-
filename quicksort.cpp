#include <iostream>
#include <vector>

using namespace std;

template <typename Comparable>
void quicksort( vector<Comparable> &a, int left, int right);

template <typename Comparable>
void quickSelect( vector<Comparable> &a, int left, int right,int k);


template <typename Comparable>
void SORT( vector<Comparable> &items)
{
  if(items.size() >1)
  {
    vector< Comparable> smaller;
    vector< Comparable> same;
    vector< Comparable> larger;

    auto chosenItem = items[items.size()/2];

    for( auto &i : items)
    {
        if(i< chosenItem)
            smaller.push_back(move(i));
        else if( i> chosenItem)
            larger.push_back(move(i));
        else 
            same.push_back(move(i));
    }

    SORT(smaller);
    SORT(larger);

    move(begin(smaller),end(smaller),begin(items));
    move(begin(same),end(same), begin(items)+smaller.size());
    move(begin(larger),end(larger),end(items)-larger.size());
  }
}

template<typename Comparable>
void insertionSort(vector<Comparable> & a,int left,int right)
{
    for(int p=left;p< right; ++p)
    {
        Comparable tmp=move(a[p]);

        int j;
        for( j=p; j>0 && tmp< a[j-1]; --j)
            a[j]=move(a[j-1]);
        a[j]=move(tmp);
    }
}


template <typename Comparable>
void quicksort(vector<Comparable> &a)
{
    quicksort(a,0,a.size()-1);
    //quickSelect(a,0,a.size()-1,0);
}

template <typename Comparable>
const Comparable &median3( vector<Comparable> &a, int left , int right)
{
    int center = (left+right) /2;

    if(a[center]< a[left])
        swap(a[left],a[center]);
    if(a[right]<a[left])
        swap(a[left],a[right]);
    if(a[right]<a[center])
        swap(a[right],a[center]);

    swap(a[center],a[right-1]);  //place pivot at right-1
    return a[right-1];
}

template <typename Comparable>
void quicksort( vector<Comparable> &a, int left, int right)
{
    if(left+1<=right)
    {
        const Comparable &pivot = median3(a,left,right);

        int i=left, j=right-1;

        for(;;)
        {
            while( a[++i]< pivot);
            while(pivot<a[--j]) ;
            if(i<j) swap(a[i],a[j]);
            else break;
        }
        swap(a[i],a[right-1]);  //restore pivot

        quicksort(a,left,i-1);  //sort small
        quicksort(a,i+1,right); //sort large

    }
    else 
    insertionSort(a,left,right);
}


template <typename Comparable>
void quickSelect( vector<Comparable> &a, int left, int right,int k)
{
    if(left+1<=right)
    {
        const Comparable &pivot = median3(a,left,right);

        int i=left, j=right-1;

        for(;;)
        {
            while( a[++i]< pivot);
            while(pivot<a[--j]) ;
            if(i<j) swap(a[i],a[j]);
            else break;
        }
        swap(a[i],a[right-1]);  //restore pivot

        if(k<=i)
        quickSelect(a,left,i-1,k);  //sort small
        else if(k> i+1)
        quickSelect(a,i+1,right,k); //sort large

    }
    else 
    insertionSort(a,left,right);
}



int main()
{
    vector<int> a={8,1,4,9,6,3,5,2,7,0};

    //SORT(a);
    quicksort(a);

    for(int i=0;i <a.size(); i++)
        cout<< a[i]<<" ";

    return 0;
}