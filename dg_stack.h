#ifndef DG_STACK_H_INCLUDED
#define DG_STACK_H_INCLUDED

#include <malloc.h>

#define LIST struct list

//LIST is used as edge in adjacency list
//and as element in stack
LIST {
    int key;
    int value;
    LIST *next;
};

LIST* Create(int key, int value) {
    LIST *res;

    res = (LIST*)malloc(sizeof(LIST));
    res -> key = key;
    res -> value = value;
    res -> next = NULL;

    return res;
}

//inserting element into the stack
void Insert(LIST *pre, LIST *elem) {
    if (pre -> next == NULL)
        pre -> next = elem;
    else {
        if (elem -> value > pre -> next -> value)
            Insert(pre -> next, elem);
        else {
            elem -> next = pre -> next;
            pre -> next = elem;
        }
    }
}

//adding edge in the adjacency list
void Add(LIST *first, LIST *elem) {
    if(first -> next != NULL)
        Add(first -> next, elem);
    else
        first -> next = elem;
}

//clearing adjacency list
void Clear(LIST *first) {
    if (first -> next != NULL)
        Clear(first -> next);
    free(first);
}

#endif // DG_STACK_H_INCLUDED
