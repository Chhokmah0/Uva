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
using namespace std;
void io() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}

int num[MAXN];
int cnt[MAXN];     //储存某个值出现的次数
deque<int> dq;     //储存最小子串
bool alpha[MAXN];  //储存子串中已经有的数字
int n, k;

int main() {
    io();
    cin >> n >> k;
    memset(num,0,sizeof(num));
    memset(cnt,0,sizeof(cnt));
    memset(alpha,0,sizeof(alpha));
    dq.clear();
    for (int i = 0; i < n; i++) {
        cin >> num[i];
        cnt[num[i]]++;
    }
    for (int i = 0; i < n; i++) {
        cnt[num[i]]--;
        if(num[i]<= 0 || num[i] > k){
            cout << "Kanade" << endl;
            return 0;
        }
        if (alpha[num[i]]) {
            continue;
        }
        while (!dq.empty() && num[i] < dq.back() && cnt[dq.back()]) {
            alpha[dq.back()] = false;
            dq.pop_back();
        }
        dq.push_back(num[i]);
        alpha[num[i]] = true;
    }
    if (dq.size() < k) {
        cout << "Kanade" << endl;
    } else {
        for (int i = 0; i < k; i++) {
            cout << dq[i];
            if (i != k) {
                cout << ' ';
            } else {
                cout << endl;
            }
        }
    }
}
