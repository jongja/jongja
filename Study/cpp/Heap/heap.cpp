/* MAX HEAP
 *  
 * Max heap algorithm for priority queue.
 * Time Complexity : O(nlogn)
 * This Max heap can simply change to Min heap. We just change three "larger than(<)"
 * to "Smaller than(<) or (>=).
 *
 */


#define MAX_HEAP_SIZE 100000

typedef struct Heap { // Modulization.
	int size;
	int heap[MAX_HEAP_SIZE] = { 0 };
	void init() {
		size = 0;
	}
	void push(int val) { // max heap push finction
		if (heap_size == MAX_HEAP_SIZE) return;
		int cur = ++heap_size;

		while (cur != 1 && heap[cur >> 1] < val) { // if we change this "<" to ">", this code become Min heap.
			heap[cur] = heap[cur >> 1];
			cur >>= 1;
		}
		heap[cur] = val;
	}
	int pop(void) {
		if (!heap_size) return -1;
		int res = heap[1];

		int e = heap[heap_size--];
		int cur = 1, child = 2;
		while (child <= heap_size) {
			if (child < heap_size && heap[child] < heap[child + 1]) child++; // if we change this "<" to ">", this code become Min heap.
			if (heap[child] <= e) break; // if we change this "<=" to ">=", this code become Min heap.
			heap[cur] = heap[child];
			cur = child; child <<= 1;
		}
		heap[cur] = e;
		return res;
	}
}heap;