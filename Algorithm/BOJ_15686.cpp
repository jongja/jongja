/* [BOJ] 15686
 * Complete!
 *
 */

#include <iostream>
#include <queue>
using namespace std;


int N, M;
int minDistance = 10000;

//int map[51][51] = {
//    {0, 2, 0, 1, 0},
//    {1, 0, 1, 0, 0},
//    {0, 0, 0, 0, 0},
//    {2, 0, 0, 1, 1},
//    {2, 2, 0, 1, 2}
//};

queue<pair<int,int> > q1;
queue<pair<int,int> > q2;

int map[51][51] = {0};

int distance(int r1, int c1, int r2, int c2){
    int dis1 = r1 - r2 > 0 ? r1 - r2 : r2 - r1;
    int dis2 = c1 - c2 > 0 ? c1 - c2 : c2 - c1;
    return dis1 + dis2;
}

queue<pair<int,int> > scanHouses(){
    queue<pair<int,int> > chicken;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(map[i][j] == 1){
                q1.push(make_pair(i,j));
            }
            if(map[i][j] == 2){
                chicken.push(make_pair(i,j));
            }
        }
    }
    return chicken;
}

void fillQueue(){
    while(!q2.empty()){
        q1.push(q2.front());
        q2.pop();
    }
}

void ChooseChicken(int step, queue<pair<int,int> > cq, queue<pair<int,int> > chicken){
    if(step == M){
        int total = 0;
        queue<pair<int,int> > temp = cq;
        
        while(!q1.empty()){
            int tempMin = 10000;
            while(!cq.empty()){
                int dis = distance(q1.front().first, q1.front().second, cq.front().first, cq.front().second);
                if(tempMin > dis)
                    tempMin = dis;
                cq.pop();
            }
            q2.push(q1.front());
            q1.pop();
            total += tempMin;
            cq = temp;
        }
        fillQueue();
        if(minDistance > total && total)
            minDistance = total;
        return;
    }
    
    while(!chicken.empty())
    {
        queue<pair<int,int> > temp = cq;
        cq.push(chicken.front());
        chicken.pop();
        ChooseChicken(step + 1, cq, chicken);
        cq = temp;
    }
    return;
}

int main(){
        cin >> N >> M;
        for(int i= 0; i < N; i++)
            for(int j=0; j < N; j++)
                cin >> map[i][j];
    queue<pair<int,int> > cq;
    queue<pair<int,int> > chicken = scanHouses();;
    ChooseChicken(0, cq, chicken);
    cout << minDistance << endl;
    return 0;
}