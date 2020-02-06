//UVa 699
#include <cstdio>
#include <cstring>
int sum[1000000];

//前序遍历的递归建树
bool build(int p)
{
    int v;
    scanf("%d",&v);
    if (v == -1) 
        return false;
    sum[p] += v;
    build(p-1);
    build(p+1);
    return true;
}

int main()
{
    int t = 0;
    while(build(500000))
    {
        t++;
        printf("Case %d:\n", t);
        int p = 0;
        while(sum[p] == 0) 
            p++;
        while(1)
        {
            if(sum[p] == 0) 
                break;
            printf("%d",sum[p]);
            p++;
            if(sum[p] != 0)
                printf(" ");
        }
        printf("\n\n");
        //数组清空
        memset(sum,0,sizeof(sum));
    }
    return 0;
}
