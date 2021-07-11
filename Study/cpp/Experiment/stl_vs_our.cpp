#include <queue>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stack>
#include <algorithm>
using namespace std;

clock_t st, ed;

#define MAX_NODE 2000
#define MAXDATA 100000
#define MAX_HEAP_SIZE MAXDATA

struct Queue {
	int size;
	int f;
	int r;
	int data[MAXDATA];

	void init() {
		size = f = r = 0;
	}
	void push(int d) {
		size++;
		data[r++] = d;
	}

	void pop(void) {
		if (size == 0) return;
		f++; size--;
	}

	int front() {
		return data[f];
	}
}qq;

struct Stack {
	int size;
	int t;
	int data[MAXDATA];

	void init() {
		size = t = 0;
	}
	void push(int d) {
		size++;
		data[t++] = d;
	}

	void pop(void) {
		if (size == 0) return;
		t--; size--;
	}

	int top() {
		return data[t];
	}
}sta;

struct Node {
	int idx;
	int heap_idx;
	int value;
	int value2;
}n[MAX_NODE];

#define MAX_HEAP_SIZE 100000

void _qsort(int l, int r, int* a) {
	if (l < r) {
		int i = l;
		int j = r + 1;
		int p = a[l];
		do {
			do i++; while (i <= r && a[i] < p);
			do j--; while (j >= l && a[j] > p);
			if (i < j) {
				int t = a[i]; a[i] = a[j]; a[j] = t;
			}
		} while (i < j);
		int t = a[j]; a[j] = a[l]; a[l] = t;
		_qsort(l, j - 1, a);
		_qsort(j + 1, r, a);
	}
}

struct Heap { // Modulization.
	int size;
	int heap[MAX_HEAP_SIZE] = { 0 };
	void init() {
		size = 0;
	}
	void push(int val) { // max heap push finction
		if (size == MAX_HEAP_SIZE) return;
		int cur = ++size;

		while (cur != 1 && heap[cur >> 1] < val) { // if we change this "<" to ">", this code become Min heap.
			heap[cur] = heap[cur >> 1];
			cur >>= 1;
		}
		heap[cur] = val;
	}
	void pop(void) {
		if (!size) return;

		int e = heap[size--];
		int cur = 1, child = 2;
		while (child <= size) {
			if (child + 1 <= size && heap[child] < heap[child + 1]) child++; // if we change this "<" to ">", this code become Min heap.
			if (heap[child] <= e) break; // if we change this "<=" to ">=", this code become Min heap.
			heap[cur] = heap[child];
			cur = child; child <<= 1;
		}
		heap[cur] = e;
	}
	int top() {
		return heap[1];
	}
}heap; // Declare as 'h'

struct cmp {
	bool opearator(int a, int b) {
		if (n[a].value > n[b].value) return true;
		else if (n[a].value == n[b].value) {
			if (n[a].value2 > n[b].value2) return true;
			else return false;
		}
		else return false;
	}
};

int main(void) {

	printf("Data Size : %d\n", MAXDATA);
	srand((unsigned int)time(NULL));

	printf("\n[QUEUE TEST]\n");
	queue<int> q;
	
	st = clock();
	for (int i = 0; i < MAXDATA; i++) {
		q.push(rand());
	}
	ed = clock();

	double stl_q_push = (double)(ed - st) / CLOCKS_PER_SEC;

	st = clock();
	for (int i = 0; i < MAXDATA; i++) {
		q.pop();
	}
	ed = clock();

	double stl_q_pop = (double)(ed - st) / CLOCKS_PER_SEC;
	
	st = clock();
	qq.init();
	for (int i = 0; i < MAXDATA; i++) {
		qq.push(rand());
	}
	ed = clock();

	double our_q_push = (double)(ed - st) / CLOCKS_PER_SEC;

	st = clock();
	for (int i = 0; i < MAXDATA; i++) {
		qq.pop();
	}
	ed = clock();

	double our_q_pop = (double)(ed - st) / CLOCKS_PER_SEC;

	printf("STL Queue - push: %lf, pop: %lf\n", stl_q_push, stl_q_pop);
	printf("OUR Queue - push: %lf, pop: %lf\n", our_q_push, our_q_pop);

	printf("\n[Stack TEST]\n");
	stack<int> s;

	st = clock();
	for (int i = 0; i < MAXDATA; i++) {
		s.push(rand());
	}
	ed = clock();

	double stl_s_push = (double)(ed - st) / CLOCKS_PER_SEC;

	st = clock();
	for (int i = 0; i < MAXDATA; i++) {
		s.pop();
	}
	ed = clock();

	double stl_s_pop = (double)(ed - st) / CLOCKS_PER_SEC;

	st = clock();
	sta.init();
	for (int i = 0; i < MAXDATA; i++) {
		sta.push(rand());
	}
	ed = clock();

	double our_s_push = (double)(ed - st) / CLOCKS_PER_SEC;

	st = clock();
	for (int i = 0; i < MAXDATA; i++) {
		sta.pop();
	}
	ed = clock();

	double our_s_pop = (double)(ed - st) / CLOCKS_PER_SEC;

	printf("STL Stack - push: %lf, pop: %lf\n", stl_s_push, stl_s_pop);
	printf("OUR Stack - push: %lf, pop: %lf\n", our_s_push, our_s_pop);

	printf("\n[HEAP TEST]\n");
	
	priority_queue<int, vector<int>, less<int> > pq;
	
	st = clock();

	for (int i = 0; i < MAXDATA; i++) {
		heap.push(rand());
	}

	ed = clock();

	double our_pq_push = (double)(ed - st) / CLOCKS_PER_SEC;
	st = clock();


	for (int i = 0; i < MAXDATA; i++) {
		heap.pop();
	}
	ed = clock();

	double our_pq_pop = (double)(ed - st) / CLOCKS_PER_SEC;

	st = clock();

	for (int i = 0; i < MAXDATA; i++) {
		pq.push(rand());
	}
	ed = clock();
	double stl_pq_push = (double)(ed - st) / CLOCKS_PER_SEC;
	st = clock();
	for (int i = 0; i < MAXDATA; i++) {
		pq.pop();
	}
	ed = clock();

	double stl_pq_pop = (double)(ed - st) / CLOCKS_PER_SEC;


	printf("STL PQ - push: %lf, pop: %lf\n", stl_pq_push, stl_pq_pop);
	printf("OUR PQ - push: %lf, pop: %lf\n", our_pq_push, our_pq_pop);


	/// SORT

	printf("\n[QUICK SORT TEST]\n");
	int arr[MAXDATA] = { 0 };
	int arr2[MAXDATA] = { 0 };

	for (int i = 0; i < MAXDATA; i++)
		arr[i] = arr2[i] = rand();

	st = clock();
	sort(arr, arr + MAXDATA - 1, less<int>());
	ed = clock();
	double stl_sort = (double)(ed - st) / CLOCKS_PER_SEC;

	st = clock();
	_qsort(0, MAXDATA - 1, arr2);
	ed = clock();
	double our_sort = (double)(ed - st) / CLOCKS_PER_SEC;

	printf("STL sort - %lf\n", stl_sort);
	printf("OUR sort - %lf\n", our_sort);
}