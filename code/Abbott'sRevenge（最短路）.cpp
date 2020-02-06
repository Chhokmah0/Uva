//Uva 816
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>
#include <vector>
using namespace std;

struct Node
{
    int r;
    int c;
    int dir;

    Node(int tr,int tc,int tdir): r(tr),c(tc),dir(tdir)
    {}
};

//初始结尾
int r0,c0,r2,c2,r1,c1,dir0;
char name[25];
int distance_from_begin[10][10][4];//到开头的距离
Node* father[10][10][4];//父指针
int can_move[10][10][4][3];//可移动

const char* dirs = "NESW";
const char* turns = "FLR";
//向东南西北前进时，对行和列的变化
const int dr[4] = {-1,0,1,0};
const int dc[4] = {0,1,0,-1};



//转换dirs中的字母到数字
int dirs_id(char ch)
{
    return strchr(dirs, ch) - dirs;
}

//转换turns中的字母到数字
int turns_id(char ch)
{
    return strchr(turns, ch) - turns;
}

//判断是否在界内
bool inside(int r,int c)
{
    return (r>=1 && r <= 9 && c>=1 && c<=9);
}

//以u的朝向方向，朝turn方向前进
Node walk(const Node& u, int turn)
{
    int dir = u.dir;
    //左转或右转，朝向会发生逆时针或顺时针的改变
    if(turn == 1) 
        dir = (dir + 3) % 4;
    if(turn == 2) 
        dir = (dir + 1) % 4;
    return Node(u.r+dr[dir],u.c+dc[dir],dir);
}

//输入函数
bool input()
{
    char dir;
    
    scanf("%s",name);
    if (!strcmp(name,"END"))
        return false;
    scanf("%d%d %c %d%d",&r0,&c0,&dir,&r2,&c2);
    dir0 = dirs_id(dir);
    r1 = r0 + dr[dir0];
    c1 = c0 + dc[dir0];

    memset(can_move,0,sizeof(can_move));
    memset(father,0,sizeof(father));

    int r,c;
    char str[5];
    while(scanf("%d",&r) == 1 && r)
    {
        scanf("%d",&c);
        while(scanf("%s",str) == 1 )
        {
            if(str[0] == '*') break;
            int* point = can_move[r][c][dirs_id(str[0])];
            for (int i = 1; i < strlen(str); i++)
            {
                point[turns_id(str[i])] = 1;
            }
        }
    }
    return true;
}

//输出函数
void printans(Node end)
{
    //用向量防止栈溢出
    vector<Node> nodes;
    for (;;)
    {
        nodes.push_back(end);
        if (distance_from_begin[end.r][end.c][end.dir] == 0)
            break;
        end = *father[end.r][end.c][end.dir]; //end一直不变
    }    
    nodes.push_back(Node(r0,c0,dir0));

    //输出
    int cnt = 0;
    printf("%s\n",name);
    for (int i = nodes.size() - 1; i >= 0; i--)
    {
        if(cnt % 10 == 0)   //每十个的开头
            printf(" ");
        printf(" (%d,%d)",nodes[i].r,nodes[i].c);
        if(++cnt % 10 == 0) //每十个的结尾（也就是每十个的下一个的开头）
            printf("\n");
    }
    if(nodes.size() % 10 != 0) printf("\n");    //最后不满十个时换行 
}

//解题函数
void solve()
{
    bool flag = true;
    queue<Node> q;
    memset(distance_from_begin,-1,sizeof(distance_from_begin));
    
    //以起始后的第一点为起始，这时可以自由前进，与其他位置的点地位相同
    Node u(r1,c1,dir0);
    distance_from_begin[r1][c1][dir0] = 0;

    q.push(u);
    while(!q.empty())
    {
        Node u = q.front();q.pop();
        if(u.r == r2 && u.c == c2) 
        {
            flag = false;
            printans(u);
            break;
        }

        //遍历三个前进方向
        for (int i = 0; i < 3; i++)
        {
            Node next = walk(u,i);
            if (can_move[u.r][u.c][u.dir][i] && inside(next.r,next.c) //可移动，下一个位置不出界
                && distance_from_begin[next.r][next.c][next.dir]<0) //下一个位置尚未被访问，所以第一次访问即为最短路径（重点）
            {
                distance_from_begin[next.r][next.c][next.dir] = distance_from_begin[u.r][u.c][u.dir] + 1; //上一个位置的距离+1
                father[next.r][next.c][next.dir] = new Node(u.r,u.c,u.dir);  //父指针 (能否不分配新内存？)
                q.push(next);   //塞入队列
            }
        }
    }
    if (flag)
    {
    printf("%s\n",name);
    printf("  No Solution Possible\n");
    }
}

int main()
{
    while(input())
        solve();
    return 0;
}
