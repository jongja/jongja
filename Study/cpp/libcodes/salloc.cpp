/* STATIC ALLOCATOR
 *
 * Using Template <T>
 * Usage : <typename> *var = salloc<typename>();
 *
*/

#include <iostream>
using namespace std;

#define MAX_ALLOC_POOL_SIZE 2000000

typedef struct AllocStruct // For testing..
{
    int a;
    int b;
    AllocStruct* next;
}node;


// STATIC ALLOCATOR //
template <typename T>
T allocator_pool_array[MAX_ALLOC_POOL_SIZE] = { 0 };
int allocator_pool_idx = 0;

template <typename T>
T* salloc() { // static allocator
    return &allocator_pool_array<T>[allocator_pool_idx++];
}

// END //

int main(void) {
    node* hello = salloc<node>();
    hello->a = 10;
    hello->b = 20;
    hello->next = NULL;

    node* newNode = salloc<node>();
    newNode->a = 30;
    newNode->b = 40;
    newNode->next = NULL;

    //int* newNode = salloc<int>();

    hello->next = newNode; // Connected
    return 0;
}
