/* Completed!
 *
 */


#include <stdio.h>

#define NULL 0
#define MAXE 60001
#define MAXN 1001
#define MAXG 101
#define MAXLEN 20
#define MAXH 7003
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
}node[MAXE], * htable[MAXG][MAXH];

struct User {
	int cnt;
	Event* events;
}u[MAXN];

int tarray[5] = { 0 };
int tarray_cnt = 0;


/* STRING FUNCTIONS */
void _strcpy(register char dst[], register const char src[]) {
	int c = 0;
	while ((dst[c] = src[c]) != 0) ++c;
}

int _strcmp(register const char str1[], register const char str2[]) {
	int c = 0;
	while (str1[c] != 0 && str1[c] == str2[c]) ++c;
	return str1[c] - str2[c];
}

/* STRING FUNCTIONS END */


/* HASH FUNCTIONS */
int hashing(char* s) {
	unsigned int key = 0, step = 1;
	for (register int i = 0; s[i]; i++) {
		key += step * s[i];
		step *= PN;
	}
	return key % MAXH;
}

void insert_hash(int gid, Event* newNode) {
	int key = hashing(newNode->name);
	if (!htable[gid][key]) {
		htable[gid][key] = newNode;
		newNode->master = true;
	}
	else {
		register Event* walker = htable[gid][key];
		bool canImaster = true;
		while (walker) {
			if (!_strcmp(walker->name, newNode->name)) canImaster = false;
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

Event* delete_hash(int uid, int gid, register char* name) {
	int key = hashing(name);
	register Event* dnode = NULL;
	register Event* walker = htable[gid][key];
	if (!walker) return NULL;
	while (walker) {
		if (!_strcmp(walker->name, name) && uid == walker->uid) {
			dnode = walker;
			if (!walker->h_prev) { // if dnode is head
				htable[gid][key] = walker->h_next;
				if (walker->h_next)
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
	if (dnode)
		dnode->h_next = dnode->h_prev = NULL;
	return dnode;
}

Event* delete_hash2(int gid, register char* name) {
	int key = hashing(name);
	register Event* dnode = NULL;
	register Event* walker = htable[gid][key];
	if (!walker) return NULL;
	while (walker) {
		if (!_strcmp(walker->name, name)) {
			dnode = walker;
			if (!walker->h_prev) { // if dnode is head
				htable[gid][key] = walker->h_next;
				if (walker->h_next)
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
	if (dnode)
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
		register Event* walker = u[uid].events;
		while (walker) {
			if (!walker->u_next) { // go to last node.
				walker->u_next = newNode;
				newNode->u_prev = walker;
				break;
			}
			walker = walker->u_next;
		}
	}
	u[uid].cnt++;
	return;
}

Event* delete_user(int uid, register char* name) {
	register Event* dnode = NULL;
	register Event* walker = u[uid].events;
	if (!walker) return NULL;
	while (walker) {
		if (!_strcmp(walker->name, name)) {
			dnode = walker;
			if (!walker->u_prev) { // if dnode is head
				u[uid].events = walker->u_next;
				if (walker->u_next)
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
	u[uid].cnt--;

	dnode->u_next = dnode->u_prev = NULL;
	return dnode;
}

/* USER FUNCTIONS END*/

void init() {
	sid = tarray_cnt = 0;
	for (register int g = 0; g < MAXG; g++) {
		for (register int i = 0; i < MAXH; i++) {
			if (i < MAXN) {
				u[i].cnt = 0;
				u[i].events = NULL;
			}
			htable[g][i] = NULL;
		}
	}
	return;
}

int changeEvent(int uid, char ename[], char cname[]) {
	int ccnt = 0;
	bool isMaster = false;
	register Event* walker = u[uid].events;
	while (walker) {
		if (!_strcmp(ename, walker->name)) {
			break;
		}
		walker = walker->u_next;
	}
	if (!walker) return 0;

	ccnt++;
	walker = delete_hash(uid, walker->gid, ename);
	_strcpy(walker->name, cname);
	isMaster = walker->master;
	insert_hash(walker->gid, walker);
	if (!isMaster) return 1;

	tarray_cnt = tarray[0] = tarray[1] = tarray[2] = tarray[3] = tarray[4] = 0;
	register Event* walker_2 = walker;
	while (walker_2) {
		walker_2 = delete_hash2(walker_2->gid, ename);
		if (walker_2) {
			ccnt++;
			tarray[tarray_cnt++] = walker_2->sid;
		}
	}

	for (register int i = 0; i < tarray_cnt; i++) {
		_strcpy(node[tarray[i]].name, cname);
		if (i + 1 < tarray_cnt) {
			node[tarray[i]].h_next = &node[tarray[i + 1]];
			node[tarray[i + 1]].h_prev = &node[tarray[i]];
		}
	}
	if (tarray_cnt > 0) {
		walker->h_next = &node[tarray[0]];
		node[tarray[0]].h_prev = walker;
	}

	return ccnt;
}

int deleteEvent(int uid, char ename[]) {
	int dcnt = 0;
	Event* walker = u[uid].events;
	while (walker) {
		if (!_strcmp(ename, walker->name)) {
			break;
		}
		walker = walker->u_next;
	}
	if (!walker) return 0;

	dcnt++;
	walker = delete_hash(uid, walker->gid, ename);
	delete_user(uid, ename);
	if (!walker->master) return 1;

	while (walker) {
		walker = delete_hash2(walker->gid, ename);
		if (walker) {
			delete_user(walker->uid, ename);
			dcnt++;
		}
	}

	return dcnt;
}

void addEvent(int uid, char ename[], int groupid) {
	Event* newNode = salloc();
	newNode->sid = sid++;
	newNode->gid = groupid;
	newNode->uid = uid;
	newNode->master = false;
	newNode->h_next = newNode->h_prev = newNode->u_next = newNode->u_prev = NULL;
	_strcpy(newNode->name, ename);
	insert_hash(groupid, newNode);
	insert_user(uid, newNode);
	return;
}

int getCount(int uid) {
	return u[uid].cnt;
}