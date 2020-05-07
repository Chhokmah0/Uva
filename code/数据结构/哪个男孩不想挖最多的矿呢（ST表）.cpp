#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <deque>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>
#define MAXN 505
#define ll long long
using namespace std;
void io() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}

int m, n;
int cnt = 0;
int max0 = 1;
int a[MAXN][MAXN];
int st[MAXN][MAXN];

int gcd(int a, int b) {
    int temp;
    while (b != 0) {
        temp = a;
        a = b;
        b = temp % a;
    }
    return a;
}

int gcd(int a, int b, int c, int d) {
    int temp = gcd(a, b);
    temp = gcd(temp, c);
    temp = gcd(temp, d);
    return temp;
}

bool inside(int x, int y) { return 0 <= x && x < n && 0 <= y && y < m; }

void build_count() {
    for (int l = 2; l <= min(n, m); l++) {  //方形区域的长度
        for (int i = 0; i <= n - l; i++) {
            for (int j = 0; j <= m - l; j++) {
                st[i][j] =
                    gcd(st[i][j], st[i + 1][j], st[i][j + 1], st[i + 1][j + 1]);
                if (l & 1) {
                    int mid = l >> 1;
                    if (inside(i + mid, j + mid)) {
                        if (st[i][j] == a[i + mid][j + mid]) {
                            if (l > max0) {
                                max0 = l;
                                cnt = 0;
                            }
                            cnt++;
                        }
                    }
                }
            }
        }
    }
}

int main() {
    io();
    cin >> n >> m;
    cnt = n * m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> st[i][j];
        }
    }
    memcpy(a, st, sizeof(st));
    build_count();
    cout << max0 * max0 << endl;
    cout << cnt << endl;
}
