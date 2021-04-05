#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

#define CMD_INIT		100
#define CMD_ADD			200
#define CMD_MOVETYPE	300
#define CMD_MOVENAME	400
#define CMD_DELETENAME	500
#define CMD_COUNTBOOK	600

#define MAX_N			5
#define MAX_NAME_LEN	7
#define MAX_TAG_LEN		4

#define MAX_BOOK    50000
#define MAX_TYPE    MAX_BOOK * MAX_N
#define MAXM 101
#define NULL 0
#define MAX_BOOK_H  30023
#define MAX_TYPE_H  10023

#define book_alloc() &b[bidx++];
#define type_alloc() &ty[tidx++];

int bidx, tidx, _M;

void mstrcpy(char dst[], const char src[]) {
    register int c = 0;
    while ((dst[c] = src[c]) != '\0') ++c;
}

int mstrcmp(const char str1[], const char str2[]) {
    register int c = 0;
    while (str1[c] != '\0' && str1[c] == str2[c]) ++c;
    return str1[c] - str2[c];
}

struct Book {
    char name[MAX_NAME_LEN];
    char type[MAX_N][MAX_TAG_LEN];
    int type_idx[MAX_N];
    int type_cnt;
    int section;
    Book* name_hash_next;
    Book* name_hash_prev;
    Book* section_hash_next;
    Book* section_hash_prev;
}b[MAX_BOOK], * section[MAXM], * name_htable[MAX_BOOK_H];

struct Type
{
    char name[MAX_TAG_LEN];
    bool valid;
    int bookid;
    Type* next;
}ty[MAX_TYPE], * type_htable[MAX_TYPE_H];

int hashing(char* s) {
    register unsigned int key = 0, step = 1;
    for (register int i = 0; s[i]; i++) {
        key += (step * s[i]);
        step *= 23;
    }
    return key % MAX_BOOK_H;
}

int hashing_ty(char* s) {
    register unsigned int key = 0, step = 1;
    for (register int i = 0; s[i]; i++) {
        key += (step * s[i]);
        step *= 19;
    }
    return key % MAX_TYPE_H;
}

void insert_name_hash(Book* newNode) {
    register int key = hashing(newNode->name);

    if (!name_htable[key]) {
        name_htable[key] = newNode;
    }
    else {
        newNode->name_hash_next = name_htable[key];
        name_htable[key]->name_hash_prev = newNode;
        name_htable[key] = newNode;
    }
}

void insert_type_hash(int mTypeNum, char mTypes[MAX_N][MAX_TAG_LEN]) {
    register int key = 0;
    for (register int i = 0; i < mTypeNum; i++) {
        key = hashing_ty(mTypes[i]);
        Type* newTy = type_alloc();
        mstrcpy(newTy->name, mTypes[i]);
        newTy->bookid = bidx - 1;
        newTy->valid = true;
        newTy->next = NULL;
        b[bidx - 1].type_idx[i] = tidx - 1;

        if (!type_htable[key]) {
            type_htable[key] = newTy;
        }
        else {
            newTy->next = type_htable[key];
            type_htable[key] = newTy;
        }
    }
}

void delete_name_hash(Book* dnode) {
    if (!dnode->name_hash_prev) {
        int key = hashing(dnode->name);
        name_htable[key] = dnode->name_hash_next;
        if (dnode->name_hash_next)
            dnode->name_hash_next->name_hash_prev = NULL;
    }
    else {
        dnode->name_hash_prev->name_hash_next = dnode->name_hash_next;
        if (dnode->name_hash_next)
            dnode->name_hash_next->name_hash_prev = dnode->name_hash_prev;
    }
    dnode->name_hash_next = dnode->name_hash_prev = NULL;
}

void delete_section_hash(Book* dnode) {
    if (!dnode->section_hash_prev) {
        int key = dnode->section;
        section[key] = dnode->section_hash_next;
        if (dnode->section_hash_next)
            dnode->section_hash_next->section_hash_prev = NULL;
    }
    else {
        dnode->section_hash_prev->section_hash_next = dnode->section_hash_next;
        if (dnode->section_hash_next)
            dnode->section_hash_next->section_hash_prev = dnode->section_hash_prev;
    }
    dnode->section_hash_next = dnode->section_hash_prev = NULL;
}

void init(int M)
{
    bidx = tidx = 0;
    _M = M;
    for (register int i = 0; i < MAX_BOOK_H; i++) {
        name_htable[i] = NULL;
        if (i < _M + 1) section[i] = NULL;
        if (i < MAX_TYPE_H) type_htable[i] = NULL;
    }
}

void add(char mName[MAX_NAME_LEN], int mTypeNum, char mTypes[MAX_N][MAX_TAG_LEN], int mSection)
{
    Book* newBook = book_alloc();
    mstrcpy(newBook->name, mName);
    newBook->section = mSection;
    newBook->name_hash_next = newBook->name_hash_prev = newBook->section_hash_next = newBook->section_hash_prev = NULL;
    newBook->type_cnt = mTypeNum;
    for (register int i = 0; i < mTypeNum; i++) {
        mstrcpy(newBook->type[i], mTypes[i]);
    }

    insert_name_hash(newBook);
    insert_type_hash(mTypeNum, mTypes);

    register int key = newBook->section;
    if (!section[key]) {
        section[key] = newBook;
    }
    else {
        newBook->section_hash_next = section[key];
        section[key]->section_hash_prev = newBook;
        section[key] = newBook;
    }
}

int moveType(char mType[MAX_TAG_LEN], int mFrom, int mTo)
{
    register int cnt = 0;
    register int key = hashing_ty(mType);
    register Type* walker = type_htable[key];
    Book* dnode = NULL;
    while (walker) {
        if (walker->valid && !mstrcmp(mType, walker->name) && b[walker->bookid].section == mFrom) {
            dnode = &b[walker->bookid];

            delete_section_hash(dnode);
            dnode->section = mTo;

            key = b[walker->bookid].section;

            if (!section[key]) {
                section[key] = dnode;
            }
            else {
                dnode->section_hash_next = section[key];
                section[key]->section_hash_prev = dnode;
                section[key] = dnode;
            }
            cnt++;
        }
        walker = walker->next;
    }

    return cnt;
}

void moveName(char mName[MAX_NAME_LEN], int mSection)
{
    int key = hashing(mName);
    Book* walker = name_htable[key];
    while (walker) {
        if (!mstrcmp(walker->name, mName)) {
            break;
        }
        walker = walker->name_hash_next;
    }
    delete_section_hash(walker);
    walker->section = mSection;

    key = walker->section;
    if (!section[key]) {
        section[key] = walker;
    }
    else {
        walker->section_hash_next = section[key];
        section[key]->section_hash_prev = walker;
        section[key] = walker;
    }
}

void deleteName(char mName[MAX_NAME_LEN])
{
    int key = hashing(mName);
    Book* walker = name_htable[key];
    while (walker) {
        if (!mstrcmp(walker->name, mName)) {
            break;
        }
        walker = walker->name_hash_next;
    }
    delete_name_hash(walker);
    delete_section_hash(walker);

    for (int i = 0; i < walker->type_cnt; i++) {
        ty[walker->type_idx[i]].valid = false;
    }

}

int countBook(int mTypeNum, char mTypes[MAX_N][MAX_TAG_LEN], int mSection)
{
    register int cnt = 0, key;
    register Type* walker = NULL;
    bool check[MAX_BOOK] = { false };
    int cache[MAX_BOOK] = { 0 };

    for (int i = 0; i < mTypeNum; i++) {
        key = hashing_ty(mTypes[i]);
        walker = type_htable[key];
        while (walker) {
            if (walker->valid && !check[walker->bookid] && !mstrcmp(mTypes[i], walker->name) && b[walker->bookid].section == mSection) {
                check[walker->bookid] = true;
                cache[cnt] = walker->bookid;
                cnt++;
            }
            walker = walker->next;
        }
    }

    for (register int i = 0; i < cnt; i++) check[cache[i]] = false;
    return cnt;
}

static bool run()
{
    int  Q;
    int  cmd, M, mTypeNum, mSection, mFrom, mTo;
    char mName[MAX_NAME_LEN], mType[MAX_TAG_LEN], mTypes[MAX_N][MAX_TAG_LEN];

    int  ret, ans;

    scanf("%d", &Q);

    bool okay = false;

    for (int q = 0; q <= Q; ++q)
    {
        scanf("%d", &cmd);

        switch (cmd)
        {
        case CMD_INIT:
            scanf("%d", &M);
            init(M);
            okay = true;
            break;
        case CMD_ADD:
            scanf("%s %d", mName, &mTypeNum);
            for (int i = 0; i < mTypeNum; ++i)
                scanf("%s", mTypes[i]);
            scanf("%d", &mSection);
            if (okay)
                add(mName, mTypeNum, mTypes, mSection);
            break;
        case CMD_MOVETYPE:
            scanf("%s %d %d", mType, &mFrom, &mTo);
            if (okay)
                ret = moveType(mType, mFrom, mTo);
            scanf("%d", &ans);
            if (ret != ans)
                okay = false;
            break;
        case CMD_MOVENAME:
            scanf("%s %d", mName, &mSection);
            if (okay)
                moveName(mName, mSection);
            break;
        case CMD_DELETENAME:
            scanf("%s", mName);
            if (okay)
                deleteName(mName);
            break;
        case CMD_COUNTBOOK:
            scanf("%d", &mTypeNum);
            for (int i = 0; i < mTypeNum; ++i)
                scanf("%s", mTypes[i]);
            scanf("%d", &mSection);
            if (okay)
                ret = countBook(mTypeNum, mTypes, mSection);
            scanf("%d", &ans);
            if (ret != ans)
                okay = false;
            break;
        }
    }
    return okay;
}

int main()
{
    setbuf(stdout, NULL);
    freopen("input.txt", "r", stdin);

    int T, MARK;
    scanf("%d %d", &T, &MARK);

    for (int tc = 1; tc <= T; tc++)
    {
        int score = run() ? MARK : 0;

        printf("#%d %d\n", tc, score);
    }

    return 0;
}
