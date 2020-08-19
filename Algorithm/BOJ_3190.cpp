/* [BOJ] 3190
 * Complete!
 *
 */

#include <iostream>
#include <queue>
using namespace std;

int N = 0;
int K = 0;
int L = 0;

void printMap(int map[100][100]) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << map[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

int changeDir(int cur_dir, int turn) {
	if (turn > 0) {
		if (cur_dir + 1 == 4) {
			return 0;
		}
		else {
			return cur_dir + 1;
		}
	}
	else {
		if (cur_dir - 1 == -1) {
			return 3;
		}
		else {
			return cur_dir - 1;
		}
	}
}

queue<pair<int,int> > gogogo(int dir, int map[100][100], queue<pair<int, int> > snake) { // only move, except enlarge length.
	int dd[4][2] = { {-1,0}, {0,1}, {1,0}, {0,-1}};
	queue<pair<int, int> > news;
	queue<pair<int, int> > middles;
	int tailx, taily;
	int flag = 0;
	int headx = snake.front().first;
	int heady = snake.front().second;
	snake.pop();

	while (snake.size() > 1) {
		flag = 1;
		middles.push(make_pair(snake.front().first, snake.front().second));
		snake.pop();
	}

	if (snake.size() == 1 && flag) {
		tailx = snake.front().first;
		taily = snake.front().second;
		snake.pop();
	}

	if (headx == tailx && heady == taily) { //length of snake is 1.
		map[headx][heady] = 0;
		map[headx + dd[dir][0]][heady + dd[dir][1]] = 2;	
		news.push(make_pair(headx + dd[dir][0], heady + dd[dir][1]));
	}
	else {
		map[tailx][taily] = 0;
		map[headx + dd[dir][0]][heady + dd[dir][1]] = 2;
		news.push(make_pair(headx + dd[dir][0], heady + dd[dir][1])); //input head
		while (!middles.empty()) {
			news.push(make_pair(middles.front().first, middles.front().second));
		}
	}
	return news;
}


int start(queue<pair<int, int> > q, int map[100][100]) {
	int dd[4][2] = { {-1,0}, {0,1}, {1,0}, {0,-1} };
	int cur_dir = 1;
	int a_sec = q.front().first;
	int dir = q.front().second;
	q.pop();
	queue<pair<int, int> > snake;
	snake.push(make_pair(0, 0));
	snake.push(make_pair(0, 0));

	while (!q.empty()) {
		if (!a_sec) {
			cur_dir = changeDir(cur_dir, dir);
			a_sec = q.front().first;
			dir = q.front().second;
			q.pop();
			
		}
		pair<int, int> h = snake.front();
		pair<int, int> t = snake.back();
		if (h.first + dd[cur_dir][0] >= 0 && h.second + dd[cur_dir][1] >= 0 && h.first + dd[cur_dir][0] < N && h.second + dd[cur_dir][1]) {
			int len = 0;
			if (map[h.first + dd[cur_dir][0]][h.second + dd[cur_dir][1]] == 1) {
				len = 1;
			}
			snake = gogogo(cur_dir, map, snake);
			if (len) {

				map[t.first][t.second] = 2;
			}
		}
		printMap(map);
		a_sec--;
	}

	return 0;
}

int main() {
	queue<pair<int, int>> q;
	int map[100][100];
	N = 6;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			map[i][j] = 0;
	K = 3; map[2][3] = 1; map[1][4] = 1; map[4][2] = 1;
	L = 3; q.push(make_pair(3, 1)); q.push(make_pair(15, -1)); q.push(make_pair(17, 1));
	map[0][0] = 2;
	cout << start(q, map);
	return 0;
}

