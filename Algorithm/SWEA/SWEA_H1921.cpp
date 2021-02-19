/* Completed!
 *  119 ms
 */

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

#define MAXF 20
#define MAXN 1001
#define MAXM 10
#define MAXA 40000
#define MAXH 80003
#define NULL 0
#define salloc() &nodes[sidx]

struct Node {
	int pid, area;
	long long int cost;
	bool reserved;
	Node* next;
}nodes[MAXA], htable[MAXH];

struct User {
	int friend_cnt;
	int friends[MAXF];
	int total[MAXM + 1];
	int count[MAXM + 1];
}u[MAXN];

int M, sidx;

struct Heap
{
	int size = 0, h[MAXA];
	void init() {
		size = 0;
	}
	void push(int idx) {
		if (size == MAXA)
			return;
		long long val = nodes[idx].cost;
		int cur = ++size;
		while (cur != 1 && nodes[h[cur >> 1]].cost > val) {
			h[cur] = h[cur >> 1];
			cur >>= 1;
		}
		h[cur] = idx;
	}
	void pop() {
		if (!size)
			return;
		int e = h[size--];
		int cur = 1, ch = 2;
		while (ch <= size) {
			if (ch < size && nodes[h[ch]].cost > nodes[h[ch + 1]].cost) ch++;
			if (nodes[h[ch]].cost >= nodes[e].cost) break;
			h[cur] = h[ch];
			cur = ch; ch <<= 1;
		}
		h[cur] = e;
	}
	int top() { return h[1]; }
}heap[MAXM + 1];

void init(int N, int _M) {
	M = _M; sidx = 0;
	for (int i = 1; i <= N; i++) {
		u[i].friend_cnt = 0;
		for (int j = 1; j <= M; j++) u[i].total[j] = u[i].count[j] = 0;
	}
	for (int i = 0; i < MAXH; i++) {
		if (i <= M) heap[i].init();
		htable[i].next = NULL;
	}
}
void befriend(int uid1, int uid2) {
	u[uid1].friends[u[uid1].friend_cnt++] = uid2;
	u[uid2].friends[u[uid2].friend_cnt++] = uid1;
	for (register int i = 1; i <= M; i++) {
		u[uid1].total[i] += u[uid2].count[i];
		u[uid2].total[i] += u[uid1].count[i];
	}
}
void add(int pid, int area, int price) {
	Node* newNode = salloc();
	newNode->area = area; newNode->pid = pid;
	newNode->reserved = false;
	newNode->cost = ((long long)price << 30) | pid;
	newNode->next = htable[pid % MAXH].next;
	htable[pid % MAXH].next = newNode;
	heap[area].push(sidx++);
}
void reserve(int uid, int pid) {
	Node* walker = 0;
	for (register Node* node = &htable[pid % MAXH]; node->next; node = node->next) {
		if (node->next->pid != pid) continue;
		walker = node->next;
		node->next = node->next->next;
		break;
	}
	walker->reserved = true;
	u[uid].count[walker->area]++;
	u[uid].total[walker->area]++;
	for (int i = 0; i < u[uid].friend_cnt; i++) {
		u[u[uid].friends[i]].total[walker->area]++;
	}
}
int recommend(int uid) {
	int _max = 0;
	Node node = { 0,0,(long long)1 << 40 };
	for (int i = 1; i <= M; i++) {
		while (heap[i].size > 0 && nodes[heap[i].top()].reserved) heap[i].pop();
		if (!heap[i].size) continue;
		if (_max < u[uid].total[i]) {
			_max = u[uid].total[i];
			node = nodes[heap[i].top()];
		}
		else if (_max == u[uid].total[i] && nodes[heap[i].top()].cost < node.cost)
			node = nodes[heap[i].top()];
	}
	return node.pid;
}

#define INIT			100
#define BEFRIEND		200
#define ADD				300
#define RESERVE			400
#define RECOMMEND		500

static bool run()
{
	int L, N, M;
	bool okay = false;

	int pid, uid;
	int uid1, uid2;
	int area, price;

	int ans;
	int cmd, ret;

	scanf("%d", &L);

	for (int l = 0; l < L; ++l)
	{
		scanf("%d", &cmd);
		switch (cmd)
		{
		case INIT:
			scanf("%d %d", &N, &M);
			init(N, M);
			okay = true;
			break;
		case BEFRIEND:
			scanf("%d %d", &uid1, &uid2);
			befriend(uid1, uid2);
			break;
		case ADD:
			scanf("%d %d %d", &pid, &area, &price);
			add(pid, area, price);
			break;
		case RESERVE:
			scanf("%d %d", &uid, &pid);
			reserve(uid, pid);
			break;
		case RECOMMEND:
			scanf("%d %d", &uid, &ans);
			ret = recommend(uid);
			if (ret != ans)
				okay = false;
			break;
		}
	}

	return okay;
}

int main() {
	int TC, MARK;

	freopen("input.txt", "r", stdin);

	setbuf(stdout, NULL);
	scanf("%d %d", &TC, &MARK);

	for (int testcase = 1; testcase <= TC; ++testcase) {
		int score = run() ? MARK : 0;
		printf("#%d %d\n", testcase, score);
	}

	return 0;
}