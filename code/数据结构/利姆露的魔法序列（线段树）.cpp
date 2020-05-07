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
#define MAXN 1000005
#define ll long long
using namespace std;
void io() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}
int n;
string s;
char str[MAXN];       //括号串
int cnt = 0;          //用于计数左括号和右括号
int cur = MAXN >> 1;  //光标
struct Node {
    int l, r;
    int min, max;
    int lazy;

    Node() {
        min = 0;
        max = 0;
        lazy = 0;
    }
} node[MAXN << 2];

int c2i(char ch) {
    switch (ch) {
        case '(':
            return 1;
        case ')':
            return -1;
    }
    return 0;
}

void pushUp(int id) {
    node[id].min = min(node[id << 1].min, node[id << 1 | 1].min);
    node[id].max = max(node[id << 1].max, node[id << 1 | 1].max);
}

void pushDown(int id) {
    if (node[id].lazy) {
        node[id << 1].lazy += node[id].lazy;
        node[id << 1 | 1].lazy += node[id].lazy;
        node[id << 1].min += node[id].lazy;
        node[id << 1].max += node[id].lazy;
        node[id << 1 | 1].min += node[id].lazy;
        node[id << 1 | 1].max += node[id].lazy;
        node[id].lazy = 0;
    }
}

void bulid(int l, int r, int id) {
    node[id].l = l;
    node[id].r = r;
    if (l == r) {
        return;
    } else {
        int mid = (l + r) >> 1;
        bulid(l, mid, id << 1);
        bulid(mid + 1, r, id << 1 | 1);
    }
}

void update(int l, int r, int id, int val) {
    if (l <= node[id].l && r >= node[id].r) {
        node[id].min += val;
        node[id].max += val;
        node[id].lazy += val;
    } else {
        if (node[id].lazy) {
            pushDown(id);
        }
        int mid = (node[id].l + node[id].r) >> 1;
        if (r <= mid) {
            update(l, r, id << 1, val);
        } else if (l > mid) {
            update(l, r, id << 1 | 1, val);
        } else {
            update(l, r, id << 1, val);
            update(l, r, id << 1 | 1, val);
        }
        pushUp(id);
    }
}

int main() {
    io();
    bulid(1, MAXN, 1);
    cin >> n;
    cin >> s;
    for (int i = 0; i < n; i++) {
        char ch = s[i];
        if (ch == 'R') {
            cur++;
        } else if (ch == 'L') {
            cur--;
        } else {
            int val = c2i(ch) - c2i(str[cur]);
            cnt += val;
            str[cur] = ch;
            update(cur, MAXN, 1, val);
        }

        if (cnt == 0) {
            if (node[1].min >= 0) {
                cout << node[1].max;
            } else {
                cout << -1;
            }
        } else {
            cout << -1;
        }
        if (i != n - 1) {
            cout << ' ';
        } else {
            cout << endl;
        }
    }
}
