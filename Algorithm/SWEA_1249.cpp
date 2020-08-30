/* [SWEA] 1249
 * Completed!
 * 
 * Memory : 13404 KB
 * Time   : 29 ms
 */
#include <stdio.h>
using namespace std;

#define MAX_SIZE 101
#define MAX_QUEUE_SIZE 100000

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
int opt[MAX_SIZE][MAX_SIZE] = { 0 };

const int dx[4] = { -1, 0, 1,  0 };
const int dy[4] = { 0, 1, 0, -1 };

int n;

int main(void) {
    int T;
    scanf("%d\n", &T);
    for (int tc = 1; tc <= T; tc++)
    {
        queue_init();

        for (int i = 0; i < MAX_SIZE; i++)
            for (int j = 0; j < MAX_SIZE; j++)
                opt[i][j] = 1e9;

        opt[0][0] = 0;
        scanf("%d", &n);

        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                scanf("%1d", &map[i][j]);

        _pair temp;
        temp.x = 0;
        temp.y = 0;
        queue_push(temp);

        while (queue_size)
        {
            temp = queue_pop();
            int curx = temp.x;
            int cury = temp.y;

            for (int i = 0; i < 4; i++)
            {
                int movx = curx + dx[i];
                int movy = cury + dy[i];
                if (movx < 0 || movx >= n || movy < 0 || movy >= n)
                    continue;
                if (opt[movx][movy] > opt[curx][cury] + map[movx][movy])
                {
                    opt[movx][movy] = opt[curx][cury] + map[movx][movy];
                    temp.x = movx;
                    temp.y = movy;
                    queue_push(temp);
                }
            }
        }
        printf("#%d %d\n", tc, opt[n - 1][n - 1]);
    }
    return 0;
}