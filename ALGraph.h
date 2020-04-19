
// 2020/1/22 //

#ifndef ALGRAPH_H
#define ALGRAPH_H

//? head files
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>

//? useful modules
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::queue;
using std::stack;
using std::sort;

//? self-defined constants
const int DIRECTED = 1; // directed graph
const int UNDIRECTED = 0; // undirected graph
const int NET = 1; // net
const int GRAPH = 0; // normal graph
const int FINDFAILED = -1; // vertex doesn't exist in the graph
const int AUTO = 1; // using weight of class "Edge"
const int TYPE = 0; // type weight
const int INFINITE = INT16_MAX; // indicate infinite
const int MAXTAG = 70; // max length of separator

// --------------- struct: AdjNode --------------- //

//? adjacent node of graph
struct AdjNode
{
    //? data members
    int idx_; // index of vertex
    int weight_; // weight of edge
    AdjNode* next_; // pointer of next adjacent node

    // ? constructor / deconstructor functions
    AdjNode();
    AdjNode(const AdjNode& item);
    AdjNode(int idx, int weight, AdjNode* next);
    ~AdjNode();

    // ? print functions
    void PrintAdjNode() const; // print content of an adjacent node
};

AdjNode::AdjNode():
    idx_(-1), weight_(-1), next_(nullptr) { }

AdjNode::AdjNode(const AdjNode& item):
    idx_(item.idx_), weight_(item.weight_), next_(item.next_) { }

AdjNode::AdjNode(int idx, int weight, AdjNode* next):
    idx_(idx), weight_(weight), next_(next) { }

AdjNode::~AdjNode() { }

void AdjNode::PrintAdjNode() const
{
    if(weight_ != -1)
    {
        cout << "Net node" << endl;
    }
    else
    {
        cout << "Not net node" << endl;
    }
    cout << "Next node: " << next_ << endl;
    cout << "Weight: " << weight_ << endl;
    if(!next_)
    {
        cout << "Next: null" << endl;
    }
    else
    {
        cout << "Next: not null" << endl;
    }
}

// --------------- struct: VexNode --------------- //

//? vertex of graph
template<typename VexType>
struct VexNode
{
    //? data members
    VexType data_;
    AdjNode* first_;

    //? constructor / deconstructor functions
    VexNode();
    VexNode(const VexNode& item);
    VexNode(VexType data, AdjNode first);
    ~VexNode();

    //? print functions
    void PrintVexNode() const; // print content of a vertex node
};

template<typename VexType>
VexNode<VexType>::VexNode():
    first_(nullptr) { }

template<typename VexType>
VexNode<VexType>::VexNode(const VexNode& item):
    data_(item.data_), first_(item.first_) { }

template<typename VexType>
VexNode<VexType>::VexNode(VexType data, AdjNode first):
    data_(data), first_(first) { }

template<typename VexType>
VexNode<VexType>::~VexNode() { }

template<typename VexType>
void VexNode<VexType>::PrintVexNode() const
{
    cout << "Data: " << data_ << endl;
    if(!first_)
    {
        cout << "First pointer: null" << endl;
    }
    else
    {
        cout << "First pointer: not null" << endl;
    }
}

// --------------- struct: Edge --------------- //

//? edge assisted to construct graph
template<typename VexType>
struct Edge
{
    //? data members
    VexType vex1_;
    VexType vex2_;
    int weight_;

    //? constructor / deconstructor functions
    Edge();
    Edge(const Edge& item);
    Edge(VexType vex1, VexType vex2, int weight);
    ~Edge();

    //? print functions
    void PrintEdge() const;
};

template<typename VexType>
Edge<VexType>::Edge():
    weight_(-1) { }

template<typename VexType>
Edge<VexType>::Edge(const Edge& item):
    vex1_(item.vex1_), vex2_(item.vex2_), weight_(item.weight_) { }

template<typename VexType>
Edge<VexType>::Edge(VexType vex1, VexType vex2, int weight):
    vex1_(vex1), vex2_(vex2), weight_(weight) { }

template<typename VexType>
Edge<VexType>::~Edge() { }

template<typename VexType>
void Edge<VexType>::PrintEdge() const
{
    cout << "Edge: (" << vex1_ << ", " << vex2_ << ") Weight: " << weight_ << endl;
}

// --------------- class: ALGraph --------------- //

//? graph consist of an adjacent list
template<typename VexType>
class ALGraph
{
    private:

        //? private data members
        int dirTag_; // judge whether the graph has direction
        int netTag_; // judge whether the edge has weight
        int vexNum_; // number of vertex
        int edgeNum_; // number of edge
        vector<VexNode<VexType> > vex_; // vertex set

        //? auxiliary functions
        // check whether the number of vertex and edge is right
        void CheckNumAndSize() const;

        // insert edge according to an instance of class "Edge"
        void InsertEdge(Edge<VexType> egVt, int mode);

        // get weight of edge in adjacent list
        int GetWeightOfAdjList(int vexIdx, int adjIdx, int rtnVal) const;

        // extract edge vector
        vector<Edge<VexType> > ExtractEgVt() const;

        // traverse graph throught DFS method recursively
        void RecursivelyTvs_DFS(int start, void(*pFun)(VexType vexDt), vector<bool>& visited) const;

        // merge two vertexes
        bool MergeTwoVex(VexType vex1, VexType vex2, vector<int>& vexSt) const;

        // find in degree of each vertex
        vector<int> GetInDegVt(const vector<VexNode<VexType> >& invAdjList) const;
        
        // judge the type of graph and print it
        void PrintGraphType() const;

        // print separator to divide each part
        void DividePart(const string& str) const; 

    public:

        //? constructor / deconstructor functions
        // construct graph through typing
        ALGraph();

        // copy constructor
        ALGraph(const ALGraph& item);

        // construct graph through adjacent list
        ALGraph(int dirTag, const vector<VexNode<VexType> >& adjList);

        // construct graph through vessels
        ALGraph(int dirTag, int netTag, int vexNum, int edgeNum, vector<VexType> vexVt, vector<Edge<VexType>> egVt);

        // deconstructor
        ~ALGraph();

        //? get data of class "ALGraph" functions
        // get the vector of graph parameters
        vector<int> GetParaVt() const;

        // get the adjacent list of the present graph
        vector<VexNode<VexType> > GetAdjList() const;

        //? search functions
        // confirm whether a vertex exists in the graph
        int LocateVex(VexType tar) const;

        //? traverse functions
        // traverse graph in BFS mode
        void TvsALGraph_BFS(int start, void(*pFun)(VexType vexDt)) const;

        // traverse graph in DFS mode
        void TvsALGraph_DFS(int start, void(*pFun)(VexType vexDt)) const;

        //? minimum path functions
        // find minimum path through Dijkstra algrithom
        void MinPath_Dijkstra(int start, vector<int>& dist, vector<int>& preVt) const;

        // find minimum path through Floyd algrithom
        void MinPath_Floyd(vector<vector<int> >& dist, vector<vector<int> >& preVt) const;

        //? minimum spanning tree functions
        // confirm minimum spanning tree of a graph through Prim algrithom
        void MinSpanTree_Prim(int start, vector<int>& lowcost, vector<int>& closest) const;

        // confirm minimum spanning tree of a graph through Kruskal algrithom
        int MinSpanTree_Kruskal() const;

        //? topology sorting functions
        // using topology sort algrithom to sort vertex set
        bool TopoSort(vector<int>& topoStVt) const;

        //? critical path functions
        // seek the critical path of a directed net
        bool SeekCirticalPath(vector<Edge<VexType> >& crtlAtyIdxVt) const;

        //? print functions
        // output each minimum path and distance from source points to other points
        void PrintMinPath_Dijkstra(VexType vex) const;

        // print the adjacent list of graph in index mode
        void PrintALGraph() const;

        //? inverse adjacent list friend functions
        // get the inverse adjacent list of the present adjacent list of a graph
        template<VexType> friend vector<VexNode<VexType> > GetInvAdjList(const vector<VexNode<VexType> >& adjList);

        // recycle memory of an adjacent list
        template<VexType> friend void DestoryAdjList(vector<VexNode<VexType>& > adjList);

        // print the content of adjacent list
        template<VexType> friend void PrintAdjList(const vector<VexNode<VexType> >& adjList);
};

template<typename VexType>
void ALGraph<VexType>::CheckNumAndSize() const
{
    // check the relation of edge number and vertex number
    if(dirTag_ == UNDIRECTED)
    {
        if(edgeNum_ < vexNum_ || edgeNum_ >  vexNum_ * (vexNum_ - 1) / 2)
        {
            cout << "Number of edge exists error!" << endl;
            system("pause");
            exit(-1);
        }
    }
    else
    {
        if(edgeNum_ < vexNum_ || edgeNum_ >  vexNum_ * (vexNum_ - 1))
        {
            cout << "Number of edge exists error!" << endl;
            system("pause");
            exit(-1);
        }
    }

    // check the size of vertex vector
    if(vexNum_ != vex_.size())
    {
        cout << "Vertex vector exists error!" << endl;
        system("pause");
        exit(-1);
    }

    // calculate sum edges
    int sumEg = 0;
    for(int i = 0; i < vexNum_; i++)
    {
        AdjNode* adjPtr = vex_[i].first_;
        while(adjPtr)
        {
            sumEg++;
            adjPtr = adjPtr->next_;
        }
    }
    // check the size of sum edges
    if((dirTag_ == DIRECTED && edgeNum_ != sumEg) || 
        (dirTag_ == UNDIRECTED && edgeNum_ != sumEg / 2))
    {
        cout << "Edge vector exists error!" << endl;
        system("pause");
        exit(-1);
    }
}

template<typename VexType>
void ALGraph<VexType>::InsertEdge(Edge<VexType> eg, int mode)
{
    // extract two vertexes
    VexType vex1 = eg.vex1_;
    VexType vex2 = eg.vex2_;
    // locate indexes of two vertexes
    int idx1 = LocateVex(vex1);
    int idx2 = LocateVex(vex2);
    if(idx1 != FINDFAILED && idx2 != FINDFAILED) // vertexes exist
    {
        if(dirTag_ == UNDIRECTED) // undirected graph
        {
            AdjNode* newNd1 = new AdjNode;
            AdjNode* newNd2 = new AdjNode;
            if(!newNd1 || !newNd2)
            {
                cout << "Memory allocate failed!" << endl;
                system("pause");
                exit(-1);
            }
            
            if(mode == AUTO) // use "eg.weight_" directly
            {
                newNd1->weight_ = eg.weight_;
                newNd2->weight_ = eg.weight_;
            }
            else // enter weight manually
            {
                cout << "Please enter the weight of edge<" << 
                idx1 << ", " << idx2 << ">: ";
                int tempWt;
                cin >> tempWt;
                newNd1->weight_ = tempWt;
                newNd2->weight_ = tempWt;
            }
            // store index
            newNd1->idx_ = idx1;
            newNd2->idx_ = idx2;
            // append node
            newNd1->next_ = vex_[idx2].first_;
            vex_[idx2].first_ = newNd1;
            newNd2->next_ = vex_[idx1].first_;
            vex_[idx1].first_ = newNd2;
        }
        else // directed graph
        {
            AdjNode* newNd = new AdjNode;
            if(!newNd) // check null pointer
            {
                cout << "Memory allocate failed!" << endl;
                system("pause");
                exit(-1);
            }

            if(mode == AUTO) // use "eg.weight_" directly
            {
                newNd->weight_ = eg.weight_;
            }
            else // enter weight manually
            {
                cout << "Please enter the weight of edge<" << idx1 << ", " << idx2 << ">: ";
                int tempWt;
                cin >> tempWt;
                newNd->weight_ = tempWt;
            }
            // store index
            newNd->idx_ = idx2;
            // append node
            newNd->next_ = vex_[idx1].first_;
            vex_[idx1].first_ = newNd;
        }
    }
    else // vertexes don't exist
    {
        cout << "The message of two vertexes exists error, please check your edge vector!" << endl;
        system("pause");
        exit(-1);
    }
}

template<typename VexType>
int ALGraph<VexType>::GetWeightOfAdjList(int vexIdx, int adjIdx, int rtnVal) const
{
    // pointer of adjacent node
    AdjNode* adjPtr = vex_[vexIdx].first_;
    while(adjPtr) // traverse adjacent node
    {
        int idx = adjPtr->idx_; // index stored
        if(idx == adjIdx) // find successfully
        {
            return adjPtr->weight_; // return weight
        }
        adjPtr = adjPtr->next_;
    }

    return rtnVal; // self-selected return value
}

template<typename VexType>
vector<Edge<VexType> > ALGraph<VexType>::ExtractEgVt() const
{
    vector<Edge<VexType> > egVt;
    // traverse edges inside the adjacent list
    for(int i = 0; i < vexNum_; i++)
    {
        AdjNode* adjPtr = vex_[i].first_;
        while(adjPtr)
        {
            int idx = adjPtr->idx_;
            int wgt = adjPtr->weight_;
            VexType vex1 = vex_[i].data_;
            VexType vex2 = vex_[idx].data_;
            Edge<VexType> tpEg(vex1, vex2, wgt); // construct temporary edge
            egVt.push_back(tpEg); // directly insert
            // remove duplication in undirected graph
            if(dirTag_ == UNDIRECTED)
            {
                // traverse edge vector
                for(int i = 0; i < int(egVt.size()); i++)
                {
                    if(egVt[i].vex1_ > egVt[i].vex2_) // duplication condition
                    {
                        // erase duplication
                        egVt.erase(egVt.begin() + i, egVt.begin() + i + 1);
                    }
                }
            }
            adjPtr = adjPtr->next_;
        }
    }
    
    return egVt;
}

template<typename VexType>
void ALGraph<VexType>::RecursivelyTvs_DFS(int start, void(*pFun)(VexType vexDt), vector<bool>& visited) const
{
    pFun(vex_[start].data_);
    visited[start] = true;
    AdjNode* adjPtr = vex_[start].first_; // start from source point
    while(adjPtr)
    {
        int idx = adjPtr->idx_;
        if(!visited[idx]) // unvisited point
        {
            RecursivelyTvs_DFS(idx, pFun, visited); // recursively traverse
        }
        adjPtr = adjPtr->next_;
    }
}

template<typename VexType>
bool ALGraph<VexType>::MergeTwoVex(VexType vex1, VexType vex2, vector<int>& vexSt) const
{
    // locate indexes
    int idx1 = LocateVex(vex1);
    int idx2 = LocateVex(vex2);
    if(idx1 == FINDFAILED || idx2 == FINDFAILED)
    {
        cout << "Vertexes entered error, please check again!" << endl;
        system("pause");
        exit(-1);
    }

    // set index
    int stIdx1 = vexSt[idx1];
    int stIdx2 = vexSt[idx2];
    if(stIdx1 == stIdx2) // two vertexes inside the same set
    {
        // * switch of print option
        // cout << "Vertexes of edge(" << vex1 << ", " << vex2 << ") are in the same set already, continue" << endl;
        return false;
    }
    // if two indexes is not equal, insert the first index to set
    for(int i = 0; i < vexNum_; i++)
    {
        // find the location of the second index in vertex set
        if(vexSt[i] == stIdx2)
        {
            vexSt[i] = stIdx1; // insert it into set of the first index
        }
    }

    return true;
}

template<typename VexType>
vector<int> ALGraph<VexType>::GetInDegVt(const vector<VexNode<VexType> >& invAdjList) const
{
    vector<int> inDegVt;
    int vexNum = int(invAdjList.size());
    for(int i = 0; i < vexNum; i++)
    {
        int count = 0;
        AdjNode* adjPtr = invAdjList[i].first_;
        while(adjPtr)
        {
            count++;
            adjPtr = adjPtr->next_;
        }
        inDegVt.push_back(count);
    }
    
    return inDegVt;
}

template<typename VexType>
void ALGraph<VexType>::PrintGraphType() const
{
    if(dirTag_ == UNDIRECTED) // undirected graph
    {
        if(netTag_ == GRAPH) // normal graph
        {
            cout << "Adjacency List of undirected graph: " << endl;
        }
        else // net
        {
            cout << "Adjacency List of undirected net: " << endl;
        }
    }
    else // directed graph
    {
        if(!netTag_) // normal graph
        {
            cout << "Adjacency List of directed graph: " << endl;
        }
        else // net
        {
            cout << "Adjacency List of directed net: " << endl;
        }
    }
}

template<typename VexType>
void ALGraph<VexType>::DividePart(const string& str) const
{
    // control the number of tag to confirm the string is in the center
    int tagNum = (MAXTAG - str.length()) / 2; 
    for(int i = 0; i < tagNum; i++)
    {
        cout << "-";
    }
    cout << str; // print string
    for(int i = 0; i < tagNum; i++)
    {
        cout << "-";
    }

    // control separator upside and downside to align
    if(str.length() % 2 == 1)
    {
        cout << "-";
    }
    cout << endl;
}

template<typename VexType>
ALGraph<VexType>::ALGraph()
{
    // basic informations
    cout << "Whether the graph has direction(0 is false, 1 is true): ";
    cin >> dirTag_;
    cout << "Whether the graph is a net(0 is false, 1 is true): ";
    cin >> netTag_;
    cout << "Please enter the number of vertex and edge by sequence: ";
    cin >> vexNum_ >> edgeNum_;

    // message of vertexes
    cout << "Please enter the message of each vertex: ";
    for(int i = 0; i < vexNum_; i++)
    {
        VexNode<VexType> tempNd;
        cin >> tempNd.data_;
        vex_.push_back(tempNd);
    }

    // message of edges
    for(int i = 0; i < edgeNum_; i++)
    {
        cout << "Please enter every two vertexes of each edge: ";
        VexType vex1, vex2;
        cin >> vex1 >> vex2;
        Edge<VexType> tpEg(vex1, vex2, -1); // temp edge
        InsertEdge(tpEg, TYPE);
    }

    CheckNumAndSize(); // check parameters
}

template<typename VexType>
ALGraph<VexType>::ALGraph(const ALGraph& item):
    dirTag_(item.dirTag_), netTag_(item.netTag_), vexNum_(item.vexNum_), edgeNum_(item.edgeNum_), vex_(item.vex_) { }

template<typename VexType>
ALGraph<VexType>::ALGraph(int dirTag, const vector<VexNode<VexType> >& adjList):
    dirTag_(dirTag), vexNum_(int(adjList.size())), vex_(adjList)
{
    vector<Edge<VexType> > edgeVt = ExtractEgVt();
    if(dirTag_ == GRAPH)
    {
        edgeNum_ = int(edgeVt.size()) / 2;
    }
    else
    {
        edgeNum_ = int(edgeVt.size());
    }

    CheckNumAndSize();
}

template<typename VexType>
ALGraph<VexType>::ALGraph(int dirTag, int netTag, int vexNum, int edgeNum, vector<VexType> vexVt, vector<Edge<VexType>> egVt):
    dirTag_(dirTag), netTag_(netTag), vexNum_(vexNum), edgeNum_(edgeNum)
{
    // construct graph through vessels
    for(int i = 0; i < vexNum; i++)
    {
        VexNode<VexType> temp;
        temp.data_ = vexVt[i];
        vex_.push_back(temp);
    }
    for(int i = 0; i < edgeNum_; i++)
    {
        InsertEdge(egVt[i], AUTO); // insert edge in mode "AUTO"
    }

    CheckNumAndSize(); // check parameters
}

template<typename VexType>
ALGraph<VexType>::~ALGraph()
{
    DestoryAdjList(vex_);
}

template<typename VexType>
vector<int> ALGraph<VexType>::GetParaVt() const
{
    vector<int> paraVt;
    paraVt.push_back(dirTag_);
    paraVt.push_back(netTag_);
    paraVt.push_back(vexNum_);
    paraVt.push_back(edgeNum_);

    return paraVt;
}

template<typename VexType>
vector<VexNode<VexType> > ALGraph<VexType>::GetAdjList() const
{
    vector<VexNode<VexType> > vexCpyVt(vexNum_); // copy of vertex vector "vex_"
    // do the deep copy of vector "vex_"
    for(int i = 0; i < vexNum_; i++)
    {
        vexCpyVt[i].data_ = vex_[i].data_; // copy item "data_"
        // copy adjacent nodes of each vertex
        AdjNode* adjPtr = vex_[i].first_;
        while(adjPtr)
        {
            AdjNode* newNd = new AdjNode;
            if(!newNd) // check null pointer
            {
                cout << "Memory allocate failed!" << endl;
                system("pause");
                exit(-1);
            }
            newNd->idx_ = adjPtr->idx_;
            newNd->weight_ = adjPtr->weight_;
            newNd->next_ = vexCpyVt[i].first_;
            vexCpyVt[i].first_ = newNd;

            adjPtr = adjPtr->next_;
        }
    }

    return vexCpyVt;
}

template<typename VexType>
int ALGraph<VexType>::LocateVex(VexType tar) const
{
    // search target
    for(int i = 0; i < vexNum_; i++)
    {
        if(tar == vex_[i].data_)
        {
            return i;
        }
    }

    return FINDFAILED; // search failed, target doesn't exist
}

template<typename VexType>
void ALGraph<VexType>::TvsALGraph_BFS(int start, void(*pFun)(VexType vexDt)) const
{
    DividePart(" Traverse Graph (BFS) ");

    // judge whether a certain point is visited
    vector<bool> visited(vexNum_, false); 
    pFun(vex_[start].data_); // call function
    visited[start] = true;

    AdjNode* adjPtr;
    queue<int> qe; // assisted queue
    qe.push(start); // push source point into queue
    while(!qe.empty())
    {
        int hd = qe.front(); // head of queue
        adjPtr = vex_[hd].first_;
        qe.pop();
        while(adjPtr)
        {
            int idx = adjPtr->idx_; // index stored
            if(!visited[idx]) // unvisited point
            {
                pFun(vex_[idx].data_); // call function
                visited[idx] = true; // sign visited
                qe.push(idx); // push index
            }
            adjPtr = adjPtr->next_;
        }
    }

    cout << endl;
    DividePart("");
}

template<typename VexType>
void ALGraph<VexType>::TvsALGraph_DFS(int start, void(*pFun)(VexType vexDt)) const
{
    DividePart(" Traverse Graph (DFS) ");

    // judge whether a certain point is visited
    vector<bool> visited(vexNum_, false);
    pFun(vex_[start].data_);
    visited[start] = true;

    AdjNode* adjPtr = vex_[start].first_;
    while(adjPtr)
    {
        int idx = adjPtr->idx_;
        if(!visited[idx]) // if this point is unvisited, recursively transmit
        {
            // confirm vector "visited" transmited to the next layer
            RecursivelyTvs_DFS(idx, pFun, visited);
        }
        adjPtr = adjPtr->next_;
    }

    cout << endl;
    DividePart("");
}

template<typename VexType>
void ALGraph<VexType>::MinPath_Dijkstra(int start, vector<int>& dist, vector<int>& preVt) const
{
    if(!netTag_ || !dirTag_) // check graph type
    {
        cout << "Only support directed net, please check again!" << endl;
        system("pause");
        exit(-1);
    }

    // set a series of basic vectors
    vector<bool> flagVt(vexNum_, false);
    dist.resize(vexNum_, INFINITE);
    preVt.resize(vexNum_, -1);
    
    // traverse adjacent of "vex_[start]", initialize vector "dist"
    AdjNode* adjPtr = vex_[start].first_;
    while(adjPtr)
    {
        int idx = adjPtr->idx_;
        dist[idx] = adjPtr->weight_;
        adjPtr = adjPtr->next_;
    }
    // initialize vector "preVt", according to vector "dist"
    for(int i = 0; i < vexNum_; i++)
    {
        if(dist[i] == INFINITE) // distance is infinite, no way
        {
            preVt[i] = -1;
        }
        else // distance is finite, exists way
        {
            preVt[i] = start;
        }
    }
    // set source point in these two vectors
    dist[start] = 0;
    flagVt[start] = true;

    for(int i = 0; i < vexNum_; i++)
    {
        int tpNum = INFINITE, tpIdx = start;
        // find minimum vertex in set "V - S"
        for(int j = 0; j < vexNum_; j++)
        {
            if(!flagVt[j] && dist[j] < tpNum)
            {
                tpIdx = j;
                tpNum = dist[j];
            }
        }
        if(tpIdx == start) // find nothing, done
        {
            return ;
        }
        // find successfully, continue
        flagVt[tpIdx] = true; // insert "tpIdx" into set "S"
        // renew the distance from adjacent pointes of "tpIdx" to source point
        for(int j = 0; j < vexNum_; j++)
        {
            int tpDist = INFINITE;
            // test each adjacent of point "tpIdx"
            AdjNode* adjPtr = vex_[tpIdx].first_;
            while(adjPtr)
            {
                int idx = adjPtr->idx_;
                if(idx == j)
                {
                    tpDist = adjPtr->weight_;
                    break;
                }
                adjPtr = adjPtr->next_;
            }
            // judge whether "j" is in set "V - S" and exists way
            if(!flagVt[j] && tpDist < INFINITE)
            {
                // renew distance
                if(dist[j] > dist[tpIdx] + tpDist)
                {
                    dist[j] = dist[tpIdx] + tpDist;
                    preVt[j] = tpIdx;
                }
            }
        }
    }
}

template<typename VexType>
void ALGraph<VexType>::MinPath_Floyd(vector<vector<int> >& dist, vector<vector<int> >& preVt) const
{
    // initialize a series of vessels
    vector<int> temp1(vexNum_, INFINITE);
    vector<int> temp2(vexNum_, -1);
    dist.resize(vexNum_, temp1);
    preVt.resize(vexNum_, temp2);

    // iterate vector "dist" and "preVt" to renew
    for(int i = 0; i < vexNum_; i++)
    {
        for(int j = 0; j < vexNum_; j++)
        {
            // renew "dist[i][j]"
            if(i == j) // distance of a point to self
            {
                dist[i][j] = 0; // distance set to zero
                continue;
            }
            // renew distance according to the edge's weight
            dist[i][j] = GetWeightOfAdjList(i, j, INFINITE);

            // renew vector "preVt"
            if(dist[i][j] < INFINITE && i != j) // exists access
            {
                preVt[i][j] = i;
            }
            else // doesn't exists access
            {
                preVt[i][j] = -1;
            }
        }
    }
    
    // insert point to accelerate, "i" is the point to insert, "dist[j][i]" and "dist[i][k]" is the two access produced from point "i"
    for(int i = 0; i < vexNum_; i++)
    {
        for(int j = 0; j < vexNum_; j++)
        {
            for(int k = 0; k < vexNum_; k++)
            {
                // value of two access less than one
                if(dist[j][i] + dist[i][k] < dist[j][k]) // renew two vector
                {
                    dist[j][k] = dist[j][i] + dist[i][k];
                    preVt[j][k] = preVt[i][k];
                }
            }
        }
    }
}

template<typename VexType>
void ALGraph<VexType>::MinSpanTree_Prim(int start, vector<int>& lowcost, vector<int>& closest) const
{
    // using "tree" to indicate "set of minimum spanning tree"
    // initialize two vectors
    lowcost.resize(vexNum_, 0);
    closest.resize(vexNum_, -1);
    vector<bool> treeSt(vexNum_, false); // tree set
    treeSt[start] = true; // insert start point into set of tree

    // further initialize
    for(int i = 0; i < vexNum_; i++)
    {
        if(i != start) // initialize vectores according to each edge
        {
            lowcost[i] = GetWeightOfAdjList(start, i, INFINITE);
            closest[i] = start;
            treeSt[i] = false;
        }
        else // distance of source point to itself is zero
        {
            lowcost[i] = 0;
        }
    }
    for(int i = 0; i < vexNum_; i++)
    {
        int tpNum = INFINITE;
        int tpIdx = start;
        for(int j = 0; j < vexNum_; j++)
        {
            if(!treeSt[j] && lowcost[j] < tpNum)
            {
                tpIdx = j;
                tpNum = lowcost[j];
            }
        }
        if(tpIdx == start) // find failed
        {
            break; // break loop
        }
        // find successfully
        treeSt[tpIdx] = true; // insert "tpIdx" into tree set
        // renew vector "lowcost" and "closest"
        for(int j = 0; j < vexNum_; j++)
        {
            int tpWgt = GetWeightOfAdjList(tpIdx, j, INFINITE);
            if(!treeSt[j] && tpWgt < lowcost[j])
            {
                lowcost[j] = tpWgt;
                closest[j] = tpIdx;
            }
        }
    }
}

template<typename VexType>
int ALGraph<VexType>::MinSpanTree_Kruskal() const
{
    // extract edge from adjacent list
    vector<Edge<VexType> > egVt = ExtractEgVt(); 
    if(int(egVt.size()) != edgeNum_) // check size
    {
        cout << "Function exists error, please check again!" << endl;
        system("pause");
        exit(-1);
    }

    // sort edge vector according to weight
    sort(egVt.begin(), egVt.end(), [](Edge<auto> eg1, Edge<auto> eg2)->bool{ return eg1.weight_ < eg2.weight_; });

    // initialize vertex vector
    vector<int> vexSt(vexNum_, 0);
    for(int i = 0; i < vexNum_; i++)
    {
        vexSt[i] = i;
    }

    // calculate the total weight
    int rst = 0; // sum of weight
    int count = vexNum_; // counter of merge time
    for(int i = 0; i < edgeNum_; i++)
    {
        // merge time no more than the number of vertex subtract one
        if(MergeTwoVex(egVt[i].vex1_, egVt[i].vex2_, vexSt))
        {
            rst += egVt[i].weight_; // sum weight value
            count--; // time decrease one
            if(count == 1) // indicate there is only one set
            {
                return rst;
            }
        }
    }

    return 0;
}

template<typename VexType>
bool ALGraph<VexType>::TopoSort(vector<int>& topoStVt) const
{
    if(dirTag_ == UNDIRECTED)
    {
        cout << "Only directed graph can be sorted, please check again!" << endl;
        return false;
    }
    if(!topoStVt.empty()) // check empty
    {
        cout << "Topology sorting vector exists error!" << endl;
        system("pause");
        exit(-1);
    }

    // get in degree number of each vertex
    vector<int> inDegVt = GetInDegVt(GetInvAdjList(vex_));
    stack<int> stk;
    int outputVex = 0;
    for(int i = 0; i < vexNum_; i++)
    {
        if(!inDegVt[i]) // in degree equal to zero, push
        {
            stk.push(i);
        }
    }

    // topology sort
    while(!stk.empty())
    {
        int hdIdx = stk.top();
        stk.pop();
        topoStVt.push_back(hdIdx); // push vertex in sequence
        outputVex++; // output number increase one

        // each adjacent node's in degree of top vertex decrease one
        AdjNode* adjPtr = vex_[hdIdx].first_;
        while(adjPtr)
        {
            int idx = adjPtr->idx_;
            inDegVt[idx]--;
            if(!inDegVt[idx]) // find adjacent node has no precursor
            {
                stk.push(idx);
            }
            adjPtr = adjPtr->next_;
        }
    }

    if(outputVex < vexNum_) // this directed graph exists loop
    {
        cout << "This graph exists loop, can not be sorted!" << endl;
        return false;
    }
    
    return true;
}

template<typename VexType>
bool ALGraph<VexType>::SeekCirticalPath(vector<Edge<VexType> >& crtlAtyIdxVt) const
{
    if(!crtlAtyIdxVt.empty())
    {
        cout << "Critical activity index vector exists error!" << endl;
        system("pause");
        exit(-1);
    }

    vector<int> topoStVt;
    if(!TopoSort(topoStVt))
    {
        cout << "This graph exists loop, has no topology sequence!" << endl;
        system("pause");
        exit(-1);
    }

    // earliest happen time vector of activities
    vector<int> ve(vexNum_, 0); 
    // seek the earliest happen time of each activity
    for(int i = 0; i < vexNum_; i++) // topology sequence
    {
        // incident earliest happen time
        int topoIdx = topoStVt[i];
        AdjNode* adjPtr = vex_[topoIdx].first_;
        while(adjPtr)
        {
            int idx = adjPtr->idx_;
            int wgt = adjPtr->weight_;
            if(ve[idx] < ve[topoIdx] + wgt)
            {
                ve[idx] = ve[topoIdx] + wgt;
            }
            adjPtr = adjPtr->next_;
        }
    }

    // latest happen time vector of activities
    vector<int> vl(vexNum_, ve[vexNum_ - 1]); 
    // seek the earliest happen time of each activity
    for(int i = vexNum_ - 1; i >= 0; i--) // inverse topology sequence
    {
        // incident latest happen time
        int topoIdx = topoStVt[i];
        AdjNode* adjPtr = vex_[topoIdx].first_;
        while(adjPtr)
        {
            int idx = adjPtr->idx_;
            int wgt = adjPtr->weight_;
            if(vl[topoIdx] > vl[idx] - wgt)
            {
                vl[topoIdx] = vl[idx] - wgt;
            }
            adjPtr = adjPtr->next_;
        }
    }

    // judge whether a certain activity is critical activity
    cout << "Path of critical activity is: " << endl;
    for(int i = 0; i < vexNum_; i++)
    {
        // judge the earlist and latest happen time of activities
        AdjNode* adjPtr = vex_[i].first_;
        while(adjPtr)
        {
            int idx = adjPtr->idx_;
            int wgt = adjPtr->weight_;
            int elyTime = ve[i]; // earlist happen time of activity
            int latTime = vl[idx] - wgt; // latest happen time of activity
            if(elyTime == latTime) // critical activity
            {
                crtlAtyIdxVt.push_back(Edge<VexType>(vex_[i].data_, vex_[idx].data_, wgt));
            }
            adjPtr = adjPtr->next_;
        }
    }

    // sort edge vector according to weight
    sort(crtlAtyIdxVt.begin(), crtlAtyIdxVt.end(), [](Edge<auto> eg1, Edge<auto> eg2)->bool{ return eg1.weight_ < eg2.weight_; });
    for(auto ele : crtlAtyIdxVt) // print critical activities on edge
    {
        ele.PrintEdge();
    }

    return true;
}

template<typename VexType>
void ALGraph<VexType>::PrintALGraph() const
{
    DividePart(" ALGraph(Data Pattern) ");
    PrintGraphType();

    PrintAdjList(vex_, netTag_);

    DividePart("");
}

template<typename VexType>
void ALGraph<VexType>::PrintMinPath_Dijkstra(VexType vex) const
{
    vector<int> dist;
    vector<int> preVt;

    int start = LocateVex(vex); // index of source point
    if(start != FINDFAILED) // find failed
    {
        // call "Dijkstra" algorithm to get result
        MinPath_Dijkstra(start, dist, preVt);
    }
    else // find successfully
    {
        cout << "Source point exists error, please check again!" << endl;
        system("pause");
        exit(-1);
    }

    DividePart(" Minimum Path List ");
    cout << "Source point: " << vex << endl;
    cout << "Minimum way between source point and other points: " << endl;

    // output minimum way and distance
    for(int i = 0; i < vexNum_; i++)
    {
        stack<int> stk;
        cout << "Minimum path: ";
        int tpPre = preVt[i];
        // precursor doesn't exist, no way
        if(tpPre == -1 && vex != vex_[i].data_)
        {
            cout << vex << "--" << vex_[i].data_ << ": no way" << endl;
            continue;
        }

        // from present node to find the first node one by one
        while(tpPre != -1)
        {
            stk.push(tpPre); // push each node into stack
            tpPre = preVt[tpPre]; // iterate "tpPre"
        }
        // print path in sequence
        while(!stk.empty())
        {
            cout << vex_[stk.top()].data_ << "--";
            stk.pop();
        }
        // print minimum distance
        cout << vex_[i].data_ << endl 
            << "Minimum distance: " << dist[i] << endl;
    }

    DividePart("");
}

template<typename VexType>
vector<VexNode<VexType> > GetInvAdjList(const vector<VexNode<VexType> >& adjList)
{
    int vexNum = int(adjList.size());
    vector<VexNode<VexType> > invAdjList(vexNum);
    for(int i = 0; i < vexNum; i++)
    {
        invAdjList[i].data_ = adjList[i].data_;
    }

    // traverse present adjacent list
    for(int i = 0; i < vexNum; i++)
    {
        AdjNode* adjPtr = adjList[i].first_;
        while(adjPtr)
        {
            int idx = adjPtr->idx_;
            int wgt = adjPtr->weight_;

            AdjNode* newNd = new AdjNode;
            if(!newNd) // check null pointer
            {
                cout << "Memory allocate failed!" << endl;
                system("pause");
                exit(-1);
            }
            newNd->weight_ = wgt;
            newNd->idx_ = i;
            newNd->next_ = invAdjList[idx].first_;
            invAdjList[idx].first_ = newNd;
            
            adjPtr = adjPtr->next_;
        }
    }

    return invAdjList;
}

template<typename VexType>
void DestoryAdjList(vector<VexNode<VexType> >& adjList)
{
    int vexNum = int(adjList.size());
    // recycle allocated memory
    for(int i = 0; i < vexNum; i++)
    {
        AdjNode* adjPtr = adjList[i].first_;
        while(adjPtr) // traverse adjacent list
        {
            AdjNode* delNd = adjPtr;
            adjPtr = adjPtr->next_;
            delete delNd;
        }
        adjList[i].first_ = nullptr; // set each pointer empty
    }
}

template<typename VexType>
void PrintAdjList(const vector<VexNode<VexType> >& adjList, int netTag)
{
    int vexNum = int(adjList.size());
    // print content in adjacent list in special format
    for(int i = 0; i < vexNum; i++)
    {
        cout << adjList[i].data_ << ": "; // vertex message
        // adjacent node message
        AdjNode* adjPtr = adjList[i].first_;
        while(adjPtr) // traverse adjacent node
        {
            int idx = adjPtr->idx_;
            VexType vexDt = adjList[idx].data_;
            if(netTag == GRAPH) // normal graph
            {
                cout << "[" << vexDt << "] "; // print data
            }
            else // net
            {
                cout << "[" << vexDt << "(" 
                    << adjPtr->weight_ << ")" << "] "; // print data and weight
            }
            adjPtr = adjPtr->next_;
        }
        cout << endl;
    }
}

// --------------- Functions --------------- //

template<typename T>
void PrintSingleVt(vector<T> sgVt)
{
    for(auto ele : sgVt)
    {
        cout << ele << "\t";
    }
    cout << endl;
}

template<typename T>
void PrintDoubleVt(vector<vector<T> > dbVt)
{
    for(auto vt : dbVt)
    {
        for(auto ele : vt)
        {
            cout << ele << "\t";
        }
        cout << endl;
    }
}

#endif