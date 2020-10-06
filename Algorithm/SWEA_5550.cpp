/* [SWEA] 5550
 * Completed!
 * 
 * Memory : 296 KB
 * Time   : 3 ms
 */
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

#define MAXN 2501

char str[MAXN];
int T;

int main(int argc, char** argv)
{
	scanf("%d", &T);
	int ans, i, list[5];
	for (int tc = 1; tc <= T; ++tc)
	{
		ans = 0;
		scanf("%s", &str);
		for (i = 0; i < 5; ++i) {
			list[i] = 0;
		}
		for (i = 0; str[i]; ++i) {
			if (ans < list[0] - list[4]) {
				ans = list[0] - list[4];
			}
			switch (str[i]) {
			case 'c':
				++list[0];
				break;
			case 'r':
				++list[1];
				if (list[0] < list[1]) {
					ans = -1;
					str[i + 1] = 0;
				}
				break;
			case 'o':
				++list[2];
				if (list[1] < list[2]) {
					ans = -1;
					str[i + 1] = 0;
				}
				break;
			case 'a':
				++list[3];
				if (list[2] < list[3]) {
					ans = -1;
					str[i + 1] = 0;
				}
				break;
			case 'k':
				++list[4];
				if (list[3] < list[4]) {
					ans = -1;
					str[i + 1] = 0;
				}
				break;
			}
		}
		for (i = 0; i < 4; ++i) {
			if (list[i] != list[i + 1]) {
				ans = -1;
				break;
			}
		}
		printf("#%d %d\n", tc, ans);
	}
	return 0;
}

/* 2nd Solution
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#define MAXF 10000
struct Queue {
	int size, front, end;
	int queue[MAXF];
	void init() {
		size = front = end = 0;
	}
	void push(int val) {
		size++;
		queue[end++] = val;
	}
	int pop() {
		size--;
		return queue[front++];
	}
}q;

int T, res;
char frog[MAXF] = { 0 };
int slen;
char croak[6] = "croak";

void start(int len, int cnt, int step) {
	if (cnt < 5) {
		if (!cnt) {
			if (res > step)
				res = step;
		}
		return;
	}
	int croak_idx = 0, idx = 0;
	bool isAnswer = false, process = false;
	q.init();
	while (idx <= len) {
		if (croak[croak_idx] == frog[idx]) {
			process = true;
			q.push(idx);
			croak_idx++;
			cnt--;
		}
		if (q.size == 5) {
			while (q.size) {
				frog[q.pop()] = '_';
			}
			isAnswer = true;
			croak_idx = 0;
		}
		idx++;
	}

	if (!process) {
		return;
	}
	step = isAnswer ? step + 1 : step;
	start(len, cnt, step);
}

int main(void) {
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		q.init();
		res = 1e9;
		slen = 0;
		scanf("%s", frog);
		for (int i = 0; frog[i] != '\0'; i++) slen++;
		if (!(slen % 5))
			start(slen, slen, 0);

		printf("#%d %d\n", tc, res != 1e9 ? res : -1);
	}
	return 0;
}

*/