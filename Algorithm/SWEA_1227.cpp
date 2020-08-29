#include <stdio.h>

#define MAX_QUEUE_SIZE 10000

bool res = false;
int map[101][101] = { 0 };
bool visit[101][101] = { false };
int dx[4] = {-1,0,1,0};
int dy[4] = {0,1,0,-1};
int sx, sy;
int ed_x, ed_y;

typedef struct PAIR{
	int x;
	int y;
}pair_t;

struct Queue{
	int size, front, end;
	pair_t queue_pool[MAX_QUEUE_SIZE];
	void init(){
		size = front = end = 0;
	}
	void push(pair_t val){
		if(size == MAX_QUEUE_SIZE)
			return;
		size++;
		queue_pool[end++] = val;
	}
	pair_t pop(){
		if(size == 0)
			return queue_pool[0];
		size--;
		return queue_pool[front++];
	}
}q;

void start(){
	q.init();
	pair_t temp;
	temp.x = sx; temp.y = sy;
	q.push(temp);
	while(q.size){
		temp = q.pop();
		
		for(int i = 0; i < 4; i++){
			int movx = temp.x + dx[i];
			int movy = temp.y + dy[i];
			if(movx < 0 || movx >= 100 || movy < 0 || movy >= 100 || visit[movx][movy] || map[movx][movy] == 1) continue;
			if(map[movx][movy] == 3){
				res = true;
				return;
			}
			visit[movx][movy] = true;
			pair_t t;
			t.x = movx; t.y = movy;
			q.push(t);
		}
	}
}

int main(void){
	freopen("input.txt", "r", stdin);
	for(int tc = 1; tc <= 10; tc++){
		res = false;		
		int a;
		scanf("%d", &a);
		for(int i = 0 ; i < 100; i++){
			for(int j = 0; j < 100; j++){
				scanf("%1d ", &map[i][j]);
				if(map[i][j] == 2){
					sx = i; sy = j;
				}
				visit[i][j] = false;
			}
		}
		start();
		printf("#%d %d\n",tc, res ? 1 : 0);
	}
}

