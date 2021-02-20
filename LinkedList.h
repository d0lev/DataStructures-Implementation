#if !defined(LINKED_LIST_H)
#define LINKED_LIST_H

typedef struct Node {
    int data;
    struct Node* next;
}Node;

typedef struct LinkedList {
    unsigned int length;
    Node *head , *tail;
} LinkedList;

LinkedList* New();
Node* newNode(int);
void add(LinkedList*,int);
void print(LinkedList*);
void delete(LinkedList*,int);
void freelist(LinkedList*);
LinkedList *reverse (LinkedList *list);
void sortlist(LinkedList *list);
void addFirst(LinkedList *list ,int value);
void addLast(LinkedList *list ,int value);
void bubbleSort(LinkedList *list);


#endif // LINKED_LIST_H

