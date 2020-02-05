#include <cstdio>
#include <cstring>
int last, cur, next[100005];
char s[100005];

int main()
{
    
    while(scanf("%s",s+1) == 1)
    {
        cur = last = 0;
        int len = strlen(s+1);
        next[0] = 0;

        for (int i = 0; i <= len; i++)
        {
            char ch = s[i];
            if(ch == '[') 
                cur = 0;
            else if(ch == ']') 
                cur = last;
            else{//在cur处插入i
                next[i] = next[cur];//让 i 的下一个是原本 cur 指向的下一个
                next[cur] = i;//让 cur 的下一个指向 i
                if(cur == last) last = i;
                cur = i;
            }
        }
        
        for(int i = next[0]; i != 0; i = next[i])
            printf("%c",s[i]);
        printf("\n");
    }
}
