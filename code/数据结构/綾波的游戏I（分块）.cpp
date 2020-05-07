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
#define MAXN 100005
#define ll long long
using namespace std;
void io() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}

int num[MAXN];
int block[320][MAXN];
int n, m, k, cnt, len, temp;

int mod(int x) {
    x %= k;
    if (x < 0) {
        x += k;
    }
    return x;
}

int main() {
    int l, r, c, d;
    scanf("%d%d", &n, &k);
    len = ceil(sqrt(n));
    for (int i = 1; i <= n; i++) {
        scanf("%d", &temp);
        temp = mod(temp);
        num[i] = temp;
        block[i / len][temp]++;
    }
    scanf("%d", &m);
    while (m--) {
        cnt = 0;
        scanf("%d%d%d%d", &l, &r, &c, &d);
        int p1 = l / len;
        int p2 = r / len;
        c = mod(c);
        d = mod(d);
        if (p1 == p2) {
            for (int i = l; i <= r; i++) {
                if (mod(num[i] + block[i / len][k]) == c) {
                    cnt++;
                }
                block[i / len][num[i]]--;
                num[i] += d;
                num[i] = mod(num[i]);
                block[i / len][num[i]]++;
            }
        } else {
            for (int i = l; i < (p1 + 1) * len; i++) {
                if (mod(num[i] + block[i / len][k]) == c) {
                    cnt++;
                }
                block[i / len][num[i]]--;
                num[i] += d;
                num[i] = mod(num[i]);
                block[i / len][num[i]]++;
            }
            for (int i = p2 * len; i <= r; i++) {
                if (mod(num[i] + block[i / len][k]) == c) {
                    cnt++;
                }
                block[i / len][num[i]]--;
                num[i] += d;
                num[i] = mod(num[i]);
                block[i / len][num[i]]++;
            }
            for (int p = p1 + 1; p < p2; p++) {
                cnt += block[p][mod(c - block[p][k])];
                block[p][k] += d;
                block[p][k] = mod(block[p][k]);
            }
        }

        printf("%d\n", cnt);
    }
}