/* [BOJ] 16235
 * Complete!
 *
 */

#include <iostream>
#include <queue>
using namespace std;

int N, M, K;
priority_queue<int, vector<int>, greater<int> > tree[10][10];
queue<int> dtree[10][10];
int a[10][10] = {0};
int add[10][10] = {0};

void copymap(){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            add[i][j] = a[i][j];
        }
    }
}

void spring(){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(tree[i][j].size()){
                priority_queue<int, vector<int>, greater<int> > temp;
                while(!tree[i][j].empty()){
                    int age = tree[i][j].top();
                    tree[i][j].pop();
                    if(a[i][j] - age >= 0){
                        a[i][j] -= age;
                        age += 1;
                        temp.push(age);
                    }else{
                        tree[i][j].push(age);
                        break;
                    }
                }
                while(!tree[i][j].empty()){
                    dtree[i][j].push(tree[i][j].top());
                    tree[i][j].pop();
                }
                tree[i][j] = temp;
            }
        }
    }
}

void summer(){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(dtree[i][j].size()){
                int total = 0;
                while(!dtree[i][j].empty()){
                    int age = dtree[i][j].front();
                    dtree[i][j].pop();
                    total += (age/2);
                }
                a[i][j] += total;
            }
        }
    }
}

void fall(){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            
            if(tree[i][j].size()){
                priority_queue<int, vector<int>, greater<int> > temp;
                while(!tree[i][j].empty()){
                    int age = tree[i][j].top();
                    tree[i][j].pop();
                    temp.push(age);
                    if(age % 5 == 0){
                        if(i - 1 >= 0 && j - 1 >= 0){
                            tree[i - 1][j - 1].push(1);
                        }
                        if(i - 1 >= 0){
                            tree[i-1][j].push(1);
                        }
                        if(i - 1 >= 0 && j + 1 < N){
                            tree[i - 1][j + 1].push(1);
                        }
                        if(j - 1 >= 0){
                            tree[i][j - 1].push(1);
                        }
                        if(j + 1 < N){
                            tree[i][j + 1].push(1);
                        }
                        if(i + 1 < N && j - 1 >= 0){
                            tree[i + 1][j - 1].push(1);
                        }
                        if(i + 1 < N){
                            tree[i + 1][j].push(1);
                        }
                        if(i + 1 < N && j + 1 < N){
                            tree[i + 1][j + 1].push(1);
                        }
                    }
                }
                tree[i][j] = temp;
            }
        }
    }
}

void winter(){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            a[i][j] += add[i][j];
        }
    }
}

int countTree(){
    int cnt = 0;
    for(int i = 0; i<N; i++){
        for(int j = 0;  j<N; j++){
            if(tree[i][j].size()) cnt += tree[i][j].size();
        }
    }
    return cnt;
}

void printMap(int map[10][10]){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cout << map[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int main(){
        cin >> N >> M >> K;
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                cin >> a[i][j];
            }
        }
        for(int i = 0; i < M; i++){
            int x,y,t;
            cin >> x >> y >> t;
            tree[x-1][y-1].push(t);
        }

    copymap();
    for(int i = 0; i<N; i++){
        for(int j = 0; j<N; j++){
            a[i][j] = 5;
        }
    }
    int loop = K;
    while(loop--){
        spring();
        summer();
        fall();
        winter();
    }
    cout << countTree() << endl;;
}
