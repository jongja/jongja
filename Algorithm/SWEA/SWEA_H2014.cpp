/* Completed!
 *
 */

#ifndef _CRT_SECURE_NO_WARNINGS 
#define _CRT_SECURE_NO_WARNINGS 
#endif

#include<stdio.h>

#define MAXU 2001
#define MAXLEN 11
#define MAXH 10323
#define MAXW 4001

#define NULL 0
#define salloc() &wnode[sidx];

int sidx = 0;
int cur_time;
char str_cache[5][MAXLEN];

struct UserNode {
    int last_search_time;
    char last_search_str[MAXLEN];
    int str_idx;
}u[MAXU];

struct WordNode {
    int sidx, cnt;
    int user[3];
    char wrongWord[MAXW];
    char corrWord[MAXW];
    WordNode* h_next, * h_prev;
    WordNode* db_next, * db_prev;

}wnode[MAXW], * htable[MAXH], * dbtable[MAXH];

void mstrcpy(char* dest, const char* src)
{
    register int i = 0;
    while (src[i] != '\0')
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = src[i];
}

int mstrcmp(const char* a, const char* b)
{
    register int i;
    for (i = 0; a[i] != '\0'; i++)
    {
        if (a[i] != b[i])
            return a[i] - b[i];
    }
    return a[i] - b[i];
}

int mstrlen(const char* a)
{
    register int len = 0;

    while (a[len] != '\0')
        len++;

    return len;
}

bool need_to_register(char* wrong, char* correct) {
    int wlen = mstrlen(wrong);
    int clen = mstrlen(correct);

    if (wlen == clen) { // change one word
        int cnt = 0;
        for (; *wrong; wrong++, correct++) {
            if (*wrong == *correct) continue;
            cnt++;
            if (cnt > 1) return false;
        }
    }
    else if (wlen - 1 == clen) { // addition one word
        bool check = false;
        for (; *correct; correct++, wrong++) {
            if (*correct == *wrong) continue;
            if (check) return false;
            check = true;
            wrong++;
        }
    }
    else if (wlen + 1 == clen) { // deletion one word
        bool check = false;
        for (; *correct; correct++, wrong++) {
            if (*correct == *wrong) continue;
            if (check) return false;
            check = true;
            correct++;
        }
    }
    else return false;
    return true;
}

unsigned int hashing(char* s) {
    register unsigned int key = 0, step = 1, pn = 23;
    for (; *s; s++) {
        key += (*s) * step;
        step *= pn;
    }
    return key % MAXH;
}


/* HASH FUNCTIONS */
// @mode --> 0: hash table, 1: db table
void insert_hash(WordNode* newNode, int mode) {
    int key = hashing(newNode->wrongWord);
    if (mode == 0) {
        if (!htable[key]) {
            htable[key] = newNode;
        }
        else {
            newNode->h_next = htable[key];
            htable[key]->h_prev = newNode;
            htable[key] = newNode;
        }
    }
    else if (mode == 1) {
        if (!dbtable[key]) {
            dbtable[key] = newNode;
        }
        else {
            newNode->db_next = dbtable[key];
            dbtable[key]->db_prev = newNode;
            dbtable[key] = newNode;
        }
    }
}

int search_hash(char* wrongWord, char* corrWord, int mode) {
    int key = hashing(wrongWord);
    int ret = -1;
    if (mode == 0) {
        register WordNode* walker = htable[key];
        while (walker) {
            if (!mstrcmp(wrongWord, walker->wrongWord) && !mstrcmp(corrWord, walker->corrWord)) {
                ret = walker->sidx;
                break;
            }
            walker = walker->h_next;
        }
    }
    else {
        register WordNode* walker = dbtable[key];
        while (walker) {
            if (!mstrcmp(wrongWord, walker->wrongWord)) {
                ret++;
                mstrcpy(str_cache[ret], walker->corrWord);
            }
            walker = walker->db_next;
        }
    }
    return ret;
}

// Only support mode 0.
void delete_hash(WordNode* dnode) {

    int key = hashing(dnode->wrongWord);

    if (!dnode->h_prev) {
        htable[key] = dnode->h_next;
        if (dnode->h_next)
            dnode->h_next->h_prev = NULL;
    }
    else {
        dnode->h_prev->h_next = dnode->h_next;
        if (dnode->h_next)
            dnode->h_next->h_prev = dnode->h_prev;
    }
    dnode->h_next = NULL;
    dnode->h_prev = NULL;

    return;
}

bool isDuplicate(char* w, char* c) {
    int key = hashing(w);
    register WordNode* walker = dbtable[key];
    while (walker) {
        if (!mstrcmp(c, walker->corrWord)) {
            return false;
        }
        walker = walker->db_next;
    }
    return true;
}

/* HASH FUNCTIONS END */


void init(int n) {
    sidx = cur_time = 0;
    for (register int i = 0; i < MAXH; i++) {
        if (i < MAXU) {
            u[i].last_search_time = 0;
            u[i].str_idx = 0;
        }
        htable[i] = dbtable[i] = NULL;
    }
}

int search(int mId, int searchTimestamp, char searchWord[11], char correctWord[5][11]) {
    cur_time = searchTimestamp;
    int ret = 0, db_cnt = 0;

    if ((ret = search_hash(searchWord, u[mId].last_search_str, 1)) >= 0) {
        for (register int i = 0; i < ret + 1; i++) {
            mstrcpy(correctWord[i], str_cache[i]);
        }
        db_cnt = ret + 1;
    }

    if (!mstrcmp(u[mId].last_search_str, searchWord)) {
        u[mId].last_search_time = cur_time;
        return 0;
    }

    if (u[mId].last_search_time > 0 && cur_time - u[mId].last_search_time <= 10) {
        if (isDuplicate(u[mId].last_search_str, searchWord) && need_to_register(u[mId].last_search_str, searchWord)) {
            if ((ret = search_hash(u[mId].last_search_str, searchWord, 0)) < 0) {
                // init new Node
                WordNode* newNode = salloc();
                newNode->cnt = 1;
                mstrcpy(newNode->wrongWord, u[mId].last_search_str);
                mstrcpy(newNode->corrWord, searchWord);
                newNode->user[0] = mId;
                newNode->user[1] = newNode->user[2] = -1;
                newNode->h_next = newNode->h_prev = newNode->db_next = newNode->db_prev = NULL;
                newNode->sidx = sidx++;

                insert_hash(newNode, 0);
            }
            else {
                bool skip = false;
                for (register int i = 0; i < 3; i++)
                    if (wnode[ret].user[i] == mId) skip = true;
                if (!skip) {
                    wnode[ret].user[wnode[ret].cnt] = mId;
                    wnode[ret].cnt++;
                    if (wnode[ret].cnt == 3) { // mode to db.
                        delete_hash(&wnode[ret]);
                        insert_hash(&wnode[ret], 1);
                    }
                }
            }

        }
    }
    u[mId].last_search_time = cur_time;
    mstrcpy(u[mId].last_search_str, searchWord);
    return db_cnt;
}