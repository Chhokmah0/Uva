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
#define MAXN 100005
#define ll long long
using namespace std;
void io() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}

struct Node {
    int l, r;
    Node* ln;
    Node* rn;
    int val;

    Node() {
        ln = nullptr;
        rn = nullptr;
        val = 0;
    }
} head[100005];

int num[1000005];
int n, m;
int cnt = 0;

void bulid_tree(Node* rt, int l, int r) {
    rt->l = l;
    rt->r = r;
    if (l == r) {
        rt->val = num[l];
    } else {
        int mid = (l + r) >> 1;
        rt->ln = new Node();
        rt->rn = new Node();
        bulid_tree(rt->ln, l, mid);
        bulid_tree(rt->rn, mid + 1, r);
    }
}

void change(Node* rt, int cur, int val, Node* new_rt) {
    new_rt->l = rt->l;
    new_rt->r = rt->r;
    if (rt->l == cur && cur == rt->r) {
        new_rt->val = val;
        return;
    }
    int mid = (rt->l + rt->r) >> 1;
    if (cur <= mid) {
        new_rt->ln = new Node();
        new_rt->rn = rt->rn;
        change(rt->ln, cur, val, new_rt->ln);
    } else {
        new_rt->ln = rt->ln;
        new_rt->rn = new Node();
        change(rt->rn, cur, val, new_rt->rn);
    }
}

int find_num(Node* rt, int cur) {
    if (rt->l == cur && cur == rt->r) {
        return rt->val;
    }
    int mid = (rt->l + rt->r) >> 1;
    if (cur <= mid) {
        return find_num(rt->ln, cur);
    } else {
        return find_num(rt->rn, cur);
    }
}

int main() {
    io();
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> num[i];
    }
    bulid_tree(&head[0], 1, n);
    while (m--) {
        int flag;
        int v, x, y;
        cin >> flag;
        if (flag == 1) {
            cin >> v >> x >> y;
            cnt++;
            change(&head[v], x, y, &head[cnt]);
        } else {
            cin >> v >> x;
            int num = find_num(&head[v], x);
            cout << num << endl;
        }
    }
}
