#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <queue>
#include <functional>
#include <list>
#include <math.h>


using namespace std;

struct Vertex;

struct Edge 
{
    Vertex *dest;
    double cost;

    Edge(Vertex *d=0, double c=0.0)
    : dest(d), cost(c) {}
};

struct Vertex
{
    string name;
    vector<Edge> adj;
    double dist;
    Vertex *prev;
    int scratch;

    Vertex(const string &nm) : name(nm)
    { reset(); }
    void reset()
    {
        dist =INFINITY;
        prev=NULL;
        scratch =0;
    }
};

class Graph
{
    public:
        Graph() {}
        ~Graph()
        {
            for(vmap::iterator itr= vertexMap.begin();
                itr!= vertexMap.end();++itr)
                delete (*itr).second;
        }

        void addEdge(const string &sourceName,const string &destName, double cost);
        void printPath(const string &destName) const;
        void unweighted( const string &startName);
        void dijkstra(const string &startName);
        void negative(const string &startName);
        void acyclic(const string &startName);
    
    private:
        Vertex *getVertex(const string &vertexName);
        void printPath(const Vertex &dest) const;
        void clearAll();

        typedef map<string, Vertex *, less<string> > vmap;

        Graph(const Graph& rhs) {}
        const Graph &operator=(const Graph &rhs)
        { return *this;}

        vmap vertexMap;

};

Vertex *Graph::getVertex(const string &vertexName)
{
    vmap::iterator itr=vertexMap.find(vertexName);

    if(itr==vertexMap.end())
    {
        Vertex *newv= new Vertex(vertexName);
        vertexMap[vertexName]= newv;
        return newv;
    }
    return (*itr).second;
}
void Graph::addEdge(const string &sourceName, const string &destName,
            double cost)
{
    Vertex *v = getVertex(sourceName);
    Vertex *w = getVertex(destName);
    v->adj.push_back(Edge(w,cost));
}
void Graph::clearAll()
{
    for(vmap::iterator itr=vertexMap.begin();
        itr!=vertexMap.end();++itr)
        (*itr).second->reset();
}

void Graph::printPath(const Vertex &dest) const
{
    if(dest.prev !=NULL)
    {
        printPath(*dest.prev);
        cout<<" to " ;
    }
}

void Graph::printPath(const string &destName) const
{
    vmap:: const_iterator itr=vertexMap.find(destName);

    const Vertex &w=*(*itr).second;
    if(w.dist ==INFINITY)
        cout<<destName<<"is unreachable";
    else
    {
        cout<<"(Cost is:"<< w.dist<<") ";
        printPath(w);
    }
    cout<< endl;
}

int main(int argc, char *argv[])
{

    return 0;
}