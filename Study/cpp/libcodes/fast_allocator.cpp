#define __UNIT_TEST_FAST_ALLOC__

#include"fast_allocator.h"

#ifdef __UNIT_TEST_FAST_ALLOC__
#include<cstdio>
using namespace std;
#endif

template<typename T>
FastAlloc<T>* FastAlloc<T>::_instance = 0;

template<typename T>
FastAlloc<T>::FastAlloc(): _top(0), _alloc_idx(0) {}

template<typename T>
T* FastAlloc<T>::_alloc() {
	T* ret = 0;
	if (_top > 0) {
		_top--;
		ret = _stack[_top];
	}
	else if (_alloc_idx < __FAST_ALLOC_MAX_SIZE__) {
		ret = &(_arr[_alloc_idx++]);
	}
	return ret;
}

template<typename T>
void FastAlloc<T>::_free(T* addr) {
	if (_top >= __FAST_ALLOC_MAX_SIZE__) {
		return; // overflow
	}
	_stack[_top] = addr;
	_top++;
}

template<typename T>
T* FastAlloc<T>::alloc() {
	if (_instance == 0)
		_instance = new FastAlloc<T>();
	return _instance->_alloc();
}

template<typename T>
void FastAlloc<T>::free(T* addr) {
	if (_instance == 0) {
		return; // invalid operation
	}
	else {
		_instance->_free(addr);
	}
}

#ifdef __UNIT_TEST_FAST_ALLOC__

int main(void) {

	int *arr[100];
	for (int i = 0; i < 100; i++) {
		arr[i] = FastAlloc<int>::alloc();
		*arr[i] = i;
	}

	for (int i = 0; i < 100; i++)
		printf("%d ", *arr[i]);
	printf("\n");

	for (int i = 0; i < 100; i++)
		FastAlloc<int>::free(arr[i]);
	return 0;
}

#endif 