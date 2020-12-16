/* [SWEA] 1258
 * Completed!
 *
 * Memory : 416 KB
 * Time   : 4 ms
 */
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

#define MAXN 100
#define MAX_QUEUE_SIZE 10001

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
			printf("Full..\n");
			return;
		}
		size++;
		queue_pool[end++] = val;
	}
	pair_t pop() {
		if (size == 0) {
			printf("Empty..\n");
			return queue_pool[end];
		}
		size--;
		return queue_pool[front++];
	}
}q;

struct Matrix {
	int size, r, c, score;
}matrix[MAXN];

int map[MAXN][MAXN] = { 0 };
int matrix_cnt = 0;
int dx[4] = { -1,0,1,0 };
int dy[4] = { 0,1,0,-1 };
int N;


void qsort(int l, int r, struct Matrix* a) {
	if (l < r) {
		int i = l;
		int j = r + 1;
		do {
			do i++; while (i <= r && a[i].score < a[l].score);
			do j--; while (j >= l && a[j].score > a[l].score);
			if (i < j) {
				Matrix t = a[i]; a[i] = a[j]; a[j] = t;
			}
		} while (i < j);
		Matrix t = a[j];
		a[j] = a[l]; a[l] = t;
		qsort(l, j - 1, a);
		qsort(j + 1, r, a);
	}
}

void countMatrix(int curx, int cury, int mat_idx) {
	q.init();
	pair_t tp;
	tp.x = curx; tp.y = cury;
	q.push(tp);
	int row = 0, col = 0;
	int movx = curx, movy = cury;
	while (map[movx][movy]) {
		col++;
		movy += dy[1];
	}
	movy = cury;
	while (map[movx][movy]) {
		row++;
		movx += dx[2];
	}
	map[curx][cury] = mat_idx;
	while (q.size) {
		tp = q.pop();
		for (int i = 0; i < 4; i++) {
			movx = tp.x + dx[i];
			movy = tp.y + dy[i];
			if (movx < 0 || movx >= N || movy < 0 || movy >= N || map[movx][movy] <= 0)continue;
			map[movx][movy] = mat_idx;
			pair_t ip;
			ip.x = movx;
			ip.y = movy;
			q.push(ip);
		}
	}
	matrix[matrix_cnt].size = row * col;
	matrix[matrix_cnt].c = col;
	matrix[matrix_cnt].r = row;
	matrix[matrix_cnt++].score = ((row * col) << 10) + row;
}

int main() {
	int T;
	scanf("%d", &T);

	for (int tc = 1; tc <= T; tc++) {
		matrix_cnt = 0;
		scanf("%d", &N);
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				scanf("%d", &map[i][j]);

		int mat_idx = -1;

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (map[i][j] > 0) {
					countMatrix(i, j, mat_idx);
					mat_idx -= 1;
				}
			}
		}
		qsort(0, matrix_cnt - 1, matrix);
		printf("#%d %d ", tc, matrix_cnt);
		for (int i = 0; i < matrix_cnt; i++) {
			if (i < matrix_cnt - 1)
				printf("%d %d ", matrix[i].r, matrix[i].c);
			else
				printf("%d %d\n", matrix[i].r, matrix[i].c);
		}
	}
	return 0;
}