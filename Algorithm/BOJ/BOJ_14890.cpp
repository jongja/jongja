/* [BOJ] 14890
 * Complete!
 *
 */


#include <iostream>
#include <queue>
using namespace std;

int N;
int L;

void RemoveBridge(int mode, int line, int Bridge[100][100]){
    if(!mode){
        for(int i = 0; i < N; i++){
            Bridge[line][i] = 0;
        }
    }else{
        for(int i = 0; i< N ; i++){
            Bridge[i][line] = 0;
        }
    }
}

void printMap(int map[100][100]){
    for(int i = 0; i<N; i++){
        for(int j = 0; j <N; j++){
            cout << map[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int pushBridge(int x, int y, int dir, int Bridge[100][100], int map[100][100]){
    if(Bridge[x][y]) return 0;
    Bridge[x][y] = 1;
    if(L == 1) return 1;
    int mmove[4][2] = { {-1, 0}, {0, 1}, {1,0}, {0, -1}};
    int curx = x;
    int res = 0;
    int cury = y;
    int cnt = 0;
    if(dir == 0 || dir == 3){
        while(curx + mmove[dir][0] >= 0 && cury + mmove[dir][1] >= 0){
            if(map[x][y] == map[curx + mmove[dir][0]][cury + mmove[dir][1]] && !Bridge[curx + mmove[dir][0]][cury + mmove[dir][1]]){
                Bridge[curx + mmove[dir][0]][cury + mmove[dir][1]] = 1;
                res = 1;
            }
            curx += mmove[dir][0];
            cury += mmove[dir][1];
            cnt++;
        }
    }else{
        while(curx + mmove[dir][0] < N && cury + mmove[dir][1] < N){
            if(map[x][y] == map[curx + mmove[dir][0]][cury + mmove[dir][1]] && !Bridge[curx + mmove[dir][0]][cury + mmove[dir][1]]){
                Bridge[curx + mmove[dir][0]][cury + mmove[dir][1]] = 1;
                res = 1;
            }
            curx += mmove[dir][0];
            cury += mmove[dir][1];
            cnt++;
        }
    }
    if(cnt < L - 1) return 0;
    return res;
}

int main(void){
        cin >> N >> L;
        int map[100][100] = {0};
        for(int i = 0; i<N; i++){
            for(int j = 0; j < N; j++){
                cin >> map[i][j];
            }
        }

    int bridge[100][100] = {0};
    int cnt = 0;
    int check = 1;
    
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(j + 1 < N){
                if(map[i][j] == map[i][j+1]) continue;
                if(map[i][j] + 1 ==  map[i][j+1] && !bridge[i][j]){
                    if(pushBridge(i, j, 3, bridge, map)){
                        check = 1;
                        continue;
                    }else{
                        check = 0;
                        break;
                    }
                }else if(map[i][j] - 1 == map[i][j+1] && !bridge[i][j + 1]){
                    if(pushBridge(i, j + 1, 1, bridge, map)){
                        check = 1;
                        continue;
                    }else{
                        check = 0;
                        break;
                    }
                }else{
                    check = 0;
                    break;
                }
            }
        }
        RemoveBridge(0, i, bridge);
        if(check) cnt++;
        check = 1;
    }
    
    check = 1;
    
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(j + 1 < N){
                if(map[j][i] == map[j + 1][i]) continue;
                if(map[j][i] + 1 ==  map[j + 1][i] && !bridge[j][i]){
                    if(pushBridge(j, i, 0, bridge, map)){
                        check = 1;
                        continue;
                    }else{
                        check = 0;
                        break;
                    }
                }else if(map[j][i] - 1 == map[j + 1][i] && !bridge[j + 1][i]){
                    if(pushBridge(j + 1, i, 2, bridge, map)){
                        check = 1;
                        continue;
                    }else{
                        check = 0;
                        break;
                    }
                }else{
                    check = 0;
                    break;
                }
            }
        }
        RemoveBridge(0, i, bridge);
        if(check) cnt++;
        check= 1;
    }
    
    cout << cnt << endl;
    return 0;
}



//Answer - solved by citizen

//#include <iostream>
//int main() {
//	int n, l, ans = 0, i, j, c;
//	short a[200][100];
//	cin >> n >> l;
//	for (i=0; i<n; i++)
//		for (j=0; j<n; j++)
//			cin >> a[i][j];
//	for (i=0; i<n; i++)
//		for (j=0; j<n; j++)
//			a[i + n][j] = a[j][i];
//	for (i=0; i<n * 2; i++) {
//		c = 1;
//		for (j=0; j<n - 1; j++) {
//			if (a[i][j] == a[i][j + 1]) c++;
//			else if (a[i][j] + 1 == a[i][j + 1] && c >= l) c = 1;
//			else if (a[i][j] - 1 == a[i][j + 1] && c >= 0) c = -l + 1;
//			else break;
//		}
//		if (j == n - 1 && c >= 0) ans++;
//	}
//	printf("%d", ans);
//	return 0;
//}

