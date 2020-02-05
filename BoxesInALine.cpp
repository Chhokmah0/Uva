#include <cstdio>
#include <cstring>

const int max = 100000 + 5;
int left[max], right[max]; //双向链表

/*
struct 链表
{
    int number;
    struct 链表 * left;
    struct 链表 * right;
};
*/




//链接左右
void link(int L, int R)
{
    left[R] = L;
    right[L] = R;
}

int main()
{
    int kase = 0;//次数
    int n, m;
    while (scanf("%d%d", &n, &m) == 2)
    {
        //初始化双向链表
        for (int i = 1; i <= n; i++)
        {
            left[i] = i-1;
            right[i] = i+1;
        }
        right[n] = 0;
        right[0] = 1;
        left[0] = n;
        
        //inv 记录操作4    
        int inv = 0;
        while (m--)
        {
            int op;
            scanf("%d", &op);

            if (op == 4)
            {
                inv = !inv;
                continue;
            }
            //3不受4影响，1和2受4影响对称交换
            else if (op != 3 && inv == 1)
                op = 3 - op;

            int x, y;
            scanf("%d%d", &x, &y);
            int lx = left[x], rx = right[x], ly = left[y], ry = right[y];//记录原来的x，y在链表中的位置
            
            //x和y相邻时特别考虑
            switch (op)
            {
            case 1:
                if(x == ly)
                    continue;
                link(lx, rx);
                link(ly, x);
                link(x, y);
                break;
            case 2:
                if(x == ry)
                    continue;
                link(lx, rx);
                link(x, ry);
                link(y, x);
                break;
            case 3:
                if (rx == y)
                {
                    link(lx, y);
                    link(y, x);
                    link(x, ry);
                }
                else if (lx == y)
                {
                    link(ly, x);
                    link(x, y);
                    link(y, rx);
                }
                else
                {
                    link(ly, x);
                    link(x, ry);
                    link(lx, y);
                    link(y, rx);
                }
                break;
            }
        }
        int b = 0;
        long long int sum = 0;
        for (int i = 1; i <= n; i++)
        {
            b = right[b];
            if(i % 2 == 1)
                sum += b;
        }
        //奇数则4不影响结果
        //如果是偶数则4会使sum正好为总和的另一半
        if(inv && n % 2 == 0)
            sum = (long long int) n*(n+1)/2 - sum;
        
        printf("Case %d: %lld\n", ++kase, sum);
    }
}
