/* DOUBLE LINKED LIST TEST
 *
 * Implement only insert(), delete(), search() functions
 * Using Static allocate
 *
 * This code for doubly liked list test.
 * By modifying MAX_DATA_SIZE, you can increase the size of the data you want to use.
 *
 */

#include <iostream>
#include <ctime>
using namespace std;

#define MAX_ALLOC_POOL_SIZE 200000
#define MAX_DATA_SIZE 100000

typedef struct LinkedListNodes
{
    int val;
    struct LinkedListNodes* next;
    struct LinkedListNodes* prev;

}node;

node allocator_pool_array[MAX_ALLOC_POOL_SIZE] = { 0 };
int allocator_pool_idx = 0;

node* salloc() { // static allocator
    return &allocator_pool_array[allocator_pool_idx++];
}

node* head = NULL;

void delete_list(int val) {
    node* walker = head;
    while (walker) {
        if (walker->val == val) { // if delete node is head
            if (walker == head) {
                head = head->next;
                head->prev = NULL;
            }
            else { // if delete node is middle or last
                walker->prev->next = walker->next;
                if (walker->next) // if walker's next is NULL (Last node)
                    walker->next->prev = walker->prev;
            }
            return;
        }
        walker = walker->next;
    }
    // cout << "NOT DATA!!" << endl;
}

void insert_list(int val) {
    node* newNode = salloc();
    newNode->next = NULL;
    newNode->prev - NULL;
    newNode->val = val;

    if (!head) {
        head = newNode;
        return;
    }
    else {
        head->prev = newNode;
        newNode->next = head;
        head = newNode;
    }
}

void test_list() { // 
    node* walker = head;
    int total = 0;
    while (walker) {
        total++;
        walker = walker->next;
    }
    cout << "Total > " << total << endl;
}


int main(void) {
    srand((unsigned int)time(NULL));
    for (int i = 0; i < MAX_DATA_SIZE; i++) {
        if (!i) insert_list(993933323);
        else if (i == 2322) insert_list(32332);
        else if (i == 32432) insert_list(433123);
        else if (i == MAX_DATA_SIZE - 1) insert_list(2451234324);
        else insert_list(rand());
    }

    delete_list(993933323); //last node test
    delete_list(32332);
    delete_list(2451234324); //head node test
    delete_list(433123);
    test_list();

    return 0;
}
