#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

#define NULL 0
#define MAXE 200000
#define MAXN 1000
#define MAXG 100
#define MAXLEN 20
#define MAXH 100003
#define PN 23
#define salloc() &node[sid];

int sid = 0;

struct Event
{
	int sid;
	int uid;
	int gid;
	bool master;
	char name[MAXLEN];
	Event* h_next;
	Event* h_prev;
	Event* u_next;
	Event* u_prev;
}node[MAXE], *htable[MAXH];

struct User {
	int cnt;
	Event* events;
}u[MAXN];


/* STRING FUNCTIONS */
void _strcpy(char dst[], const char src[]) {
	int c = 0;
	while ((dst[c] = src[c]) != 0) ++c;
}

int _strcmp(const char str1[], const char str2[]) {
	int c = 0;
	while (str1[c] != 0 && str1[c] == str2[c]) ++c;
	return str1[c] - str2[c];
}

/* STRING FUNCTIONS END */


/* HASH FUNCTIONS */
int hashing(char* s) {
	unsigned int key = 0, step = 1;
	for (int i = 0; s[i]; i++) {
		key += step * s[i];
		step *= PN;
	}
	return key % MAXH;
}

void insert_hash(Event* newNode) {
	int key = hashing(newNode->name);
	if (!htable[key]) {
		htable[key] = newNode;
		newNode->master = true;
	}
	else {
		Event* walker = htable[key];
		bool canImaster = true;
		while (walker) {
			if (_strcmp(walker->name, newNode->name)) canImaster = false;
			if (!walker->h_next) { // go to last node.
				walker->h_next = newNode;
				newNode->h_prev = walker;
				if (canImaster) newNode->master = true;
				break;
			}
			walker = walker->h_next;
		}
	}
	return;
}

Event* delete_hash(int uid, char* name) {
	int key = hashing(name);
	Event* dnode = NULL;
	Event* walker = htable[key];
	while (walker) {
		if (!_strcmp(walker->name, name) && uid == walker->uid) {
			dnode = walker;
			if (!walker->h_prev) { // if dnode is head
				htable[key] = walker->h_next;
				walker->h_next->h_prev = NULL;
			} 
			else if (!walker->h_next) { // if dnode is last node
				walker->h_prev->h_next = NULL;
			}
			else {
				walker->h_prev->h_next = walker->h_next;
				walker->h_next->h_prev = walker->h_prev;
			}
			break;
		}
		walker = walker->h_next;
	}

	dnode->h_next = dnode->h_prev = NULL;
	return dnode;
}

/* HASH FUNCTIONS END */

/* USER FUNCTIONS */

void insert_user(int uid, Event* newNode) {
	if (!u[uid].events) {
		u[uid].events = newNode;
	}
	else {
		Event* walker = u[uid].events;
		while (walker) {
			if (!walker->u_next) { // go to last node.
				walker->u_next = newNode;
				newNode->u_prev = walker;
				break;
			}
			walker = walker->u_next;
		}
	}
	return;
}

Event* delete_user(int uid, char* name) {
	Event* dnode = NULL;
	Event* walker = u[uid].events;
	while (walker) {
		if (!_strcmp(walker->name, name)) {
			dnode = walker;
			if (!walker->u_prev) { // if dnode is head
				u[uid].events = walker->u_next;
				walker->u_next->u_prev = NULL;
			}
			else if (!walker->u_next) { // if dnode is last node
				walker->u_prev->u_next = NULL;
			}
			else {
				walker->u_prev->u_next = walker->u_next;
				walker->u_next->u_prev = walker->u_prev;
			}
			break;
		}
		walker = walker->u_next;
	}

	dnode->u_next = dnode->u_prev = NULL;
	return dnode;
}

/* USER FUNCTIONS END*/

void init() {
	sid = 0;
	for (int i = 0; i < MAXH; i++) {
		if (i < MAXN) {
			u[i].cnt = 0;
			u[i].events = NULL;
		}
		htable[i]->h_next = htable[i]->h_prev = htable[i]->u_next = htable[i]->h_prev = NULL;
	}
	return;
}

int changeEvent(int uid, char ename[], char cname[]) {
	return 0;
}

int deleteEvent(int uid, char ename[]) {
	return 0;
}

void addEvent(int uid, char ename[], int groupid) {
	Event* newNode = salloc();
	newNode->sid = sid++;
	newNode->gid = groupid;
	newNode->uid = uid;
	newNode->master = false;
	newNode->h_next = newNode->h_prev = newNode->u_next = newNode->h_prev = NULL;
	_strcpy(newNode->name, ename);
	insert_hash(newNode);
	insert_user(uid, newNode);
	return;
}

int getCount(int uid) {
	return u[uid].cnt;
}

typedef enum {
	INIT,
	ADD,
	DELETE,
	CHANGE,
	GETCOUNT
} COMMAND;

extern void init();
extern void addEvent(int uid, char ename[], int groupid);
extern int deleteEvent(int uid, char ename[]);
extern int changeEvent(int uid, char ename[], char cname[]);
extern int getCount(int uid);

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

static int mSeed;
static int pseudo_rand(void)
{
	mSeed = mSeed * 431345 + 2531999;
	return mSeed & 0x7FFFFFFF;
}

static void make_string(char str[], int seed)
{
	mSeed = seed;
	int length = 5 + pseudo_rand() % 10;
	for (int i = 0; i < length; ++i) {
		str[i] = 'a' + pseudo_rand() % 26;
	}
	str[length] = 0;
}

static int run()
{
	int answer = 100;

	int cmd, p1, p2, p3, p4;
	char str1[15], str2[15];

	int N, ret, flag;
	scanf("%d %d %d", &cmd, &N, &flag);

	init();

	for (int i = 1; i < N; ++i) {
		scanf("%d", &cmd);
		switch (cmd) {
		case ADD:
			if (flag == 1) {
				scanf("%d %s %d", &p1, str1, &p3);
			}
			else {
				scanf("%d %d %d", &p1, &p2, &p3);
				make_string(str1, p2);
			}
			addEvent(p1, str1, p3);
			break;

		case DELETE:
			if (flag == 1) {
				scanf("%d %s %d", &p1, str1, &p3);
			}
			else {
				scanf("%d %d %d", &p1, &p2, &p3);
				make_string(str1, p2);
			}
			ret = deleteEvent(p1, str1);
			if (ret != p3)
				answer = 0;
			break;

		case CHANGE:
			if (flag == 1) {
				scanf("%d %s %s %d", &p1, str1, str2, &p4);
			}
			else {
				scanf("%d %d %d %d", &p1, &p2, &p3, &p4);
				make_string(str1, p2);
				make_string(str2, p3);
			}
			ret = changeEvent(p1, str1, str2);
			if (ret != p4)
				answer = 0;
			break;

		case GETCOUNT:
			scanf("%d %d", &p1, &p2);
			ret = getCount(p1);
			if (ret != p2)
				answer = 0;
			break;

		default:
			break;
		}
	}

	return answer;
}

int main()
{
	setbuf(stdout, NULL);
	//freopen("sample_input.txt", "r", stdin);

	int T;
	scanf("%d", &T);

	for (int tc = 1; tc <= T; tc++) {
		printf("#%d %d\n", tc, run());
	}

	return 0;
}
