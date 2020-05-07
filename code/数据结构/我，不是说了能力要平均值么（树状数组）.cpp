#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>
#define MAXN 200005
using namespace std;
long long n, k;
long long s[MAXN];

long long notIncrease(long long* num, int length) {
    if (length == 1) {
        return 0;
    }
    int p = length / 2;
    long long front = notIncrease(num, p);
    long long end = notIncrease(num + p, length - p);
    long long mid = 0;
    int p1 = 0, p2 = p;
    while (p1 != p && p2 < length) {
        if (num[p1] >= num[p2]) {
            mid += length - p2;
            p1++;
        } else {
            p2++;
        }
    }
    sort(num, num + length, greater<long long>());
    return front + mid + end;
}

long long gcd(long long a, long long b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

int main() {
    scanf("%lld%lld", &n, &k);
    memset(s,0,sizeof(s));
    for (int i = 1; i <= n; i++) {
        long long temp;
        scanf("%lld", &temp);
        s[i] = temp - k + s[i - 1];
    }
    long long cnt = notIncrease(s, n + 1);
    long long all = ((n + 1) * n) / 2;
    long long temp = gcd(all, cnt);
    printf("%lld/%lld\n", cnt / temp, all / temp);
    return 0;
}
