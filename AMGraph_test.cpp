
// 2020/1/22 //

#include "AMGraph.h"

int main()
{
    // AMGraph<char> test;
    // test.PrintGraph();

    vector<vector<int> > vt;
    vector<int> temp(10, INT16_MAX);
    vt.resize(10, temp);
    for(auto v : vt)
    {
        for(auto i : v)
            cout << i << " ";
        cout << endl;
    }

    system("pause");
    return 0;
}