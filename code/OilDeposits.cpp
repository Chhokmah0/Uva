#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
const int maxn = 100 + 5;

char pic[maxn][maxn];//图本身
int m, n, idx[maxn][maxn];//idx == 连通图的id
queue<int> x,y;

//深度优先用递归实现
void floodfill_dfs(int r, int c, int id)
{
    if(r<0 || c<0 || r>=m || c>=n)//出界
        return;
    if(pic[r][c] != '@' || idx[r][c])//不是@或已经访问
        return;
    idx[r][c] = id;
    for (int i = -1; i <= 1; i++)
        for (int j = -1; j <= 1; j++)
            floodfill_dfs(r+i,c+j,id);
}

//宽度优先用队列实现
void floodfill_bfs(int r, int c, int id)
{
    x.push(r);y.push(c);
    while(!x.empty())
    {
        r = x.front();x.pop();
        c = y.front();y.pop();
        for (int i = -1; i <= 1; i++)
            for (int j = -1; j <= 1; j++)
                if(!(r+i<0 || c+j<0 || r+i>=m || c+j>=n || pic[r+i][c+j] != '@' || idx[r+i][c+j]))
                {
                    x.push(r+i);
                    y.push(c+j);
                }
        idx[r][c] = 1;
    }
}

int main()
{
    while (scanf("%d%d", &m, &n) == 2)
    {
        if(m == 0 && n == 0) break;
        memset(idx,0,sizeof(idx));
        for (int i = 0; i < m; i++)
            scanf("%s",pic[i]);
        int cnt = 0;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if(idx[i][j] == 0 && pic[i][j] == '@')
                    floodfill_bfs(i,j,++cnt);
        printf("%d\n",cnt);
    }
}
