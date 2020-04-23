//UVa 1600
#include <cstdlib>
#include <queue>
#include <cstring>
#include <cstdio>
int map[25][25];
bool visited[25][25];
int id[25][25],times[25][25], r, c, k;
int dx[] = {1,0,0,-1};
int dy[] = {0,1,-1,0};
using namespace std;

void read() {
    memset(visited,0,sizeof(visited));
    memset(times,0,sizeof(times));
    memset(id,0,sizeof(id));
    scanf("%d%d", &r, &c);
    scanf("%d", &k);
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            scanf("%d", &map[i][j]);
        }
    }
}

inline bool inside(int x, int y) {
    return (x >= 0 && x < r && y >= 0 && y < c);
}

void printvisit(){
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            printf("%d ",visited[i][j]);
        }
        printf("\n");
    }
}

void printid(){
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            printf("%d ",id[i][j]);
        }
        printf("\n");
    }
}

void bfs(){
    queue<int> qx,qy;
    qx.push(0);qy.push(0);
    id[0][0] = k;
    times[0][0] = 0;
    visited[0][0] = true;
    while(!qx.empty()){
        int x0 = qx.front();qx.pop();
        int y0 = qy.front();qy.pop();
        for (int i = 0; i < 4; i++){
            int x = x0+dx[i], y = y0+dy[i];
            if(inside(x,y)){
                if(map[x][y]){
                    if(id[x0][y0]){
                        if(id[x][y] < id[x0][y0] - 1){
                            id[x][y] = id[x0][y0] - 1;
                        }
                        if(!visited[x][y]){
                            qx.push(x);qy.push(y);
                            times[x][y] = times[x0][y0] + 1;
                            visited[x][y] = true;
                        }
                    }
                }else{
                    id[x][y] = k;
                    if(!visited[x][y]){
                        qx.push(x);qy.push(y);
                        times[x][y] = times[x0][y0] + 1;
                        visited[x][y] = true;
                    }
                }
            }
        }
        // printvisit();
        // printf("\n");
        // printid();
        // printf("\n");
    }
}

int main() {
    int t;
    scanf("%d",&t);
    while(t--){
        read();
        bfs();
        printf("%d\n",times[r-1][c-1] ? times[r-1][c-1] : -1);
    }
}
