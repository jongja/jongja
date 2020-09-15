/* DOUBLE LINKED LIST
 *
 * Implement only insert(), delete(), search() functions
 * Using Static allocate
 *
 */

typedef struct LinkedListNodes
{
    int val;
    struct LinkedListNodes* next;
    struct LinkedListNodes* prev;

}node;

void delete_list(int val) {
    node* walker = head;
    while (walker) {
        if (walker->val == val) { // if delete node is head
            if (!walker->prev) { // if head node,
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
}

void insert_list(int val) {
    node* newNode = salloc();
    newNode->next = NULL;
    newNode->prev = NULL;
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