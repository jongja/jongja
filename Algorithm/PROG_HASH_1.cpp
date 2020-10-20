/* [PROG] Hash lesson 1
 *
 * Complete!
 *
 */

#include <vector>
#include <string>
#include <iostream>
using namespace std;

#define MAXH 200000
#define salloc() &nodes[sidx+];

struct hnode
{
	string name;
	bool complete;
	hnode* next;
}nodes[100000];

hnode* htable[MAXH] = { 0 };

int sidx = 0;

int hashing(string s) {
	unsigned int key = 0, step = 1;
	for (int i = 0; s[i]; i++) {
		key += step * s[i];
		step *= 23;
	}
	return key % MAXH;
}

void insert_hash(hnode* n) {
	int idx = hashing(n->name);
	if (!htable[idx]) {
		htable[idx] = n;
	}
	else {
		n->next = htable[idx];
		htable[idx] = n;
	}
	return;
}

void* find_hash(string name) {
	int idx = hashing(name);
	hnode* walker = htable[idx];

	while (walker) {
		if (walker->name == name && !walker->complete) {
			walker->complete = true;
			break;
		}
		walker = walker->next;
	}
}

string solution(vector<string> participant, vector<string> completion) {
	string answer = "";
	sidx = 0;
	int plen = participant.size();
	int clen = completion.size();
	for (int i = 0; i < plen; i++) {
		hnode* newNode = salloc();
		newNode->name = participant[i];
		newNode->complete = false;
		newNode->next = NULL;
		insert_hash(newNode);
	}

	for (int i = 0; i < clen; i++) {
		find_hash(completion[i]);
	}

	for (int i = 0; i < sidx; i++) {
		if (!nodes[i].complete) {
			answer = nodes[i].name;
			break;
		}
	}
	return answer;
}