
// 2020/3/28 //

#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <vector>

struct Position
{
    int x;
    int y;

    Position();
    Position(int x, int y);
    ~Position();
};

Position::Position():
    x(0), y(0) {}

Position::Position(int x, int y):
    x(x), y(y) {}

Position::~Position() {}

const int range = 30;
std::vector<int> subM(range, 0);
std::vector<std::vector<int> > M(range, subM);
Position here, next;
std::vector<Position> DIR = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };

void Init(int num)
{
    for(int i = 0; i <= num + 1; i++)
    {
        M[0][i] = -1;
        M[num + 1][i] = -1;
    }
    for(int i = 0; i <= num + 1; i++)
    {
        M[i][0] = -1;
        M[i][num + 1] = -1;
    }
}

void PrintMat(int start, int end)
{
    for(int i = start; i <= end; i++)
    {
        for(int j = start; j <= end; j++)
        {
            std::cout  << M[i][j] << "\t";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void Solve(int size)
{
    here.x = 1;
    here.y = 1;
    int dirInd = 0;
    int num = 1;
    M[1][1] = 1;
    while(num < size * size)
    {
        next.x = here.x + DIR[dirInd].x;
        next.y = here.y + DIR[dirInd].y;
        if(M[next.x][next.y] == 0)
        {
            num++;
            M[next.x][next.y] = num;
            here = next;
        }
        else
        {
            dirInd = (dirInd + 1) % 4;
        }
    }
}

int main()
{
    std::cout << "Please enter integer bigger than 1 and less than 20" << std::endl;
    int num = 0;
    std::cin >> num;

    Init(num);
    PrintMat(0, num + 1);
    Solve(num);
    PrintMat(1, num);

    system("pause");
    return 0;
}