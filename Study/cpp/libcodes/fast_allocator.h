#ifndef __FAST_ALLOCATOR_H__
#define __FAST_ALLOCATOR_H__

#define __FAST_ALLOC_MAX_SIZE__ 100000

template<typename T>
class FastAlloc
{
private:
	T _arr[__FAST_ALLOC_MAX_SIZE__];
	T* _stack[__FAST_ALLOC_MAX_SIZE__]; // policy: the most recently used, faster cache mem approach
	int _top, _alloc_idx;

	FastAlloc<T>();
	T* _alloc();
	void _free(T* addr);

	static FastAlloc<T>* _instance;
public:
	static T* alloc();
	static void free(T* addr);
};

#endif
