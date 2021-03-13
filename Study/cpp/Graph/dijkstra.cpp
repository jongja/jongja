/* Dijkastra with linked list Graph
 * 
 * Minimum route Algorithm.
 * This algorithm use priority queue made by MIN Heap.
 * This algorithm need its own table to update minimum route.
 */
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
using namespace std;

#define MAXV 1000
#define MAXE 2000
#define salloc() &e[sidx++];
#define MAX_HEAP_SIZE 10000
#define INF 10000000

struct Pair {
	int cost;
	int cur;
};

typedef struct Heap { 
	int size;
	Pair heap[MAX_HEAP_SIZE] = { 0 };
	void init() {
		size = 0;
	}
	void push(Pair val) { 
		if (size == MAX_HEAP_SIZE) return;
		int cur = ++size;

		while (cur != 1 && heap[cur >> 1].cost > val.cost) { 
			heap[cur] = heap[cur >> 1];
			cur >>= 1;
		}
		heap[cur] = val;
	}
	Pair pop(void) {
		if (!size) return { -1,-1 };
		Pair res = heap[1];

		Pair e = heap[size--];
		int cur = 1, child = 2;
		while (child <= size) {
			if (child + 1 <= size && heap[child].cost > heap[child + 1].cost) child++; 
			if (heap[child].cost >= e.cost) break;
			heap[cur] = heap[child];
			cur = child; child <<= 1;
		}
		heap[cur] = e;
		return res;
	}
}heap;


struct Edge {
    int idx;
    int cost;
    Edge* next;
}e[MAXE];

struct Vertex {
    Edge* connection;
}v[MAXV];

int V, E;
int sidx = 0;
int dtable[MAXV];

void dijkstra(int cur) {
	heap minh;
	minh.init();

	for (int i = 0; i < V; i++) dtable[i] = INF;
	dtable[cur] = 0;

	Edge* walker = v[cur].connection;
	while (walker) {
		dtable[walker->idx] = walker->cost;
		minh.push({ walker->cost, walker->idx });
		walker = walker->next;
	}

	Pair top;

	while (minh.size) {
		top = minh.pop();
		walker = v[top.cur].connection;
		while (walker) {
			if (dtable[walker->idx] > top.cost + walker->cost) {
				dtable[walker->idx] = top.cost + walker->cost;
				minh.push({ top.cost + walker->cost , walker->idx });
			}
			walker = walker->next;
		}
	}

}

int main(void) {
    freopen("input.txt", "r", stdin);
    int curv, cure, cost;
    cin >> V >> E;
    for (int i = 0; i < E; i++) {
        cin >> curv >> cure >> cost;

        Edge* newE = salloc();
        newE->idx = cure;
        newE->next = NULL;
        newE->cost = cost;
        if (!v[curv].connection) {
            v[curv].connection = newE;
        }
        else {
            newE->next = v[curv].connection;
            v[curv].connection = newE;
        }
    }

	dijkstra(0);


	cout << "[Minimum costs of each node]" << endl;
	for (int i = 1; i < V; i++) {
		cout << 0 << " to " << i << " : " << dtable[i] << endl;
	}
}