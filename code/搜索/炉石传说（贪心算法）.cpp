// 电子科技大学Lutece -2329
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
using namespace std;

int n,X,Y;
int moves = 0;
vector<int> monster;

int main(){
    cin >> n >> X >> Y;
    for (int i = 0; i < n; i++){
        int temp;
        cin >> temp;
        monster.push_back(temp);
    }

    while(monster.size()){
        moves++;
        vector<int> tempY = monster,tempX = monster;
        int max = -1, p = 0, dx = 0, dy = 0;
        for (int i = 0; i < monster.size(); i++)
        {
            dx += (tempX[i] > X) ? X : tempX[i];
            if(tempY[i] > max){
                max = tempY[i];
                p = i;
            }
        }
        dy = (tempY[p] > Y)? Y : tempY[p];
        if((tempY[p] -= Y) <= 0){
            tempY.erase(tempY.begin() + p);
        }
        vector<int>::iterator itr = tempX.begin();
        while(!(itr == tempX.end())){
            *itr -= X;
            if(*itr <= 0){
                tempX.erase(itr);
            }else{
                itr++;
            }
        }
        monster = (dx > dy)? tempX : tempY;
    }

    cout << moves << endl;
}
