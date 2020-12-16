/* [BOJ] 12100
 * Complete!
 *
 */

#include <iostream>
#include <queue>
using namespace std;

int N = 0;
int Max = 0;

int findMax(int map[20][20]){
    int res = 0;
    for(int i = 0; i<N; i++){
        for(int j = 0; j<N; j++){
            if(map[i][j] > res)
                res = map[i][j];
        }
    }
    return res;
}

void printMap(int map[20][20]){
    for(int i = 0; i<N; i++){
        for(int j = 0; j<N; j++){
            cout << map[i][j] << " ";
        }
        cout << endl;
    }
    
}

void copyMap(int dest[20][20], int src[20][20]){
    for(int i = 0; i<N; i++){
        for(int j = 0; j<N; j++){
            dest[i][j] = src[i][j];
        }
    }
}

void start(int step, int dir, int map[20][20]){
    if(step == 5){
        int compare = findMax(map);
        if(compare > Max) Max = compare;
        return;
    }
    int pre_map[20][20];
    queue<int> q;
    
    if(dir == 0){ // up
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                if(map[j][i]) q.push(map[j][i]);
            }
            int cur = 0;
            int pre_check = 0;
            while(!q.empty()){
                int num = q.front();
                q.pop();
                if(cur >= 1 && map[cur - 1][i] == num && !pre_check){
                    map[cur - 1][i] *= 2;
                    pre_check = 1;
                }else{
                    map[cur][i] = num;
                    cur++;
                    pre_check = 0;
                }
            }
            while(cur < N){
                map[cur++][i] = 0;
            }
        }
    }
    else if(dir == 1){ // right
        for(int i = N-1; i >= 0; i--){
            for(int j = N-1; j >= 0; j--){
                if(map[i][j]) q.push(map[i][j]);
            }
            int cur = N - 1;
            int pre_check = 0;
            while(!q.empty()){
                int num = q.front();
                q.pop();
                if(cur < N - 1 && map[i][cur + 1] == num && !pre_check){
                    map[i][cur + 1] *= 2;
                    pre_check = 1;
                }else{
                    map[i][cur] = num;
                    cur--;
                    pre_check = 0;
                }
            }
            while(cur >= 0){
                map[i][cur--] = 0;
            }
        }
    }
    else if(dir == 2){ // down
        for(int i = N-1; i >= 0; i--){
            for(int j = N-1; j >= 0; j--){
                if(map[j][i]) q.push(map[j][i]);
            }
            int cur = N - 1;
            int pre_check = 0;
            while(!q.empty()){
                int num = q.front();
                q.pop();
                if(cur < N - 1 && map[cur + 1][i] == num && !pre_check){
                    map[cur + 1][i] *= 2;
                    pre_check = 1;
                }else{
                    map[cur][i] = num;
                    cur--;
                    pre_check = 0;
                }
            }
            while(cur >= 0){
                map[cur--][i] = 0;
            }
        }
    }
    else if(dir == 3){ // left
        for(int i = 0; i<N; i++){
            for(int j = 0; j<N; j++){
                if(map[i][j]) q.push(map[i][j]);
            }
            int cur = 0;
            int pre_check = 0;
            while(!q.empty()){
                int num = q.front();
                q.pop();
                if(cur >=1 && map[i][cur - 1] == num && !pre_check){
                    map[i][cur - 1] *= 2;
                    pre_check = 1;
                }else{
                    map[i][cur] = num;
                    cur++;
                    pre_check = 0;
                }
            }
            while(cur < N){
                map[i][cur++] = 0;
            }
        }
    }
    for(int i = 0; i<4; i++){
        copyMap(pre_map, map);
        start(step + 1, i, map);
        copyMap(map, pre_map);
    }
}

int main(){
    int map[20][20];
    cin >> N;
    for(int i = 0; i<N; i++)
        for(int j = 0; j<N; j++)
            cin >> map[i][j];
    int pre_map[20][20];
    for(int i = 0; i<4; i++){
        copyMap(pre_map, map);
        start(0,i,map);
        copyMap(map, pre_map);
    }
    cout << Max;
}

