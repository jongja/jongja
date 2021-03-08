/* Graph
 * (with linked list)
 *
 */

#include <iostream>
using namespace std;

#define MAXV 1000
#define MAXE 2000
#define salloc() &e[sidx++];

struct Edge {
    int idx;
    int cost;
    Edge* next;
}e[MAXE];

struct Vertex {
    int idx;
    Edge* connection;
}v[MAXV];

int V, E;
int sidx = 0;

int main(void) {
    int curv, cure, cost;
    cin >> V >> E;
    for (int i = 0; i < V; i++) {
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
}