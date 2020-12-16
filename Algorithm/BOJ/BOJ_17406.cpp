/* [BOJ] 17406
 * Complete!
 *
 * Memory : 2000 KB
 * Time   : 24 ms
 */

#include <iostream>
#include <queue>
using namespace std;

typedef struct magic {
	int x;
	int y;
	int size;
}MAGIC;

int N, M, K;
MAGIC magic[6];
int map[50][50];
int Min = 100000000;

int mini() {
	int res = 0;
	int total = 0;
	for (int i = 0; i < M; i++) {
		total += map[0][i];
	}
	res = total;
	for (int i = 1; i < N; i++) {
		total = 0;
		for (int j = 0; j < M; j++) {
			total += map[i][j];
		}
		if (res > total)
			res = total;
	}
	return res;
}

void copymap(int d[50][50], int s[50][50]) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			d[i][j] = s[i][j];
		}
	}
}

void strange(int num) {
	queue<int> q;
	int step = magic[num].size;
	while (step) {
		int cnt = step;
		int curx = magic[num].x - cnt - 1;
		int cury = magic[num].y - cnt - 1;
		cnt = cnt * 2 + 1;
		for (int i = 0; i < cnt; i++) {
			q.push(map[curx][cury + i]);
		}
		for (int i = 1; i < cnt; i++) {
			q.push(map[curx + i][cury + cnt - 1]);
		}
		for (int i = 1; i < cnt; i++) {
			q.push(map[curx + cnt - 1][cury + cnt - 1 - i]);
		}
		for (int i = 1; i < cnt - 1; i++) {
			q.push(map[curx + cnt - 1 - i][cury]);
		}

		for (int i = 1; i < cnt; i++) {
			map[curx][cury + i] = q.front();
			q.pop();
		}
		for (int i = 1; i < cnt; i++) {
			map[curx + i][cury + cnt - 1] = q.front();
			q.pop();
		}
		for (int i = 1; i < cnt; i++) {
			map[curx + cnt - 1][cury + cnt - 1 - i] = q.front();
			q.pop();
		}
		for (int i = 1; i < cnt; i++) {
			map[curx + cnt - 1 - i][cury] = q.front();
			q.pop();
		}
		step--;
	}
}

void start(int command[6], bool usage[6], int step) {
	if (step == K) {
		int original[50][50] = { 0 };
		copymap(original, map);
		for (int i = 0; i < K; i++) {
			strange(command[i]);
		}
		int result = mini();
		if (Min > result)
			Min = result;
		copymap(map, original);
		return;
	}
	for (int i = 0; i < K; i++) {
		if (!usage[i]) {
			command[step] = i;
			usage[i] = true;
			start(command, usage, step + 1);
			usage[i] = false;
		}
	}
}

int main(void) {
	//freopen("input.txt", "r", stdin);
	cin >> N >> M >> K;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
		}
	}
	for (int i = 0; i < K; i++) {
		cin >> magic[i].x >> magic[i].y >> magic[i].size;
	}
	int command[6] = { -1 };
	bool usage[6] = { false };
	for (int i = 0; i < K; i++) {
		command[0] = i;
		usage[i] = true;
		start(command, usage, 1);
		usage[i] = false;
	}
	cout << Min << endl;
}
