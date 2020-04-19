
// 2020/1/22 //

#ifndef AMGRAPH_H
#define AMGRAPH_H

#include <iostream>
#include <cstdlib>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

typedef int EdgeType;

template<typename VexType>
class AMGraph
{
    private:
        int dirTag_; // judge whether the graph has direction
        int netTag_; // judge whether the graph is a net
        int vexNum_;
        int edgeNum_;
        vector<VexType> vex_;
        vector<vector<EdgeType> > edge_;
    public:
        AMGraph();
        AMGraph(int vexNum, int edgeNum, vector<VexType> vex, vector<vector<EdgeType> > edge);
        ~AMGraph();
        int LocateVex(VexType tar) const;
        void PrintGraph() const;
};

template<typename VexType>
AMGraph<VexType>::AMGraph()
{
    cout << "Whether the graph has direction(1 is true, 0 is false): ";
    cin >> dirTag_;
    cout << "Whether the graph is a net(1 is true, 0 is false): ";
    cin >> netTag_;
    cout << "Please enter the number of vertex: ";
    cin >> vexNum_;
    cout << "Please enter the number of edge: ";
    cin >> edgeNum_;

    cout << "Firstly, please enter the message of each vertex: ";
    vex_.resize(vexNum_);
    for(int i = 0; i < vexNum_; i++)
    {
        cin >> vex_[i];
    }

    if(netTag_ == 0)
    {
        vector<EdgeType> tempVt(vexNum_, 0);
        edge_.resize(vexNum_, tempVt);
    }
    else
    {
        vector<EdgeType> tempVt(vexNum_, INT16_MAX);
        edge_.resize(vexNum_, tempVt);
    }

    cout << "Secondly, please enter two vertexes of an edge: " << endl;
    int tempEdgeNum = edgeNum_;
    while(tempEdgeNum--)
    {
        VexType vex1, vex2;
        cout << "Please enter the two vertexes of an edge: ";
        cin >> vex1 >> vex2;
        int idx1 = LocateVex(vex1);
        int idx2 = LocateVex(vex2);

        if(idx1 != -1 && idx2 != -1)
        {
            int weight = 0;
            if(netTag_ == 1)
            {
                cout << "Please enter the weight of edge <" << vex1 << ", " << vex2 << ">: ";
                cin >> weight;
            }

            if(dirTag_ == 0)
            {
                if(netTag_ == 0)
                {
                    edge_[idx1][idx2] = 1;
                    edge_[idx2][idx1] = 1;
                }
                else
                {
                    edge_[idx1][idx2] = weight;
                    edge_[idx2][idx1] = weight;
                }
            }
            else
            {
                if(netTag_ == 0)
                {
                    edge_[idx1][idx2] = 1;
                }
                else
                {
                    edge_[idx1][idx2] = weight;
                }
            }
        }
        else
        {
            cout << "The message of two vertexes exists error, please enter again!" << endl;
            tempEdgeNum++;
        }
    }
}

template<typename VexType>
AMGraph<VexType>::AMGraph(int vexNum, int edgeNum, vector<VexType> vex, vector<vector<EdgeType> > edge)
{
    if(dirTag_ == 0)
    {
        if((edgeNum > vexNum * (vexNum - 1) / 2) || (edgeNum < vexNum))
        {
            cout << "Number of edge exists error!" << endl;
            exit(-1);
        }
        else
        {
            edgeNum_ = edgeNum;
        }
    }
    else
    {
        if((edgeNum > vexNum * (vexNum - 1)) || (edgeNum < vexNum))
        {
            cout << "Number of edge exists error!" << endl;
            exit(-1);
        }
        else
        {
            edgeNum_ = edgeNum;
        }
    }

    if(vex.size() != vexNum)
    {
        cout << "Vertex vector exists error!" << endl;
        exit(-1);
    }
    else
    {
        vex_ = vex;
    }

    if(edge.size() != edgeNum_)
    {
        cout << "Length of edge vector's column exists error!" << endl;
        exit(-1);
    }
    for(auto vt : edge)
    {
        if(vt.size() != edgeNum_)
        {
            cout << "Length of edge vector's row exists error!" << endl;
            exit(-1);
        }
        else
        {
            edge_.push_back(vt);
        }
    }
}

template<typename VexType>
AMGraph<VexType>::~AMGraph() { }

template<typename VexType>
int AMGraph<VexType>::LocateVex(VexType tar) const
{
    for(int i = 0; i < vexNum_; i++)
    {
        if(vex_[i] == tar)
        {
            return i;
        } 
    }
    
    return -1;
}

template<typename VexType>
void AMGraph<VexType>::PrintGraph() const
{
    cout << "Adjacent matrix of this graph is: " << endl;
    for(auto vt : edge_)
    {
        for(auto vexDt : vt)
        {
            cout << vexDt << "\t";
        }
        cout << endl;
    }
}

#endif

// ! experience:
// ! 1. Whenever you use vector, you must consider initialization problem
// ! 2. You should confirm the size is right