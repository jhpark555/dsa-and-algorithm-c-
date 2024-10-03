#include <iostream>
#include <vector>

using namespace std;

class MinHeap
{
    public:
        MinHeap()
        { size=0; }
        ~MinHeap() { }

        void arrange(int k)
        {
        
            while(k/2>0)
            {
                if (heap[k]< heap[k/2]) 
                    swap(heap[k],heap[k/2]);
                k /=2;
            }
        }
        void insert(int &x)
        {
            //printf("#%d \n",x);
            heap.push_back(x);

            size +=1;
            arrange(size);
        }
        int minchild(int k)
        {
            if( k*2 > size) return 2*k;
            else if (heap[2*k]< heap[2*k+1]) return 2*k;
            else return 2*k+1;
        }
        void sink(int k)
        {
            while(2*k<= size)
            {
               int mc= minchild(k);
                if (heap[k]> heap[mc])
                {
                    swap(heap[k],heap[mc]);
                }
                k=mc;
            }
        }
        int delete_at_root()
        {
            int item=heap[1];
            heap[1]=heap[size];
            size -=1;
            sink(1);
            return item;
        }
        vector<int> heap_sort()
        {
            int n;

            vector<int> arr;
            printf("***size=%d \n",size);
            for( int node=0; node< size; node++)
            {
                n=delete_at_root();
                arr.push_back(n);            
            }
            printf("***size=%d \n",size);
            return arr;
        }

    private:
        vector<int> heap;
        int size;
};

int main()
{
    int arr[7]={2, 3, 5, 7, 9, 10, 6};
    MinHeap h; 
    for(int i=0;i< 7;i++)
        h.insert(arr[i]);

    vector<int> t;

    t= h.heap_sort();
    
    //for(int i=0;i<t.size();i++) cout<<t[i]<<" ";
    return 0;
}