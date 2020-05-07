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
#define MAXN 2000005
#define ll long long
using namespace std;
void io() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}

struct Node {
    int l, r;
    int lazy;
    int max;
    Node() {
        lazy = 0;
        max = 0;
    }
} node[MAXN << 2];

int a[MAXN];
int n, m;

void push_up(int id) {
    node[id].max = max(node[id << 1].max, node[id << 1 | 1].max);
}

void push_down(int id) {
    node[id << 1].lazy += node[id].lazy;
    node[id << 1 | 1].lazy += node[id].lazy;
    node[id << 1].max += node[id].lazy;
    node[id << 1 | 1].max += node[id].lazy;
    node[id].lazy = 0;
}

void build_tree(int l, int r, int id) {
    node[id].l = l;
    node[id].r = r;
    if (l == r) {
        node[id].max = a[l];
        return;
    }

    int mid = (l + r) >> 1;
    build_tree(l, mid, id << 1);
    build_tree(mid + 1, r, id << 1 | 1);
    push_up(id);
}

void add(int l, int r, int id, int val) {
    if (l <= node[id].l && node[id].r <= r) {
        node[id].max += val;
        node[id].lazy += val;
    } else {
        push_down(id);
        int mid = (node[id].l + node[id].r) >> 1;
        if (l <= mid) add(l, r, id << 1, val);
        if (r > mid) add(l, r, id << 1 | 1, val);
        push_up(id);
    }
}

void cut(int id, int cur) {
    if (node[id].l == node[id].r && cur == node[id].l) {
        node[id].max = -10000000;
    } else {
        int mid = (node[id].l + node[id].r) >> 1;
        if (cur <= mid) {
            cut(id << 1, cur);
        } else {
            cut(id << 1 | 1, cur);
        }
        push_up(id);
    }
}

int find(int l, int r, int id, int val) {
    if (node[id].max < val) {
        return -1;
    }
    if (node[id].l == node[id].r) {
        return node[id].l;
    }
    push_down(id);
    int p = -1;
    int mid = (node[id].l + node[id].r) >> 1;
    if (l <= mid) {
        p = find(l, r, id << 1, val);
        if (p < 0 && r > mid) {
            p = find(l, r, id << 1 | 1, val);
        }
        return p;
    }
    if (r > mid) {
        return find(l, r, id << 1 | 1, val);
    }
    return -1;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    build_tree(1, n, 1);
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        int s, t;
        scanf("%d%d", &s, &t);
        s++;
        int p = find(s, n, 1, t);
        if (p < 0) {
            p = find(1, s - 1, 1, t);
            if (p >= 0) {
                cut(1, p);
                printf("%d\n", n - s + p);
            } else {
                printf("%d\n", p);
            }
        } else {
            cut(1, p);
            printf("%d\n", p - s);
        }
        add(1, n, 1, 1);
    }
}
