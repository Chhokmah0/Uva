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
#define MAXN 1000005
#define ll long long
using namespace std;
void io() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}

struct Node {
    int max;
    int l, r;
} node[MAXN << 2];

int num[MAXN];
int T, n, m, l, r, k;

void push_up(int id) {
    node[id].max = max(node[id << 1].max, node[id << 1 | 1].max);
}

void build_tree(int id, int l, int r) {
    node[id].l = l;
    node[id].r = r;
    if (l == r) {
        node[id].max = num[l];
    } else {
        int mid = (l + r) >> 1;
        build_tree(id << 1, l, mid);
        build_tree(id << 1 | 1, mid + 1, r);
        push_up(id);
    }
}

int find_change(int id, int l, int r, int val) {
    if (node[id].max < val) {
        return -1;
    }
    if (node[id].l == node[id].r) {
        node[id].max -= val;
        return node[id].l;
    }

    int mid = (node[id].l + node[id].r) >> 1;
    int p = -1;
    if (l <= mid) {
        p = find_change(id << 1, l, r, val);
        if (p < 0 && r > mid) {
            p = find_change(id << 1 | 1, l, r, val);
        }
        push_up(id);
        return p;
    }
    if (r > mid) {
        p = find_change(id << 1 | 1, l, r, val);
        push_up(id);
        return p;
    }
    return -1;
}

int main() {
    io();
    scanf("%d",&T);
    while (T--) {
        scanf("%d%d",&n,&m);
        for (int i = 1; i <= n; i++) {
            scanf("%d",&num[i]);
        }
        build_tree(1, 1, n);
        while (m--) {
            scanf("%d%d%d",&l,&r,&k);
            printf("%d\n",find_change(1,l,r,k));
        }
    }
}
