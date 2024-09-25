#include <iostream>
#include <vector>
#include <map>
#include <list>

using namespace std;

template<typename HashedObj>
class HashTable
{
    public:
        explicit HashTable( int size=100);
        bool contains(const HashedObj &x) const
        {
            auto &whichList =theLists[myhash(x)];
            return find(begin(whichList),end(whichList),x) !=end(whichList);
        }

        void makeEmpty()
        {
            for(auto &thisList: theLists)
                thisList.clear();
        }

        bool insert(const HashedObj &x)
        {
            auto &whichList =theLists[myhash(x)];
            if(find(begin(whichList),end(whichList),x) !=end(whichList))
                return false;
            whichList.push_back(x);

            if(++currentSize> theLists.size())
                rehash();
            return true;
        }
        bool insert(HashedObj &&x);
        bool remove(const HashedObj &x)
        {
            auto &whichList =theLists[myhash(x)];
            auto itr =find(begin(whichList),end(whichList),x);
            if(itr==end(whichList))
                return false;
            whichList.erase(itr);
            --currentSize;
            return true;
        }

    private:
        vector< list<HashedObj> > theLists;   //array of lists
        int currentSize;

        void rehash();
        size_t myhash(const HashedObj &x) const
        {
            static hash<HashedObj> hf;
            return hf(x) % theLists.size();
        }

};

template<typename Key>
class hash
{
    public:
        size_t operator() (const Key& k)
        {
            size_t hashVal =0;
            for(char ch: k)
                hashVal =37* hashVal +ch;

            return hashVal;
        }

};