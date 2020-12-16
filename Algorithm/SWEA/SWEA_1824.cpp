/* [SWEA] 1824
 * Complete!
 *
 * Memory : 13076 KB
 * Time	  :  ms
 */

#include <stdio.h>

#define MAX_MAP_SIZE 21

int T, R, C;
char map[MAX_MAP_SIZE][MAX_MAP_SIZE] = { 0 };
int dx[4] = { -1,0,1,0 };
int dy[4] = { 0,1,0,-1 };
int dir = 1, mem = 0;
bool end_prg = false;
bool already[MAX_MAP_SIZE][MAX_MAP_SIZE][4][16];

void do_command(char c) {
	switch (c)
	{
	case '>':
		dir = 1;
		break;
	case '<':
		dir = 3;
		break;
	case '^':
		dir = 0;
		break;
	case 'v':
		dir = 2;
		break;
	case '-':
		mem -= 1;
		if (mem == -1) mem = 15;
		break;
	case '+':
		mem += 1;
		if (mem == 16) mem = 0;
		break;
	case '_':
		if (!mem) dir = 1;
		else dir = 3;
		break;
	case '|':
		if (!mem) dir = 2;
		else dir = 0;
		break;
	case '@':
		end_prg = true;
		break;
	case '.':
		break;
	default:
		mem = c - '0';
		break;
	}
	return;
}

int move_cur(int cur, int rc) { // rc == 0, row
	int mov = cur;
	if (!rc) {
		mov += dx[dir];
		if (mov >= 0 && mov < R) return mov;
		else if (mov >= R) return 0;
		else return R - 1;
	}
	else {
		mov += dy[dir];
		if (mov >= 0 && mov < C) return mov;
		else if (mov >= C) return 0;
		else return C - 1;
	}
}

void start(int curx, int cury, int step) {
	if (end_prg || already[curx][cury][dir][mem]) return;
	int movx, movy;
	already[curx][cury][dir][mem] = true;
	if (map[curx][cury] == '?') {
		for (int i = 0; i < 4; i++) {
			dir = i;
			movx = move_cur(curx, 0);
			movy = move_cur(cury, 1);
			start(movx, movy, step + 1);
			if (end_prg) return;
			dir = i;
		}
		return;
	}

	do_command(map[curx][cury]);
	movx = move_cur(curx, 0);
	movy = move_cur(cury, 1);
	start(movx, movy, step + 1);
}

void init() {
	dir = 1;
	end_prg = false;
	mem = 0;
	for (int i = 0; i < MAX_MAP_SIZE; i++)
		for (int j = 0; j < MAX_MAP_SIZE; j++)
			for (int k = 0; k < 4; k++)
				for (int u = 0; u < 16; u++)
					already[i][j][k][u] = false;
}

int main(void) {
	char res[2][5] = { "YES", "NO" };
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		init();
		scanf("%d %d ", &R, &C);
		for (int i = 0; i < R; i++)
			for (int j = 0; j < C; j++)
				scanf("%c ", &map[i][j]);

		start(0, 0, 0);

		printf("#%d %s\n", tc, end_prg ? "YES" : "NO");
	}
}