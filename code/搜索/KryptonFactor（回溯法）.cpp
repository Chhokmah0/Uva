//UVA - 129
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
#include <string>
using namespace std;

int n, L;

bool cmp(string str, int p1, int p2) {
    if (p1 < 0) {
        return true;
    }
    for (int i = 0; i < p2 - p1; i++) {
        if (str[p1 + i] != str[p2 + i]) {
            return cmp(str, p1 - 2, p2 - 1);
        }
    }
    return false;
}

void print(string str){
    for (int i = 1; i <= str.length(); i++)
    {
        printf("%c",str[i-1]);
        if(i%64 == 0){
            printf("\n");
        }else if(i%4 == 0 && i != str.length()){
            printf(" ");
        }
    }
    printf("\n%d\n",str.length());
}

bool dfs(string str) {
    if (str.length() > 0) {
        if (cmp(str, str.length() - 2, str.length() - 1)) {
            if (!(--n)) {
                print(str);
                return true;
            }
        } else {
            return false;
        }
    }
    
    for (int i = 0; i < L; i++) {
        if (dfs(str + char(i+'A'))) {
            return true;
        }
    }
    return false;
}

int main() {
    while (scanf("%d%d", &n, &L) == 2 && (n || L)) {
        dfs("");
    }
    return 0;
}