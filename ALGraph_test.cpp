
// 2020/1/23 //

#include "ALGraph.h"
#include <iterator>
#include <algorithm>

using std::ostream_iterator;
using std::copy;

int main()
{
    vector<char> chVt1 = {'1', '2', '3', '4', '5'};
    vector<Edge<char> > egVt1 = {
        Edge<char>('1', '3', 5),
        Edge<char>('1', '2', 2),
        Edge<char>('2', '4', 6),
        Edge<char>('2', '3', 2),
        Edge<char>('3', '5', 1),
        Edge<char>('3', '4', 7),
        Edge<char>('4', '5', 4),
        Edge<char>('4', '3', 2)
    };
    ALGraph<char> graph1(DIRECTED, NET, 5, 8, chVt1, egVt1);

    vector<char> chVt2 = {'1', '2', '3', '4', '5', '6'};
    vector<Edge<char> > egVt2 = {
        Edge<char>('1', '3', -1),
        Edge<char>('1', '2', -1),
        Edge<char>('2', '4', -1),
        Edge<char>('3', '5', -1),
        Edge<char>('3', '2', -1),
        Edge<char>('4', '6', -1),
        Edge<char>('4', '3', -1),
        Edge<char>('5', '6', -1),
        Edge<char>('5', '4', -1),
    };
    ALGraph<char> graph2(DIRECTED, GRAPH, 6, 9, chVt2, egVt2);

    vector<char> chVt3 = {'1', '2', '3', '4', '5', '6', '7', '8'};
    vector<Edge<char> > egVt3 = {
        Edge<char>('1', '3', -1),
        Edge<char>('1', '2', -1),
        Edge<char>('2', '6', -1),
        Edge<char>('2', '5', -1),
        Edge<char>('2', '4', -1),
        Edge<char>('3', '8', -1),
        Edge<char>('3', '7', -1),
        Edge<char>('4', '5', -1),
        Edge<char>('7', '8', -1)
    };
    ALGraph<char> graph3(UNDIRECTED, GRAPH, 8, 9, chVt3, egVt3);

    vector<char> chVt4 = {'0', '1', '2', '3'};
    vector<Edge<char> > egVt4 = {
        Edge<char>('0', '3', 4),
        Edge<char>('0', '1', 1),
        Edge<char>('1', '3', 2),
        Edge<char>('1', '2', 9),
        Edge<char>('2', '3', 8),
        Edge<char>('2', '1', 5),
        Edge<char>('2', '0', 3),
        Edge<char>('3', '2', 6)
    };
    ALGraph<char> graph4(DIRECTED, NET, 4, 8, chVt4, egVt4);

    vector<char> chVt5 = {'1', '2', '3', '4', '5', '6', '7'};
    vector<Edge<char> > egVt5 = {
        Edge<char>('1', '7', 36),
        Edge<char>('1', '6', 28),
        Edge<char>('1', '2', 23),
        Edge<char>('2', '7', 1),
        Edge<char>('2', '3', 20),
        Edge<char>('3', '7', 4),
        Edge<char>('3', '4', 15),
        Edge<char>('4', '7', 9),
        Edge<char>('4', '5', 3),
        Edge<char>('5', '7', 16),
        Edge<char>('5', '6', 17),
        Edge<char>('6', '7', 26)
    };
    ALGraph<char> graph5(UNDIRECTED, NET, 7, 12, chVt5, egVt5);

    vector<char> chVt6 = {'0', '1', '2', '3', '4', '5'};
    vector<Edge<char> > egVt6 = {
        Edge<char>('0', '3', -1),
        Edge<char>('0', '2', -1),
        Edge<char>('0', '1', -1),
        Edge<char>('2', '4', -1),
        Edge<char>('2', '1', -1),
        Edge<char>('3', '4', -1),
        Edge<char>('5', '4', -1),
        Edge<char>('5', '3', -1)
    };
    ALGraph<char> graph6(DIRECTED, GRAPH, 6, 8, chVt6, egVt6);

    vector<char> chVt7 = {'0', '1', '2', '3', '4', '5'};
    vector<Edge<char> > egVt7 = {
        Edge<char>('0', '2', 15),
        Edge<char>('0', '1', 2),
        Edge<char>('1', '4', 19),
        Edge<char>('1', '3', 10),
        Edge<char>('2', '4', 11),
        Edge<char>('2', '1', 4),
        Edge<char>('3', '5', 6),
        Edge<char>('4', '5', 5)
    };
    ALGraph<char> graph7(DIRECTED, NET, 6, 8, chVt7, egVt7);

    vector<int> dist1;
    vector<int> preVt1;
    vector<vector<int> > dist2;
    vector<vector<int> > preVt2;
    ostream_iterator<int> itInt(cout, " ");
    vector<int> lowcost;
    vector<int> closest;

    graph1.PrintALGraph();
    graph1.MinPath_Dijkstra(0, dist1, preVt1);
    PrintSingleVt(dist1);
    PrintSingleVt(preVt1);
    graph1.PrintMinPath_Dijkstra('1');
    
    graph2.PrintALGraph();
    graph2.TvsALGraph_BFS(0, 
        [](auto vexDt)->void{ cout << vexDt << "\t"; });
    
    graph3.PrintALGraph();
    graph3.TvsALGraph_DFS(0, 
        [](auto vexDt)->void{ cout << vexDt << "\t"; });

    graph4.MinPath_Floyd(dist2, preVt2);
    PrintDoubleVt(dist2);
    PrintDoubleVt(preVt2);

    graph5.MinSpanTree_Prim(0, lowcost, closest);
    PrintSingleVt(lowcost);
    PrintSingleVt(closest);

    cout << "Total weight: " << graph5.MinSpanTree_Kruskal() << endl;

    graph4.PrintALGraph();
    vector<VexNode<char> > invAdjList = GetInvAdjList(graph4.GetAdjList());
    PrintAdjList(invAdjList, NET);
    DestoryAdjList(invAdjList);

    ALGraph<char> graph8(graph4.GetParaVt()[0], graph4.GetAdjList());
    graph4.PrintALGraph();
    graph8.PrintALGraph();

    vector<int> topoStVt;
    if(graph6.TopoSort(topoStVt))
    {
        PrintSingleVt(topoStVt);
    }

    vector<Edge<char> > crtlAtyIdxVt;
    graph7.SeekCirticalPath(crtlAtyIdxVt);

    system("pause");
    return 0;
}