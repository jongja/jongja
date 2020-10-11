/* [SWEA] 1868
 * Completed!
 * 
 * Memory : 13908 KB
 * Time   : 68 ms
 */
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

#define MAXN 301
#define MAX_QUEUE_SIZE 90003

int map[MAXN][MAXN] = { 0 };
int nmap[MAXN][MAXN] = { 0 };

int dx[8] = { -1, -1, 0, 1, 1, 1, 0, -1 };
int dy[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };
int N;

typedef struct PAIR {
	int x;
	int y;
}pair_t;

struct Queue {
	int size, front, end;
	pair_t queue_pool[MAX_QUEUE_SIZE];
	void init() {
		size = 0; front = 0; end = 0;
	}
	void push(pair_t val) {
		if (size == MAX_QUEUE_SIZE) {
			return;
		}
		size++;
		queue_pool[end++] = val;
	}
	pair_t pop() {
		if (size == 0) {
			return queue_pool[end];
		}
		size--;
		return queue_pool[front++];
	}
}q;

int spread(int curx, int cury) {
	int res = 0;
	q.init();
	pair_t tp;
	tp.x = curx; tp.y = cury;
	q.push(tp);
	while (q.size) {
		tp = q.pop();
		if (map[tp.x][tp.y] > 0) continue;
		for (int i = 0; i < 8; i++) {
			int movx = tp.x + dx[i];
			int movy = tp.y + dy[i];
			if (movx < 0 || movx >= N || movy < 0 || movy >= N || map[movx][movy] >= 0) continue;
			res++;
			map[movx][movy] = nmap[movx][movy];
			pair_t ttp;
			ttp.x = movx; ttp.y = movy;
			q.push(ttp);
		}
	}
	return res;
}

int main() {
	int T;
	char ip;
	scanf("%d", &T);

	for (int tc = 1; tc <= T; tc++) {
		scanf("%d", &N);
		for (register int i = 0; i < N; i++) {
			for (register int j = 0; j < N; j++) {
				scanf("%c", &ip);
				if (ip == '\n') {
					j--;
					continue;
				}
				if (ip == '*') {
					map[i][j] = 9;
				}
				else {
					map[i][j] = -1;
				}
			}
		}

		for (register int i = 0; i < N; i++) {
			for (register int j = 0; j < N; j++) {
				if (map[i][j] == 9) continue;
				else {
					int pang = 0;
					for (register int k = 0; k < 8; k++) {
						int movx = i + dx[k];
						int movy = j + dy[k];
						if (movx < 0 || movx >= N || movy < 0 || movy >= N) continue;
						if (map[movx][movy] == 9) pang++;
					}
					nmap[i][j] = pang;
				}
			}
		}
		int answer = 0;
		for (register int i = 0; i < N; i++) {
			for (register int j = 0; j < N; j++) {
				if (nmap[i][j] == 0 && map[i][j] == -1) {
					map[i][j] = 0;
					spread(i, j);
					answer++;
				}
			}
		}

		for (register int i = 0; i < N; i++)
			for (register int j = 0; j < N; j++)
				if (map[i][j] == -1) answer++;

		printf("#%d %d\n", tc, answer);
	}
	return 0;
}