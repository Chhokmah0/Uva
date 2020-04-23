// Uva 536

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

char pre[30], in[30];


void post(int p1, int p2, int i1, int i2)
{
    char root = pre[p1];

    int i = strchr(in, root) - in;  //根的位置
    int ll = i - i1;    //左子树的长度
    int rl = i2 - i;    //右子树的长度
    
    //后序输出
    if (ll) //左子树存在
        post(p1+1, p2-rl, i1, i-1);
    if (rl) //右子树存在
        post(p1+1+ll, p2, i+1, i2);
    printf("%c",root);  //父节点
}

int main()
{
    while (scanf("%s%s", pre, in) == 2)
    {
        int len = strlen(pre);
        post(0,len-1,0,len-1);
        printf("\n");
    }
}
