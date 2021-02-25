/* Complete!
 *
 */

#ifndef _CRT_SECURE_NO_WARNINGS 
#define _CRT_SECURE_NO_WARNINGS 
#endif

#include<stdio.h>

#define MAX_N    100
#define MAX_TOOL 50

#define MAX_T 5001
#define NULL 0

int semiconductors = 0;
int _N;
int step;

struct Eventnode {
    int tool;
    int step;
    int tools_pt;
    int time;
};

struct Tnode {
    bool hasLot;
    int pt;
    int step;
    Tnode* next;
    Tnode* prev;
}tnode[MAX_T];

struct Nnode
{
    int lots;
    int working_lots;
    Tnode* t;
}nnode[MAX_N];

struct Heap {
    int size;
    struct Eventnode data[MAX_T];
    void init() {
        size = 0;
    }
    void push(Eventnode val) {
        if (size == MAX_T) {
            return;
        }
        register int cur = ++size;
        while (cur != 1) {
            if (val.time > data[cur >> 1].time) break;
            else if (val.time == data[cur >> 1].time) {
                if (val.tool < data[cur >> 1].tool) break;
                else if (val.tool == data[cur >> 1].tool) {
                    if (val.tools_pt > data[cur >> 1].tools_pt)
                        break;
                }
            }
            data[cur] = data[cur >> 1];
            cur >>= 1;
        }
        data[cur] = val;
    }

    void pop() {
        if (!size)
            return;
        register Eventnode e = data[size--];
        register int cur = 1, ch = 2;
        while (ch <= size) {
            if (ch < size) {
                if (data[ch].time > data[ch + 1].time) ch++;
                else if (data[ch].time == data[ch + 1].time) {
                    if (data[ch].tool < data[ch + 1].tool) ch++;
                    else if (data[ch].tool == data[ch + 1].tool) {
                        if (data[ch].tools_pt > data[ch + 1].tools_pt) ch++;
                    }
                }
            }
            if (e.time < data[ch].time) {
                break;
            }
            else if (e.time == data[ch].time) {
                if (e.tool > data[ch].tool) {
                    break;
                }
                else if (e.tool == data[ch].tool) {
                    if (e.tools_pt < data[ch].tools_pt) {
                        break;
                    }
                }
            }
            data[cur] = data[ch];
            cur = ch; ch <<= 1;
        }
        data[cur] = e;
    }

    Eventnode top() {
        return data[1];
    }

}heap;

void insert_list(int to, Tnode* newNode) {
    register Tnode* walker = nnode[to].t;
    bool pushed = false;
    if (!walker) {
        nnode[to].t = newNode;
        pushed = true;
    }
    else {
        while (walker) {
            if (newNode->pt < walker->pt) {
                if (!walker->prev) {
                    newNode->next = walker;
                    walker->prev = newNode;
                    nnode[to].t = newNode;
                    pushed = true;
                    break;
                }
                else {
                    newNode->next = walker;
                    walker->prev->next = newNode;
                    newNode->prev = walker->prev;
                    walker->prev = newNode;
                    pushed = true;
                    break;
                }
            }
            walker = walker->next;
        }
    }
    if (!pushed) {
        walker = nnode[to].t;
        while (walker->next) walker = walker->next;
        walker->next = newNode;
        newNode->prev = walker;
    }
    return;
}

void init(int N) {
    _N = N;
    semiconductors = 0;
    heap.init();
    for (register int i = 0; i < N + 1; i++) {
        nnode[i].lots = nnode[i].working_lots = 0;
        nnode[i].t = NULL;
    }
}

void setupTool(int T, int stepNo[5000], int procTime[5000]) {
    for (register int i = 0; i < T; i++) {
        tnode[i].hasLot = false;
        tnode[i].next = NULL;
        tnode[i].prev = NULL;
        tnode[i].pt = procTime[i];
        tnode[i].step = i;
        insert_list(stepNo[i], &tnode[i]);
    }
}

void startEvent() {
    Eventnode cur = heap.top();
    heap.pop();
    int cur_time = cur.time;
    int cur_tool = cur.tool;
    int cur_step = cur.step;
    int cur_pt = cur.tools_pt;
    tnode[cur.step].hasLot = false;

    if (cur_tool < _N - 1) {
        nnode[cur_tool].working_lots--;
        nnode[cur_tool + 1].lots++;
        Tnode* walker = nnode[cur_tool + 1].t;
        while (walker) {
            if (!walker->hasLot) {
                walker->hasLot = true;
                cur.time += walker->pt;
                cur.tool = cur_tool + 1;
                cur.tools_pt = walker->pt;
                cur.step = walker->step;
                nnode[cur_tool + 1].lots--;
                nnode[cur_tool + 1].working_lots++;
                heap.push(cur);
                break;
            }
            walker = walker->next;
        }
    }
    else {
        semiconductors++;
        nnode[cur_tool].working_lots--;
    }
    if (nnode[cur_tool].lots) {
        nnode[cur_tool].lots--;
        nnode[cur_tool].working_lots++;
        tnode[cur_step].hasLot = true;
        cur.time = cur_time + cur_pt;
        cur.tool = cur_tool;
        cur.tools_pt = cur_pt;
        cur.step = cur_step;
        heap.push(cur);
    }
}

void addLot(int time, int number) {
    if (heap.size > 0) {
        while (heap.top().time <= time) {
            startEvent();
        }
    }
    nnode[0].lots += number;
    register Tnode* walker = nnode[0].t;
    while (walker) {
        if (nnode[0].lots && !walker->hasLot) {
            register Eventnode cur;
            walker->hasLot = true;
            cur.time = time + walker->pt;
            cur.tool = 0;
            cur.tools_pt = walker->pt;
            cur.step = walker->step;
            nnode[0].working_lots++;
            nnode[0].lots--;
            heap.push(cur);
        }
        walker = walker->next;
    }
    return;
}

int simulate(int time, int wip[MAX_N]) {
    while (heap.size && heap.top().time <= time) {
        startEvent();
    }
    for (register int i = 0; i < _N; i++)
        wip[i] = nnode[i].lots + nnode[i].working_lots;
    return semiconductors;
}