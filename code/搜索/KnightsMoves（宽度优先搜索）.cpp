// Uva 439

#include <stack>
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <iostream>
#include <cctype>
#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;

int G[8][8];
int d[8][2] = {   
    {1,2},{1,-2},{2,1},{2,-1},
    {-1,2},{-1,-2},{-2,1},{-2,-1}
};

bool inside(int x, int y)
{
    return (x >= 0 && y >= 0 && x < 8 && y < 8);
}

void bfs(int x, int y)
{
    memset(G, 0, sizeof(G));
    G[x][y] = 1;
    queue<int> qx,qy;
    qx.push(x);
    qy.push(y);
    while (!qx.empty())
    {
        int ux = qx.front(); qx.pop();
        int uy = qy.front(); qy.pop();
        for (int i = 0; i < 8; i++)
        {
            int vx = ux + d[i][0];
            int vy = uy + d[i][1];
            if (inside(vx,vy) && !G[vx][vy])
            {
                G[vx][vy] = G[ux][uy] + 1;
                qx.push(vx);
                qy.push(vy);    
            }
        }
    }
}

int main()
{
    char a[3], b[3];
    while(scanf("%s%s", a, b) == 2)
    {
        int x0 = a[0] - 'a';
        int y0 = a[1] - '1';
        int x1 = b[0] - 'a';
        int y1 = b[1] - '1';
        bfs(x0, y0);
        printf("To get from %s to %s takes %d knight moves.\n", a, b, G[x1][y1] - 1);
    }
    return 0;
}