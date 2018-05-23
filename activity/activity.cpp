//
// Created by Bastos on 20/05/2018.
//

#include "activity.h"

#define NINF std::numeric_limits<double>::infinity()

Node* Activity::addNode(std::string n, int id, double d, std::string p, std::string r, bool cl, bool rl) {
    Node* newNode = new Node(n,id,d,p,r,cl,rl);
    nodeSet.insert(newNode);
    return newNode;
}

Node* Activity::findNode(std::string name){
    for(std::set<Node*>::const_iterator it = Activity::nodeSet.begin(); it != nodeSet.end(); it++ ){
        Node* currentNode = *it;
        if(currentNode->getNamex() == name){
            return currentNode;
        }
    }
    return NULL;
}

Node* Activity::findNodeByID(int id){
    for(std::set<Node*>::const_iterator it = Activity::nodeSet.begin(); it != nodeSet.end(); it++ ){
        Node* currentNode = *it;
        if(currentNode->id == id){
            return currentNode;
        }
    }
    return NULL;
}

Node* Activity::findClaim(std::string r){
    for(std::set<Node*>::const_iterator it = Activity::nodeSet.begin(); it != nodeSet.end(); it++ ){
        Node* currentNode = *it;
        if(currentNode->resource == r && currentNode->claim){
            return currentNode;
        }
    }
    return NULL;
}

Node* Activity::findRelease(std::string r){
    for(std::set<Node*>::const_iterator it = Activity::nodeSet.begin(); it != nodeSet.end(); it++ ){
        Node* currentNode = *it;
        if(currentNode->resource == r && currentNode->release){
            return currentNode;
        }
    }
    return NULL;
}

Dep* Activity::addDepByName(std::string s, std::string d){

    Node* src = findNode(s);
    Node* dst = findNode(d);


   if(src != NULL && dst != NULL){
        Dep* newDep = new Dep(src,dst);
        depSet.insert(newDep);
        return newDep;
    }
    return NULL;
}

TopologicalActivity::TopologicalActivity(int V) // Constructor
{
    this->V = V;
    adj = new list<AdjListNode>[V];
}

void TopologicalActivity::addEdge(int u, int v, int weight)
{
    AdjListNode node(v, weight);
    adj[u].push_back(node); // Add v to u's list
}

// A recursive function used by longestPath. See below
// link for details
// https://www.geeksforgeeks.org/topological-sorting/
void TopologicalActivity::topologicalSortUtil(int v, bool visited[], stack<int> &Stack)
{
    // Mark the current node as visited
    visited[v] = true;

    // Recur for all the vertices adjacent to this vertex
    list<AdjListNode>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
    {
        AdjListNode node = *i;
        if (!visited[node.getV()])
            topologicalSortUtil(node.getV(), visited, Stack);
    }

    // Push current vertex to stack which stores topological
    // sort
    Stack.push(v);
}

// The function to find longest distances from a given vertex.
// It uses recursive topologicalSortUtil() to get topological
// sorting.
void TopologicalActivity::longestPath(int s, Activity& act)
{
    stack<int> Stack;
    int dist[V];

    // Mark all the vertices as not visited
    bool *visited = new bool[V];
    for (int i = 0; i < V; i++)
        visited[i] = false;

    // Call the recursive helper function to store Topological
    // Sort starting from all vertices one by one
    for (int i = 0; i < V; i++)
        if (visited[i] == false)
            topologicalSortUtil(i, visited, Stack);

    // Initialize distances to all vertices as infinite and
    // distance to source as 0
    for (int i = 0; i < V; i++)
        dist[i] = NINF;
    dist[s] = 0;

    // Process vertices in topological order
    while (Stack.empty() == false)
    {
        // Get the next vertex from topological order
        int u = Stack.top();
        Stack.pop();

        // Update distances of all adjacent vertices
        list<AdjListNode>::iterator i;
        if (dist[u] != NINF)
        {
            for (i = adj[u].begin(); i != adj[u].end(); ++i)
                if (dist[i->getV()] < dist[u] + i->getWeight())
                    dist[i->getV()] = dist[u] + i->getWeight();
        }
    }

    // Print the calculated longest distances
    for (int i = 0; i < V; i++)
        (dist[i] == NINF)? cout << "INF ":
        cout << i << " " << act.findNodeByID(i)->namex << " " << dist[i] << " " << endl;
}

int TopologicalActivity::longestPathN2N(int s, int d)
{
    stack<int> Stack;
    int dist[V];

    // Mark all the vertices as not visited
    bool *visited = new bool[V];
    for (int i = 0; i < V; i++)
        visited[i] = false;

    // Call the recursive helper function to store Topological
    // Sort starting from all vertices one by one
    for (int i = 0; i < V; i++)
        if (visited[i] == false)
            topologicalSortUtil(i, visited, Stack);

    // Initialize distances to all vertices as infinite and
    // distance to source as 0
    for (int i = 0; i < V; i++)
        dist[i] = NINF;
    dist[s] = 0;

    // Process vertices in topological order
    while (Stack.empty() == false)
    {
        // Get the next vertex from topological order
        int u = Stack.top();
        Stack.pop();

        // Update distances of all adjacent vertices
        list<AdjListNode>::iterator i;
        if (dist[u] != NINF)
        {
            for (i = adj[u].begin(); i != adj[u].end(); ++i)
                if (dist[i->getV()] < dist[u] + i->getWeight())
                    dist[i->getV()] = dist[u] + i->getWeight();
        }
    }

    return dist[d];
}

TopologicalActivity* Activity::convertActivityToTA(){
    TopologicalActivity* taAct = new TopologicalActivity(this->nodeSet.size());
    for( auto e : this->depSet) {
        taAct->addEdge(e->src->id,e->dst->id,e->src->duration);
    }
    return taAct;
}

set<std::string> getResources(Activity* act){
    set<std::string> resources;
    for( auto n : act->nodeSet){
        if(n->claim){
            resources.insert(n->resource);
        }
    }
    return resources;
}

void Activity::generateActivityMatrix() {
    TopologicalActivity* taAct = this->convertActivityToTA();
    set<std::string> resources = getResources((this));
    Matrix *m = new Matrix(resources.size(),resources.size());
    int i = 0;
    for( auto r : resources){
        Node* cl = this->findClaim(r);
        int j = 0;
        for( auto r : resources){
            Node* rl = this->findRelease(r);
            (*m)(j,i) = taAct->longestPathN2N(cl->id,rl->id);
            cout << "From cl : " << cl->id << " To rl: " << rl->id << " position " << i << ", " << j << " value: " << (*m)(i,j) << endl;
            j++;
        }
        i++;
    }
    this->activityMatrix = m;

}

Activity* ActivitySet::findByName(std::string name) {
    for ( auto a : activitySet ) {
        if(a->getName() == name){
            return a;
        }
    }
    return NULL;
}