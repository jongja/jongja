/* [BOJ] 17142
 * Not Completed..
 *
 */
 
#include <iostream>
#include <queue>
using namespace std;

typedef struct vi {
	int x;
	int y;
	bool gen;
}VIRUS;

int N, M;
int map[50][50] = { 0 };
int dx[4] = { -1,0,1,0 };
int dy[4] = { 0, 1, 0, -1 };
int Min = 2500;
VIRUS virus[10];
int vnum = 0;
int cmap[50][50] = { 0 };

bool isAnswer() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (!cmap[i][j]) return false;
		}
	}
	return true;
}

void startVirus() {
	queue<pair<int, int> > q;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cmap[i][j] = map[i][j];
		}
	}
	for (int i = 0; i < vnum; i++) {
		if (virus[i].gen) {
			q.push(make_pair(virus[i].x, virus[i].y));
			cmap[virus[i].x][virus[i].y] = -1;
		}
	}
	int curx, cury, movx, movy, curtime;
	
	while (!q.empty()) {
		curx = q.front().first;
		cury = q.front().second;
		q.pop();
		if(cmap[curx][cury] < 0) curtime = -1 * cmap[curx][cury] + 1;
		
		for(int i =0 ; i < 4; i++){
			movx = curx + dx[i];
			movy = cury + dy[i];
			if(movx < 0 || movx >= N || movy < 0 || movy >= N || cmap[movx][movy]) continue;
			cmap[movx][movy] = cmap[curx][cury] - 1;
			q.push(make_pair(movx, movy));
		}
	}
	cout << endl;
	for(int i =0 ; i < N; i++){
		for(int j = 0; j < N; j++)
			cout << cmap[i][j] << " ";
		cout << endl;
	}
	cout << endl;
	
	if (isAnswer()) {
		if (Min > curtime)
			Min = curtime;
	}
	return;
}

void start(int step, int cur) {
	if (step == M) {
		startVirus();
		return;
	}
	for (int i = cur + 1; i < vnum; i++) {
		virus[i].gen = true;
		start(step + 1, i);
		virus[i].gen = false;
	}
}

int main(void) {
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
			if (map[i][j] == 2) {
				virus[vnum].x = i;
				virus[vnum].y = j;
				virus[vnum++].gen = false;
			}
		}
	}
	for (int i = 0; i < vnum; i++) {
		virus[i].gen = true;
		start(1, i);
		virus[i].gen = false;
	}
	if (Min == 2500) cout << -1 << endl;
	else cout << Min << endl;
}
