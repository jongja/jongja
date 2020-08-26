/* [BOJ] 14502 
 * Complete!
 * 
 * Memory : 1188 KB
 * Time   : 40 ms
 */

#include <stdio.h>
using namespace std;

#define MAX_SIZE 8
#define MAX_QUEUE_SIZE 10000

typedef struct PAIR {
    int x;
    int y;
}_pair;

_pair queue_pool[MAX_QUEUE_SIZE] = { 0 };
int queue_size = 0;
int queue_front = 0;
int queue_idx = 0;

void queue_push(_pair data) {
    if (queue_size == MAX_QUEUE_SIZE)
        return;
    queue_size++;
    queue_pool[queue_idx++] = data;
}

_pair queue_pop() {
    queue_size--;
    return queue_pool[queue_front++];
}

void queue_init() {
    queue_size = 0;
    queue_front = 0;
    queue_idx = 0;
}

int map[MAX_SIZE][MAX_SIZE] = { 0 };
int cmap[MAX_SIZE][MAX_SIZE] = { 0 };

const int dx[4] = { -1, 0, 1,  0 };
const int dy[4] = { 0, 1, 0, -1 };
int MAX = 0;
int N, M;

int virus() {
    queue_init();
    _pair temp;
    int res = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cmap[i][j] = map[i][j];
            if (map[i][j] == 2) {
                temp.x = i;
                temp.y = j;
                queue_push(temp);
            }
        }
    }
    int movx, movy;
    while (queue_size) {
        temp = queue_pop();
        for (int i = 0; i < 4; i++) {
            movx = temp.x + dx[i];
            movy = temp.y + dy[i];
            if (movx < 0 || movx >= N || movy < 0 || movy >= M || cmap[movx][movy] != 0) continue;
            cmap[movx][movy] = 2;
            _pair tp;
            tp.x = movx;
            tp.y = movy;
            queue_push(tp);
        }
    }
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            if (cmap[i][j] == 0) res++;

    return res;
}

void start(int curx, int cury, int step) {
    if (step == 3) {
        int res = virus();
        if (MAX < res)
            MAX = res;
        return;
    }
    for (int i = curx; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (map[i][j] == 0) {
                map[i][j] = 1;
                start(i, j, step + 1);
                map[i][j] = 0;
            }
        }
    }
}

int main(void) {
    int T;
    scanf("%d %d\n", &N, &M);
    queue_init();
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            scanf("%d", &map[i][j]);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (map[i][j] == 0) {
                map[i][j] = 1;
                start(i, j, 1);
                map[i][j] = 0;
            }
        }
    }
    printf("%d\n", MAX);
    return 0;
}