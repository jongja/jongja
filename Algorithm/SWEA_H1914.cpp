/* Not Completed..
 * 
 */

#ifndef _CRT_SECURE_NO_WARNINGS 
#define _CRT_SECURE_NO_WARNINGS 
#endif

#include<stdio.h>

#define MAX_N    100
#define MAX_TOOL 50
#define MAX_HEAP 4800

int N;

struct Tool {
	int step;
	int tid;
	int pt;
	int end_time;
	bool hasLot;
}t[MAX_TOOL];

struct Heap {
	int h[MAX_HEAP];
	int size;
	bool init_mode;

	void init() {
		size = 0;
		init_mode = false;
	}
	void push(int tid) {
		if (size == MAX_HEAP)
			return;
		int cur = ++size;
		if (init_mode) {
			while (cur != 1 && t[h[cur >> 1]].pt > t[tid].pt) {
				h[cur] = h[cur >> 1];
				cur >>= 1;
			}
		}
		else {
			while (cur != 1 && t[h[cur >> 1]].end_time > t[tid].end_time) {
				h[cur] = h[cur >> 1];
				cur >>= 1;
			}
		}
		h[cur] = tid;
	}

	void pop() {
		if (size == 0)
			return;
		int e = h[size--];
		int cur = 1, ch = 2;

		while (ch <= size) {
			if (init_mode) {
				if (ch < size && t[h[ch]].pt > t[h[ch + 1]].pt) ch++;
				if (t[h[ch]].pt >= t[e].pt) break;
			}
			else {
				if (ch < size && t[h[ch]].end_time > t[h[ch + 1]].end_time) ch++;
				if (t[h[ch]].end_time >= t[e].end_time) break;
			}
			h[cur] = h[ch];
			cur = ch; ch <<= 1;
		}
		h[cur] = e;
	}

	void init_push(int tid) {
		init_mode = true;
		push(tid);
		init_mode = false;
	}

	int top() {
		return h[1];
	}
};

struct Step {
	Heap pq;
	int lot;
}s[MAX_N];

int tid, curTime, resultLot;

void sim_start(int future_time) {
	int top_tid = 0;
	for(int i = 0; i < N; i++) {
		top_tid = s[i].pq.top();
		while (t[top_tid].end_time > 0 && t[top_tid].end_time <= future_time) {
			if (i == N - 1) { // if this Step is last
				s[i].pq.pop();
				resultLot++;
			}
			else {
				s[i].pq.pop();
				s[i + 1].lot++;
			}

			if (s[i].lot > 0) { // if current step has lot, add to tool.
				s[i].lot--;
				t[top_tid].end_time = future_time + t[top_tid].pt;
				s[i].pq.push(top_tid);
			}

			top_tid = s[i].pq.top();
		}
	}
}

void init(int N) {
	::N = N;
	tid = curTime = resultLot = 0;
	for (int i = 0; i < N; i++) {
		s[i].lot = 0;
		s[i].pq.init();
	}
}

void setupTool(int T, int stepNo[5000], int procTime[5000]) {
	for (int i = 0; i < T; i++) {
		t[i].hasLot = false;
		t[i].pt = procTime[i];
		t[i].end_time = 0;
		t[i].step = stepNo[i];
		t[i].tid = i;
		s[stepNo[i]].pq.init_push(i);
	}
}

void addLot(int time, int number) {
	s[0].lot += number;
	sim_start(curTime + time);
	
}

int simulate(int time, int wip[MAX_N]) {
	sim_start(curTime + time);
	return 0;
}



#define ENDCASE 0
#define ADDLOT  1
#define SIMUL   2

static int run() {
	int totalStep = 0, totalTool = 0, stepID[MAX_N * MAX_TOOL], procTime[MAX_N * MAX_TOOL];
	int event, time, number;
	int userOut, userWip[MAX_N], resultOut, resultWip[MAX_N];
	int score = 100;

	for (int j = 0; j < MAX_N; j++) {
		userWip[j] = resultWip[j] = 0;
	}

	scanf("%d %d", &totalStep, &totalTool);
	init(totalStep);

	for (register int i = 0; i < totalTool; i++) {
		scanf("%d %d", stepID + i, procTime + i);
	}
	setupTool(totalTool, stepID, procTime);

	while (1) {
		scanf("%d", &event);
		if (event == ADDLOT) {
			scanf("%d %d", &time, &number);
			addLot(time, number);
		}

		else if (event == SIMUL) {
			scanf("%d", &time);
			for (int j = 0; j < totalStep; j++) {
				userWip[j] = 0;
				scanf("%d", &resultWip[j]);
			}
			scanf("%d", &resultOut);

			userOut = simulate(time, userWip);

			for (int j = 0; j < totalStep; j++) {
				if (userWip[j] != resultWip[j]) {
					score = 0;
					break;
				}
			}
			if (userOut != resultOut) {
				score = 0;
			}
		}
		else {
			return score;
		}
	}
	return score;
}

int main() {
	setbuf(stdout, NULL);
	int TestCase;

	freopen("input.txt", "r", stdin); 
	scanf("%d", &TestCase);
	for (int t = 1; t <= TestCase; ++t)
		printf("#%d %d\n", t, run());
	return 0;
}
