/* [BOJ] 16234
 * Complete!
 *
 */

#include <iostream>
#include <queue>
using namespace std;

int N, L, R;

int isUnion(int a, int b){
    int result = a - b;
    if(result < 0) result *= -1;
    if(result >= L && result <= R)
        return 1;
    else
        return 0;
}

int findUnion(int uni[50][50], int map[50][50]){
    int res = 0;
    queue<pair<int, int> > q;
    int group_num = 1;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(!uni[i][j]){
                q.push(make_pair(i, j));
                while(!q.empty()){
                    int x = q.front().first;
                    int y = q.front().second;
                    q.pop();
                    if(x - 1 >= 0 && !uni[x - 1][y] && isUnion(map[x][y], map[x - 1][y])){
                        res = 1;
                        q.push(make_pair(x-1, y));
                        uni[x - 1][y] = group_num;
                    }
                    if(x + 1 < N && !uni[x + 1][y] && isUnion(map[x][y], map[x + 1][y])){
                        res = 1;
                        q.push(make_pair(x+1, y));
                        uni[x + 1][y] = group_num;
                    }
                    if(y + 1 < N && !uni[x][y + 1] && isUnion(map[x][y], map[x][y + 1])){
                        res = 1;
                        q.push(make_pair(x, y + 1));
                        uni[x][y + 1] = group_num;
                    }
                    if(y - 1 >= 0 && !uni[x][y - 1] && isUnion(map[x][y], map[x][y - 1])){
                        res = 1;
                        q.push(make_pair(x, y - 1));
                        uni[x][y - 1] = group_num;
                    }
                }
                if(res) group_num++;
            }
        }
    }
    return res;
}

void startUnion(int uni[50][50], int map[50][50], int cur_x, int cur_y, int group){
    int result = 0;
    int count = 0;
    queue<pair<int,int> > q;
    queue<pair<int,int> > ch;
    
    q.push(make_pair(cur_x, cur_y));
    ch.push(make_pair(cur_x, cur_y));
    uni[cur_x][cur_y] = 0;
    
    while(!q.empty()){
        int x = q.front().first;
        int y = q.front().second;
        q.pop();
        result += map[x][y];
        count++;
        if(x - 1 >= 0 && uni[x - 1][y] == group){
            q.push(make_pair(x-1, y));
            ch.push(make_pair(x-1, y));
            uni[x-1][y] = 0;
        }
        if(x + 1 < N && uni[x + 1][y] == group){
            q.push(make_pair(x+1, y));
            ch.push(make_pair(x+1, y));
            uni[x+1][y] = 0;
        }
        if(y + 1 < N && uni[x][y + 1] == group){
            q.push(make_pair(x, y + 1));
            ch.push(make_pair(x, y + 1));
            uni[x][y + 1] = 0;
        }
        if(y - 1 >= 0 && uni[x][y - 1] == group){
            q.push(make_pair(x, y - 1));
            ch.push(make_pair(x, y - 1));
            uni[x][y-1] = 0;
        }
    }
    int people = result / count;
    while(!ch.empty()){
        int x = ch.front().first;
        int y = ch.front().second;
        ch.pop();
        map[x][y] = people;
    }
}

void printMap(int map[50][50]){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cout << map[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int main(void){
    int map[50][50] = {0};
    int uni[50][50] = {-1};
    cin >> N >> L >> R;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cin >> map[i][j];
            uni[i][j] = 0;
        }
    }
    
    int move = 0;
    while(findUnion(uni, map)){
        for(int i = 0; i<N; i++){
            for(int j = 0; j<N; j++){
                if(uni[i][j]){
                    startUnion(uni, map, i, j, uni[i][j]);
                }
            }
        }
        move++;
    }
    cout << move << endl;
}

