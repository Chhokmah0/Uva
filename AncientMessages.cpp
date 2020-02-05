#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 200 + 5;

char pic[maxn][maxn];//图本身
int kase = 0;
int h, w, idx[maxn][maxn];//idx == 连通图的id
const char* htob[16] = {
    "0000","0001","0010","0011",
    "0100","0101","0110","0111",
    "1000","1001","1010","1011",
    "1100","1101","1110","1111"
};
const char int_to_char[6] = {'W','A','K','J','S','D'};

int char_to_int(char ch)
{
    if (ch >= '0' && ch <= '9')
        return ch - '0';
    else
        return ch - 'a' + 10;
}

void floodfill(int r, int c, int id)
{
    
    char ch = pic[r][c];
    idx[r][c] = id;
    for (int i = -1; i <= 1; i++)
        for (int j = -1; j <= 1; j++)
            if (r+i >= 0 && r+i <= h+2 && c+j >= 0 && c+j <= w+2)//未出界
                if(idx[r+i][c+j] != id && pic[r+i][c+j] == ch)
                    floodfill(r+i,c+j,id);
    return;
}

int findhollow(int r, int c)
{
    idx[r][c] = 3;//防止多次findhollow
    int cnt = 0;

    //有空头，不可能出界
    for (int i = -1; i <= 1; i++)
        for (int j = -1; j <= 1; j++)
        {
            if(!idx[r+i][c+j])
            {
                floodfill(r+i,c+j,-1);
                cnt++;
            }
            if(idx[r+i][c+j] == 1)
                cnt += findhollow(r+i,c+j);
        }
    return cnt;
}


int main()
{
    while(scanf("%d%d", &h, &w) == 2 && (h || w))
    {
        //多次循环时要清空
        memset(pic,'0',sizeof(pic));
        memset(idx,0,sizeof(idx));
        
        //读入图像，并在外围多加一圈0
        *(pic[0]+4*w+2) = '\0';//左右各加一列，所以+2
        *(pic[h+1]+4*w+2) = '\0';
        for (int i = 1; i <= h; i++)
        {
            char line[30];
            scanf("%s",line);
            char* str = pic[i]+1;
            for (int j = 0; j < w; j++)
            {
                memcpy(str,htob[char_to_int(line[j])],4*sizeof(char));
                str += 4;
            }
            *(str+1) = '\0';
        }
        
        //主要运行代码
        w *= 4;
        floodfill(0,0,2);
        int n=0;
        int cnt[55];
        for (int i = 0; i < h+2; i++)
        {
            for (int j = 0; j < w+2; j++)
            {
                if (pic[i][j]=='1' && !idx[i][j])
                {
                    floodfill(i,j,1);
                    cnt[n++] = findhollow(i,j);
                }
            }
        }

        //转换，排序
        char cha[55];
        for (int i = 0; i < n; i++)
            cha[i] = int_to_char[cnt[i]];
        sort(&cha[0],&cha[n]);

        //输出
        printf("Case %d: ",++kase);
        for (int i = 0; i < n; i++)
        {
            printf("%c",cha[i]);
        }
        printf("\n");
        
        
        /*
        //打印出图像和id
        for (int i = 0; i < h+2; i++)
            printf("%s\n",pic[i]);
        for (int i = 0; i < h+2; i++)
        {
            for (int j = 0; j < w+2; j++)
                printf("%d",idx[i][j]);
            printf("\n");
        }
        */
    }
}
