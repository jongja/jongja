/* [SWEA] 1767
 * Complete!
 * 
 * Memory : 12504 KB
 * Time   : 8 ms
 */
#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <iostream>
using namespace std;

#define MAX_MAP_SIZE 16

typedef struct mexynos {
	int x;
	int y;
}mcore;

int T, N;
int map[MAX_MAP_SIZE][MAX_MAP_SIZE] = { 0 };
int dx[4] = { -1, 0, 1, 0 };
int dy[4] = { 0, 1, 0, -1 };
int res = 1e9;
int con_res = 0;
int core_cnt;
mcore mc[13] = { 0 };

bool fill_line(int x, int y, int dir) {
	int movx = x + dx[dir], movy = y + dy[dir];
	while (movx < N && movx >= 0 && movy < N && movy >= 0) { // probe
		if (map[movx][movy] > 0) return false;
		movx += dx[dir];
		movy += dy[dir];
	}
	movx = x + dx[dir], movy = y + dy[dir];
	while (movx < N && movx >= 0 && movy < N && movy >= 0) { // connect
		map[movx][movy] = 2;
		movx += dx[dir];
		movy += dy[dir];
	}
	return true;
}

void restore_line(int x, int y, int dir) {
	int movx = x + dx[dir], movy = y + dy[dir];
	while (movx < N && movx >= 0 && movy < N && movy >= 0) { // probe
		map[movx][movy] = 0;
		movx += dx[dir];
		movy += dy[dir];
	}
}

int line(int dir, int x, int y) {
	if (dir == 0) return x;
	else if (dir == 1) return N - 1 - y;
	else if (dir == 2) return N - 1 - x;
	else return y;
}

void start(int step, int connect, int sum) {
	if (step >= core_cnt) { // return condition.
		if (con_res <= connect) {
			if (con_res < connect) {
				con_res = connect;
				res = sum;
			}
			else {
				if (res > sum)
					res = sum;
			}
		}
		return;
	}

	int movx = mc[step].x, movy = mc[step].y;
	bool skip = false;
	bool result;

	for (int i = 0; i < 4; i++) { // check already connected..?
		movx = mc[step].x + dx[i];
		movy = mc[step].y + dy[i];
		if (movx < 0 || movx >= N || movy < 0 || movy >= N) {
			skip = true;
			break;
		}
	}

	movx = mc[step].x, movy = mc[step].y;
	if (!skip) {
		bool go = false;
		for (int j = 0; j < 4; j++) {
			if (fill_line(movx, movy, j)) {
				start(step + 1, connect + 1, sum + line(j, movx, movy));
				restore_line(movx, movy, j);
				go = true;
			}
		}
		if (!go) start(step + 1, connect, sum);
	}
	else {
		start(step + 1, connect + 1, sum);
	}
	return;
}

int main(void) {
	freopen("input.txt", "r", stdin);
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		core_cnt = 0;
		con_res = 0;
		res = 1e9;
		scanf("%d", &N);
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cin >> map[i][j];
				if (map[i][j]) {
					mc[core_cnt].x = i;
					mc[core_cnt++].y = j;
				}
			}
		}
		start(0, 0, 0);
		printf("#%d %d\n", tc, res);
	}
}