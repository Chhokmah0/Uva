// 电子科技大学Lutece - 414
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
using namespace std;

map<int, int> vis, lvis;  //从左向右，从右向左的遍历过的状态
int ans[9];
const int dx[] = {1, -1, 0, 0}, dy[] = {0, 0, 1, -1};
int times = 0;
bool flag = false;

int encode(int list[9]) {
    int code = 0;
    for (int i = 0; i < 9; i++) {
        code = code * 10 + list[i];
    }
    return code;
}

//会返回x的位置
int uncode(int code) {
    int p;
    for (int i = 8; i >= 0; i--) {
        ans[i] = code % 10;
        if (!ans[i]) {
            p = i;
        }
        code /= 10;
    }
    return p;
}

//用一个函数来减少代码量
void move(queue<int>& q, map<int, int>& self, map<int, int>& other) {
    //提取出头数据
    int temp[9];
    int code = q.front();
    q.pop();
    //判断是否和结尾相连
    if (other.count(code)) {
        flag = true;
        times = self[code] + other[code];
        return;
    }
    int cnt = self[code];
    int p = uncode(code);
    int x = p / 3, y = p % 3;
    //扩展
    for (int i = 0; i < 4; i++) {
        memcpy(temp, ans, sizeof(ans));
        int newx = x + dx[i], newy = y + dy[i];
        if (0 <= newx && newx < 3 && 0 <= newy && newy < 3) {
            int newp = newx * 3 + newy;
            swap(temp[p], temp[newp]);
            int tcode = encode(temp);
            if (!self.count(tcode)) {//去重
                self[tcode] = cnt + 1;
                q.push(tcode);
            }
        }
    }
}

void bbfs() {
    queue<int> q, p;
    int code0 = encode(ans);
    q.push(code0);
    vis[code0] = 0;
    p.push(123456780);
    lvis[123456780] = 0;
    while (!q.empty() || !p.empty()) {
        if (!q.empty()) move(q, vis, lvis);
        if (flag) break;
        if (!p.empty()) move(p, lvis, vis);
        if (flag) break;
    }
}

bool input(){
    vis.clear();lvis.clear();
    times = 0;
    flag = false;
    for (int i = 0; i < 9; i++) {
        char ch[2];
        if(!(cin >> ch)){
            return false;
        }
        if (ch[0] == 'x') {
            ans[i] = 0;
        } else {
            ans[i] = ch[0] - '0';
        }
    }
    return true;
}
int main() {
    
    while(input()){
        bbfs();
        if (flag) {
            cout << times << endl;
        } else {
            cout << "unsolvable" << endl;
        }
    }
}
