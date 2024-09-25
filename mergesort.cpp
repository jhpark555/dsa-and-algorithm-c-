#include <iostream>
#include <vector>

using namespace std;

template<typename Comparable>
void mergeSort(vector<Comparable> &a, vector<Comparable> &tmpArray,int left,int right);

template<typename Comparable>
void merge(vector<Comparable>&a,vector<Comparable>& tmpArray,
    int leftPos,int rightPos, int rightEnd);

template<typename Comparable>
void mergeSort( vector<Comparable> &a)
{
    vector<Comparable> tmpArray(a.size());
    mergeSort(a,tmpArray,0 ,a.size()-1);
}

template<typename Comparable>
void mergeSort(vector<Comparable> &a, vector<Comparable> &tmpArray,int left,int right)
{
    if(left< right)
    {
        int center =(left+right) /2;
        mergeSort(a,tmpArray,left,center);
        mergeSort(a,tmpArray,center+1,right);
        merge(a,tmpArray,left,center+1,right);
    }
}

template<typename Comparable>
void merge(vector<Comparable>&a,vector<Comparable>& tmpArray,
    int leftPos,int rightPos, int rightEnd)
{
    int leftEnd=rightPos-1;
    int tmpPos= leftPos;
    int numElements= rightEnd-leftPos+1;

    while(leftPos <= leftEnd && rightPos <=rightEnd)
        if(a[leftPos] <= a[rightPos])
            tmpArray[tmpPos++]= move(a[leftPos++]);
        else
            tmpArray[tmpPos++]= move(a[rightPos++]);

    while( leftPos<=leftEnd)
        tmpArray[tmpPos++]= move(a[leftPos++]);
    while( rightPos<=rightEnd)
        tmpArray[tmpPos++]= move(a[rightPos++]);

    for(int i=0; i< numElements; ++i,--rightEnd)
        a[rightEnd]=move(tmpArray[rightEnd]);


}

int main()
{
   vector<int> a={38,27,26,24,15,13,2,1};

   mergeSort(a);

   for(int i=0; i<a.size(); i++)
        cout<< a[i]<<" ";
}