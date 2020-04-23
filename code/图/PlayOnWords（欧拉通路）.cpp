// Uva 10129
//该题有可能出现两个欧拉通路，一个有确切入点而另一个没有，所以需要实际走过一边看是否可以全部通过

#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <cctype>
#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;

const int maxn = 1000 + 5;
int G[26][26];//路
int in_out[26];//某点出入次数

//转换
int char_to_int(char ch)
{
    return ch - 'a';
}

//输入函数
void input()
{
    memset(G,0,sizeof(G));
    memset(in_out,0,sizeof(in_out));
    int n;
    scanf("%d", &n);
    char word[maxn];
    while(n--)
    {
        scanf("%s", word);
        int len = strlen(word);
        int begin = char_to_int(word[0]);
        int end = char_to_int(word[len-1]);
        G[begin][end]++;
        in_out[begin]++;
        in_out[end]--;
    }

}

//找一个起点
int find_begin()
{
    for (int i = 0; i < 26; i++)
        if(in_out[i] == 1)
            return i;
    return -1;
}

//欧拉通路
void euler(int u)
{
    for (int v = 0; v < 26; v++)
        if (G[u][v])
        {
            G[u][v]--;
            euler(v);
        }
}

//判断函数
bool judge()
{
    //只有一个入点和一个出点，或任意点都可以做入点
    int flag_begin = 0;
    int flag_end = 0;
    for (int i = 0; i < 26; i++)
    {
        int num = in_out[i];
        if (num  > 1 || num < -1)
            return false;
        if (num == 1)
            flag_begin++;
        if (num == -1)
            flag_end++;
    }
    if(!(flag_begin + flag_end == 0 ||flag_begin + flag_end == 2))
        return false;
    
    //所有的路都被走过
    for (int u = 0; u < 26; u++)
        for (int v = 0; v < 26; v++)
            if (G[u][v])
                return false;
    return true;    
}

int main()
{
    int n;
    scanf("%d", &n);
    while(n--)
    {
        input();
        int begin = find_begin();
        if (begin >= 0)
            euler(begin);
        else
            euler(0);
        
        if(judge())
            printf("Ordering is possible.\n");
        else
            printf("The door cannot be opened.\n");      
    }
}

