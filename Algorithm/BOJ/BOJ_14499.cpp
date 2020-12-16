/* [BOJ] 14499
 * Complete!
 *
 */
#include <iostream>
using namespace std;

int N, M, x, y, K;
int map[20][20] = {0};
int command[1000] = {0};
int dice[6] = {0};

void moveDice(int dir){
    if(dir == 1){
        int temp = dice[4];
        dice[4] = dice[5];
        dice[5] = dice[2];
        dice[2] = dice[0];
        dice[0] = temp;
    }else if (dir == 2){
        int temp = dice[4];
        dice[4] = dice[0];
        dice[0] = dice[2];
        dice[2] = dice[5];
        dice[5] = temp;
    }else if(dir == 3){
        int temp = dice[4];
        dice[4] = dice[1];
        dice[1] = dice[2];
        dice[2] = dice[3];
        dice[3] = temp;
    }else{
        int temp = dice[4];
        dice[4] = dice[3];
        dice[3] = dice[2];
        dice[2] = dice[1];
        dice[1] = temp;
    }
}

int main(void){
    
    cin >> N >> M >> x >> y >> K;
    for(int i = 0; i< N; i++){
        for(int j = 0; j < M; j++){
            cin >> map[i][j];
        }
    }
    for(int i = 0; i < K; i++){
        cin >> command[i];
    }
    
    for(int i = 0; i < K; i++){
        if(command[i] == 1){
            if(y + 1 > M - 1) continue;
            y = y + 1;
            moveDice(command[i]);
            if(!map[x][y]){
                map[x][y] = dice[4];
            }else{
                dice[4] = map[x][y];
                map[x][y] = 0;
            }
        }else if(command[i] == 2){
            if(y - 1 < 0) continue;
            y = y - 1;
            moveDice(command[i]);
            if(!map[x][y]){
                map[x][y] = dice[4];
            }else{
                dice[4] = map[x][y];
                map[x][y] = 0;
            }
        }else if(command[i] == 3){
            if(x - 1 < 0) continue;
            x = x - 1;
            moveDice(command[i]);
            if(!map[x][y]){
                map[x][y] = dice[4];
            }else{
                dice[4] = map[x][y];
                map[x][y] = 0;
            }
        }else{
            if(x + 1 > N - 1) continue;
            x = x + 1;
            moveDice(command[i]);
            if(!map[x][y]){
                map[x][y] = dice[4];
            }else{
                dice[4] = map[x][y];
                map[x][y] = 0;
            }
        }
        cout << dice[2] << endl;
    }
    
    return 0;
}
