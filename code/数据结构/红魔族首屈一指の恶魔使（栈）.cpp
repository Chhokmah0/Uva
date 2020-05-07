#include <cstdio>
#include <cstring>
#include <iostream>
#include <stack>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
#define MAXN 1000005
using namespace std;

int T,N;
char str[MAXN];

int main(){
    scanf("%d",&T);
    for (int i = 0; i < T; i++){
        scanf("%d",&N);
        if(N==0){
            printf("0\n");
            continue;
        }else{
            scanf("%s",str);
        }
        int count = 0,times = 0;
        for (int j = 0; j < N; j++)
        {
            if(str[j] == '('){
                count++;
            }else{
                if(count>0){
                    count--;
                }else{
                    times++;
                }
            }
        }
        times += count;
        printf("%d\n",times);
    }
}
