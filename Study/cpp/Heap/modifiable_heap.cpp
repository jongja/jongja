/* MODIFIABLE MAX HEAP
 *  
 * Modifible Max heap algorithm for priority queue.
 * Time Complexity : O(nlogn)
 * If we want to change a node value in heap data structure, we need to keep the rules for the data structure.
 * This can be solved by using push and pop algorithms as they are.
 *
 */


#define MAX_HEAP_SIZE 100000
#define MAX_NODE 2000

struct Node {
	int idx;
	int heap_idx;
	int value;
}n[MAX_NODE];

typedef struct Heap { // Modulization.
	int size;
	int heap[MAX_HEAP_SIZE] = { 0 };
	void init() {
		size = 0;
	}

	void push(int node_idx) { 
		if (size == MAX_HEAP_SIZE) return;
		int cur = ++size;

		while (cur != 1 && n[heap[cur >> 1]].value < n[node_idx].value) { 
			heap[cur] = heap[cur >> 1];
			n[heap[cur >> 1]].heap_idx = cur;
			cur >>= 1;
		}
		heap[cur] = node_idx;
		n[node_idx].heap_idx = cur;
	}

	int pop(void) {
		if (!size) return -1;
		int res = heap[1];

		int e = heap[size--];
		int cur = 1, child = 2;
		while (child <= size) {
			if (child + 1 <= size && n[heap[child]].value < n[heap[child + 1]].value) child++;
			if (n[heap[child]].value <= n[e].value) break; 
			heap[cur] = heap[child];
			n[heap[child]].heap_idx = cur;
			cur = child; child <<= 1;
		}

		heap[cur] = e;
		n[e].heap_idx = cur;
		return res;
	}

	void delete_with_idx(int node_idx) {
		int e = heap[size--];
		int cur = n[node_idx].heap_idx, child = cur << 1;

		while (child <= size) {
			if (child + 1 <= size && n[heap[child]].value < n[heap[child + 1]].value) child++;
			if (n[heap[child]].value <= n[e].value) break;
			heap[cur] = heap[child];
			n[heap[child]].heap_idx = cur;
			cur = child; child <<= 1;
		}

		heap[cur] = e;

		while (cur != 1 && n[heap[cur >> 1]].value < n[e].value) {
			heap[cur] = heap[cur >> 1];
			n[heap[cur >> 1]].heap_idx = cur;
			cur >>= 1;
		}

		heap[cur] = e;
		n[e].heap_idx = cur;	
	}

	void modify(int node_idx, int mod_value) {
		delete_with_idx(node_idx);
		n[node_idx].value = mod_value;
		push(node_idx);
	}
}heap; 
