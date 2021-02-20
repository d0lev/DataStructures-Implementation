#include <stdio.h>
#include "LinkedList.h"
#include "stdlib.h"

LinkedList* New() {
    LinkedList *list = NULL;
    list = (LinkedList*)malloc(sizeof(LinkedList));
    if (list) {
        list->head = NULL;
        list->tail = NULL;
        list->length = 0;
        return list;
    }
    else return NULL;
}

Node* newNode(int value) {
    Node *newnode = NULL;
    newnode = (Node*)(malloc(sizeof(Node)));
    if (newnode) {
        newnode->data = value;
        newnode->next = NULL;
        return newnode;
    }
    else return NULL;
}

void add(LinkedList *list , int value) {
    // check if the head of the list is null
    if (!list->head) {
        list->head = newNode(value);
        list->tail = list->head;
        list->length ++;
    }
    else {
        // if its not null traverse the linkedlist untill the end
        Node *current = list->head;
        while (current->next) {
            current = current->next;
        }
        // current now is the node in the last position of the linked list
        current->next = newNode(value);
        list->tail = current->next;
        list->length ++;
    }
}

void print(LinkedList *list) {
    if (!list){
      printf("empty list");
      return;
     }

    Node *current = list->head;
    printf("The length of the linkedlist is : %u\n",list->length);
    while (current) {
        if (!current->next) printf("%d --> (null)",current->data);
        else
        printf("%d --->",current->data);
        current = current->next;
    }
}

void delete(LinkedList *list , int value) {
    if (!list->length) return;
    Node *current = list->head;
    Node *previous = list->head;
    // check if the node that will be removed is the head
    if(list->head->data == value) {
        list->head = current->next;
        free(current);
        list->length --;
        return;
      }
      
    // if the node that will be removed is no the head
    // search the node and keep the previous each iteration
    else {
        while (current) {
            if (current->data == value) {
                previous->next = current->next;
                list->length --;
                free(current);
                return;
            }
            previous = current;
            current = current->next;
        }
    }
}

void freelist(LinkedList *list) {
    Node *current = list->head;
    while (current) {
        Node *delete = current;
        current = current->next;
        free(delete);        
    }
    free(list);
    list = NULL;
}

LinkedList *reverse (LinkedList *list) {
    if(!list->length) return NULL;
    Node *current = list->head;
    Node *prev = NULL;
    Node *reversed = NULL;
    while(current) {
        prev = current;
        current = current->next;
        prev->next = reversed;
        reversed = prev;
    }
    list->head = reversed;
    return list;
}

void sortlist(LinkedList *list){
    LinkedList *sortedlist = (LinkedList*)(malloc(sizeof(LinkedList)));
    add(sortedlist,list->head->data);
    Node *runner = list->head->next;
    while (runner) {
        if (runner->data < sortedlist->head->data) {
            addFirst(sortedlist,runner->data);
        }
        else addLast(sortedlist,runner->data);
        runner = runner->next;
    }

}

void addFirst(LinkedList *list ,int value) {
    if(!list->length) return;
    Node *newhead = newNode(value);
    Node *prev = list->head;
    list->head = newhead;
    list->tail = newhead;
    newhead->next = prev;
    list->length ++ ;
}

void addLast(LinkedList *list ,int value) {
    if(!list->length) return;
    Node *newnode = newNode(value);
    Node *current = list->head;
    Node *prev = list->head;
    while(current && current->data < value) {
        prev = current;
        current = current->next;
    }
    if (current == NULL) {
        prev->next = newnode;
        list->length ++ ;
    }
    else {
        prev->next = newnode;
        newnode->next = current;
        list->length ++ ;
    }

}

void bubbleSort(LinkedList *list) {
    Node *current = list->head;
    while (current) {
        Node *runner = current->next;
        while(runner) {
            if (current->data > runner->data) {
                Node *restOfList = runner->next;
                current->next = restOfList;
                runner->next = current;
                runner = current;
            }
        
            runner = runner->next;
        }
        current = current->next;
    }
    print(list);

}
