// UVA - 129
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <vector>
using namespace std;

set<char> alpha, graph[26];
vector<char> tans, ans;
bool visited[26];
int place[26];
int minM;

inline int c2i(char ch) { return ch - 'A'; }

void buildGraph(string str, int& i) {
    char ch = str[i++];
    alpha.insert(ch);
    if(str[i] != ':'){
        return;
    }
    i++;
    for (; i < str.length(); i++) {
        if (str[i] != ';') {
            alpha.insert(str[i]);
            graph[c2i(ch)].insert(str[i]);
            graph[c2i(str[i])].insert(ch);
        } else {
            return;
        }
    }
    return;
}

void dfs(int cnt) {
    if (cnt == alpha.size()) {
        int tmax = 0;
        for (char u : tans) {
            for (char v : graph[c2i(u)]) {
                int temp = abs(place[c2i(u)] - place[c2i(v)]);
                if (temp >= minM) {
                    return;
                }
                if (temp > tmax) {
                    tmax = temp;
                }
            }
        }
        ans = tans;
        minM = tmax;
    }

    for (char ch : alpha) {
        if (!visited[c2i(ch)]) {
            visited[c2i(ch)] = !visited[c2i(ch)];
            tans.push_back(ch);
            place[c2i(ch)] = cnt;
            dfs(cnt + 1);
            place[c2i(ch)] = 0;
            tans.pop_back();
            visited[c2i(ch)] = !visited[c2i(ch)];
        }
    }
}

int main() {
    string str;
    while (getline(cin, str) && str[0] != '#') {
        minM = 9999;
        memset(place, 0, sizeof(place));
        memset(visited, 0, sizeof(visited));
        alpha.clear();
        tans.clear();
        ans.clear();
        for (auto& u : graph) { //要清空set得要传递引用
            u.clear();
        }

        for (int i = 0; i < str.length(); i++) {
            buildGraph(str, i);
        }

        dfs(0);
        for (char ch : ans) {
            cout << ch << ' ';
        }
        cout << "-> " << minM << endl;
    }
}
