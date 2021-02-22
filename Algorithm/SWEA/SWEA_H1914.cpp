/* Complete!
 *
 */

#ifndef _CRT_SECURE_NO_WARNINGS 
#define _CRT_SECURE_NO_WARNINGS 
#endif

#include<stdio.h>

#define MAX_N    100
#define MAX_TOOL 50

#define ENDCASE 0
#define ADDLOT  1
#define SIMUL   2

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

bool canIpush(register Eventnode cur, register Eventnode parent) {
    if (cur.time < parent.time) {
        return true;
    }
    else if (cur.time > parent.time) {
        return false;
    }
    else {
        if (cur.tool > parent.tool) {
            return true;
        }
        else if (cur.tool < parent.tool) {
            return false;
        }
        else {
            if (cur.tools_pt < parent.tools_pt) {
                return true;
            }
            else {
                return false;
            }
        }
    }
}

bool canIpop(register Eventnode cur, register Eventnode child) {
    if (cur.time < child.time) {
        return true;
    }
    else if (cur.time > child.time) {
        return false;
    }
    else {
        if (cur.tool < child.tool) {
            return false;
        }
        else if (cur.tool > child.tool) {
            return true;
        }
        else {
            if (cur.tools_pt < child.tools_pt) {
                return true;
            }
            else {
                return false;
            }
        }
    }
}

bool canIright(register Eventnode cur, register Eventnode right) {
    if (cur.time > right.time) {
        return true;
    }
    else if (cur.time < right.time) {
        return false;
    }
    else {
        if (cur.tool > right.tool) {
            return false;
        }
        else if (cur.tool < right.tool) {
            return true;
        }
        else {
            if (cur.tools_pt > right.tools_pt) {
                return true;
            }
            else {
                return false;
            }
        }
    }
}

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
        while (cur != 1 && canIpush(val, data[cur >> 1])) {
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
            if (ch < size && canIright(data[ch], data[ch + 1])) ch++;
            if (canIpop(e, data[ch])) {
                break;
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
    for (int i = 0; i < N + 1; i++) {
        nnode[i].lots = nnode[i].working_lots = 0;
        nnode[i].t = NULL;
    }
}

void setupTool(int T, int stepNo[5000], int procTime[5000]) {
    for (int i = 0; i < T; i++) {
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
    else {
        semiconductors++;
        nnode[cur_tool].working_lots--;
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
}

void addLot(int time, int number) {
    if (heap.size == 0) {
        nnode[0].lots += number;
        register Tnode* walker = nnode[0].t;
        while (walker) {
            if (nnode[0].lots && !walker->hasLot) {
                register Eventnode cur;
                walker->hasLot = true;

                cur.time = walker->pt;
                cur.tool = 0;
                cur.tools_pt = walker->pt;
                cur.step = walker->step;

                nnode[0].working_lots++;
                nnode[0].lots--;
                heap.push(cur);

            }
            walker = walker->next;
        }
    }
    else {
        while (heap.top().time <= time) {
            startEvent();
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

int run() {
    int totalStep = 0, totalTool = 0, stepID[MAX_N * MAX_TOOL], procTime[MAX_N * MAX_TOOL];
    int event, time, number;
    int userOut, userWip[MAX_N], resultOut, resultWip[MAX_N];
    int score = 100;

    for (int j = 0; j < MAX_N; j++) {
        userWip[j] = resultWip[j] = 0;
    }

    scanf("%d %d", &totalStep, &totalTool);
    init(totalStep);
    step = 0;
    for (register int i = 0; i < totalTool; i++) {
        scanf("%d %d", stepID + i, procTime + i);
    }
    setupTool(totalTool, stepID, procTime);

    while (1) {
        step++;
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
