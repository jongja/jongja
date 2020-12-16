/* [BOJ] 15685
 * Complete!
 *
 */

#include <iostream>
#include <stack>
#include <queue>
using namespace std;

int N;
int x, y, d, g;
int input[20][4];
int map[101][101] = {0};
int dir[4][2] = {{0, 1}, {-1, 0}, {0, -1}, {1, 0}};

int countSquare(){
    int count = 0;
    for(int i = 0; i < 101; i++){
        for(int j = 0; j < 101; j++){
            if(i + 1 > 100 || j + 1 > 100) continue;
            if(map[i][j] && map[i+1][j] && map[i][j+1] && map[i+1][j+1]) count++;
        }
    }
    return count;
}

int changeDir(int dir){
    if(dir == 0){
        return 1;
    }else if(dir == 1){
        return 2;
    }else if(dir == 2){
        return 3;
    }else{
        return 0;
    }
}

void DrawMap(stack<pair<int, pair<int, int> > > s, int gen, int cur){
    if(cur > gen) return;
    stack<pair<int, pair<int, int> > > s2;
    if(cur == 0){
        int x = s.top().second.first;
        int y = s.top().second.second;
        int d = s.top().first;
        s.pop();
        map[x][y] = gen + 1;
        map[x + dir[d][0]][y + dir[d][1]] = gen + 1;
        s2.push(make_pair(d, make_pair(x + dir[d][0], y + dir[d][1])));
    }else{
        queue<pair<int, pair<int, int> > > q;
        stack<pair<int, pair<int, int> > > s1;
        int x = s.top().second.first;
        int y = s.top().second.second;
        while(!s.empty()){
            int d = s.top().first;
            s.pop();
            s1.push(make_pair(d, make_pair(x, y)));
            d = changeDir(d);
            map[x + dir[d][0]][y + dir[d][1]] = gen + 1;
            q.push(make_pair(d, make_pair(x + dir[d][0], y + dir[d][1])));
            x = x + dir[d][0]; y = y + dir[d][1];
        }
        while(!s1.empty()){
            s2.push(make_pair(s1.top().first, make_pair(s1.top().second.first, s1.top().second.second)));
            s1.pop();
        }
        while(!q.empty()){
            s2.push(make_pair(q.front().first, make_pair(q.front().second.first, q.front().second.second)));
            q.pop();
        }
    }
    DrawMap(s2, gen, cur + 1);
    return;
}

int main(void){
        cin >> N;
        for(int i = 0; i < N; i++){
            cin >> x >> y >> d >> g;
            input[i][0] = x; input[i][1] = y; input[i][2] = d; input[i][3] = g;
        }
    
    for(int i = 0; i < N; i++){
        stack<pair<int, pair<int, int> > > s;
        s.push(make_pair(input[i][2], make_pair(input[i][1], input[i][0])));
        DrawMap(s, input[i][3], 0);
    }
    
    cout << countSquare() << endl;
    return 0;
}
