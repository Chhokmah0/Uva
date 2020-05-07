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
void io() { ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr); }
int n,cnt = 1;
int vistied[MAXN];
int a[MAXN];

int main(){
    scanf("%d",&n);
    for (int i = 1; i <= n; i++){
        scanf("%d",&a[i]);
    }
    for (int i = 1; i <= n; i++)
    {
        if(!vistied[i]){
            int u = i;
            while(!vistied[u]){
                vistied[u] = cnt;
                u = a[u];
            }
            if(vistied[u] == cnt){
                cnt++;
            }else{
                int v = i;
                while(vistied[v] != vistied[u]){
                    vistied[v] = vistied[u];
                    v = a[v];
                } 
            }
        }
    }
    
    printf("%d\n",cnt-1);
}
