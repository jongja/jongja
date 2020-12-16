#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

#define MAXN 1000   
#define MAXM 10     
#define MAXF 20
#define MAXA 40000
#define HASH 80003
typedef long long ll;

struct Node {
    int pid, area;
    ll score;  
    bool reserved;
    Node* next;
} nodes[MAXA], table[HASH];
int nid;
#define node() &nodes[nid]

struct User {
    int num_friends;
    int friends[MAXF];  
    int count[MAXM + 1];
    int total[MAXM + 1]; 
} user[MAXN + 1];

#define swap(a,b) {register int t;t=a;a=b;b=t;}
struct Heap { 
    int size;
    int nid[MAXA];
    void push(int id) {
        register int cur = ++size;
        nid[size] = id;
        while (cur > 1 && nodes[nid[cur]].score < nodes[nid[cur / 2]].score) {
            swap(nid[cur], nid[cur / 2]);
            cur >>= 1;
        }
    }
    void pop() {
        register int cur = 1, next;
        nid[1] = nid[size];
        while (cur * 2 < size) {
            if (cur * 2 + 1 == size) next = cur * 2;
            else next = (nodes[nid[cur * 2]].score < nodes[nid[cur * 2 + 1]].score) ? cur * 2 : cur * 2 + 1;
            if (nodes[nid[cur]].score < nodes[nid[next]].score) break;
            swap(nid[cur], nid[next]);
            cur = next;
        }
        size--;
    }
    int top() { return nid[1]; }
} heap[MAXM + 1]; 

int M;
void init(int N, int _M)
{
    nid = 0; M = _M;
    for (register int i = 1; i <= N; i++) {
        user[i].num_friends = 0;
        for (register int j = 1; j <= M; j++) user[i].count[j] = user[i].total[j] = 0;
    }
    for (register int i = 1; i <= M; i++) heap[i].size = 0;
    for (register int i = 0; i < HASH; i++) table[i].next = 0;
}

void befriend(int uid1, int uid2)
{
    user[uid1].friends[user[uid1].num_friends++] = uid2;
    user[uid2].friends[user[uid2].num_friends++] = uid1;
    for (register int i = 1; i <= M; i++) {
        user[uid1].total[i] += user[uid2].count[i];
        user[uid2].total[i] += user[uid1].count[i];
    }
}

void add(int pid, int area, int price)
{
    register Node* node = node();
    node->pid = pid; node->reserved = false; node->area = area;
    node->score = (ll)price << 30 | pid;
    node->next = table[pid % HASH].next;
    table[pid % HASH].next = node; 
    heap[area].push(nid++);
}

void reserve(int uid, int pid)
{
    register Node* target = 0;
    for (register Node* node = &table[pid % HASH]; node->next; node = node->next) {
        if (node->next->pid != pid) continue;
        target = node->next;
        node->next = node->next->next;
        break;
    }
    target->reserved = true;
    user[uid].count[target->area]++;
    user[uid].total[target->area]++;
    for (register int i = 0; i < user[uid].num_friends; i++)
        user[user[uid].friends[i]].total[target->area]++;
}

int recommend(int uid)
{
    register int max = 0;
    register Node node = { 0,0,(ll)1 << 40 };
    for (register int i = 1; i <= M; i++) {
        while (heap[i].size > 0 && nodes[heap[i].top()].reserved) heap[i].pop();
        if (heap[i].size == 0) continue;
        if (max < user[uid].total[i]) {
            node = nodes[heap[i].top()];
            max = user[uid].total[i];
        }
        else if (max == user[uid].total[i] && nodes[heap[i].top()].score < node.score)
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