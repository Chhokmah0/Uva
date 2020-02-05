//UVa 
#include <cstdio>
#include <string>
#include <vector>
#include <iostream>
using namespace std;

int n;
vector<int> pile[30];

//寻找pile中a的位置，返回给p，h
void find_block(int a, int& p,int& h)
{
    for (p = 0; p < n; p++)
        for (h = 0; h < pile[p].size(); h++)
            if (pile[p][h] == a) return;
}

void clear(int p, int h)
{
    for (int i = h+1; i < pile[p].size(); i++)
    {
        int b = pile[p][i];
        pile[b].push_back(b);
    }
    pile[p].resize(h+1);
    return;
}

void move(int pa, int ha, int pb, int hb)
{
    for (int i = ha; i < pile[pa].size(); i++)
    {
        int temp = pile[pa][i];
        pile[pb].push_back(temp);
    }
    pile[pa].resize(ha);
    return;
}

int main(){
    cin >> n;
    int a,b;
    string s1, s2;
    for (int i = 0; i < n; i++)
    {
        pile[i].push_back(i);
    }
    

    while(cin >> s1 >> a >> s2 >> b)
    {
        int pa,pb,ha,hb;
        find_block(a,pa,ha);
        find_block(b,pb,hb);

        if (s1 == "move") clear(pa,ha);
        if (s2 == "onto") clear(pb,hb);
        move(pa,ha,pb,hb);
        for (int p = 0; p < n; p++)
        {
            printf("[%d]:",p);
            for (int h = 0; h < pile[p].size(); h++)
            {
                printf("%3d", pile[p][h]);
            }
            printf("\n");
        }
        
    }
}
