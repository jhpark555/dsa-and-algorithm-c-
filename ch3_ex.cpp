#include <iostream>
#include <vector>

using namespace std;

template<typename Container>
void removeEveryOtherItem(Container & lst)
{
    typename Container::iterator itr =lst.begin();
    
    while(itr!=lst.end()){
        itr= lst.erase(itr);
        if(itr!=lst.end()) ++itr;
    }
    
}

template<typename Container, typename Object>
void change(Container& c, const Object &newvalue)
{
 typename Container::iterator itr = c.begin();
 while(itr!=c.end()){
    *itr++=newvalue;
 }

}

void print(vector<int>& lst, ostream& out =cout)
{
 if(lst.empty()) cout<<"Empty";
  else{
    auto itr= lst.begin();
    while(itr!=lst.end()){
        out<<*itr<<endl;
            ++itr;
    }
  }

}

template<typename Container>
void printo(const Container &c, ostream& out=cout)
{
    if(c.empty()) out<<"empty";
    else{
        auto itr = begin(c);
        out<<*itr<<" ";

        while(itr!=end(c)){
            out<<*itr++ <<" ";
        }
    }
}

template<typename Container>
auto begin(Container &c)->decltype(c.begin())
{
    return c.begin();
}
template<typename Container>
auto end(Container &c)->decltype(c.end())
{
    return c.end();
}



int main()
{
    vector<int> v(10);
    for(int i=0;i<10;i++) v[i]=i;
      
    
    //removeEveryOtherItem(v);

    change(v,0);
    
    //for(int i=0;i<10;i++) {
    //   cout<<v[i]<<endl;
    //}
  
    printo(v);
    return 0;
}