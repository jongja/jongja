/* [BOJ] 4195 
 * Complete!
 * 
 * Memory : 12920 KB
 * Time   : 48 ms
 */

#include <iostream>
#include <cstdio>
using namespace std;

#define PN 23
#define MAX_HASH_SIZE 200000
#define MAX_UNION_SIZE 200000

struct fnode
{
	char name[21];
	struct fnode* next;
	int idx;
};

struct fnode data_pool[MAX_HASH_SIZE] = { 0 };
struct fnode* hash_table[MAX_HASH_SIZE] = { 0 };
int T, F;
int data_pool_idx = 0;
int p[MAX_UNION_SIZE] = { 0 };
int c[MAX_UNION_SIZE] = { 0 };

struct fnode* salloc() {
	return &data_pool[data_pool_idx++];
}

int _strcmp(char* s1, char* s2) {
	while (*s1) {
		if (*s1 != *s2) {
			return *s1 > * s2 ? 1 : -1;
		}
		s1++; s2++;
	}
	return *s2 != '\0' ? 1 : 0;
}

void _strcpy(char* dst, char* src) {
	while (*src) *(dst++) = *(src++);
	*dst = '\0';
	return;
}

unsigned int hasing(char* str) {
	unsigned int p = 1, key = 0;
	while (*str) {
		key += (*str) * p;
		p *= PN;
		str++;
	}
	return key % MAX_HASH_SIZE;
}

fnode* hash_insert(char* str, int cnt) {
	int idx = hasing(str);
	fnode* newNode = salloc();
	newNode->next = NULL;
	newNode->idx = cnt;
	_strcpy(newNode->name, str);
	if (!hash_table[idx]) {
		hash_table[idx] = newNode;
	}
	else {
		fnode* walker = hash_table[idx];
		while (walker->next) {
			if (!_strcmp(walker->name, newNode->name)) return walker;
			walker = walker->next;
		}
		if (!_strcmp(walker->name, newNode->name)) {
			return walker;
		}
		else {
			walker->next = newNode;
		}
	}
	return newNode;
}

int find(int n) {
	if (p[n] < 0) return n;
	else {
		p[n] = find(p[n]);
		return p[n];
	}
}

int uni(int a, int b) {

	int ap = find(a);
	int bp = find(b);

	if (ap != bp) {
		p[bp] = ap;
		c[ap] += c[bp];
	}
	return c[ap];
}

void init() {
	for (int i = 0; i < MAX_HASH_SIZE; i++) {
		if (i < MAX_UNION_SIZE) {
			p[i] = -1;
			c[i] = 1;
		}
		hash_table[i] = NULL;
	}
	data_pool_idx = 0;
}

int main(void) {
	freopen("wow.csv", "r", stdin);
	int T, F, cnt = 0;
	fnode* r1, * r2;
	char s1[21] = { 0 }, s2[21] = { 0 };
	scanf("%d", &T);
	for (int i = 0; i < T; i++) {
		init();
		scanf("%d", &F);
		for (int j = 0; j < F; j++) {
			scanf("%s %s", s1, s2);
			r1 = hash_insert(s1, cnt++);
			r2 = hash_insert(s2, cnt++);
			int res = uni(r1->idx, r2->idx);
			printf("%d\n", res);
		}
	}
	return 0;
}