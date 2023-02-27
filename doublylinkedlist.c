#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Struct to define an Element
typedef struct Element {
    int data;
    struct Element* next;
    struct Element* prev;
} Element;

//Struct to define a List
typedef struct List {
    Element* head;
    int size;
} List;

//Function to create a new Element
Element* CreateElement(int data) {
    Element* element = malloc(sizeof(Element));
    element->data = data;
    element->next = NULL;
    element->prev = NULL;
    return element;
}

//Function to create a List
List* CreateList() {
    List* list = malloc(sizeof(List));
    list->head = NULL;
    list->size = 0;
    return list;
}

//Function to insert an element after another
void InsertElementAfter(Element* prevElement, int data) {
    if (prevElement == NULL) {
        return;
    }
    Element* newElement = (Element*)malloc(sizeof(Element));
    newElement->data = data;
    newElement->next = prevElement->next;
    newElement->prev = prevElement;
    prevElement->next = newElement;
    if (newElement->next != NULL) {
        newElement->next->prev = newElement;
    }
}

//Function to insert an element before another
void InsertElementBefore(Element** headRef, Element* nextElement, int data) {
    if (nextElement == NULL) {
        return;
    }
    Element* newElement = (Element*)malloc(sizeof(Element));
    newElement->data = data;
    newElement->prev = nextElement->prev;
    newElement->next = nextElement;
    if (nextElement->prev != NULL) {
        nextElement->prev->next = newElement;
    } else {
        *headRef = newElement;
    }
    nextElement->prev = newElement;
}


//Function to add an element at the head
void PreInsertHead(List* list, int data) {
    Element* element = CreateElement(data);
    element->next = list->head;
    list->head = element;
    list->size++;
}

//Function to remove an element from the list
void RemoveElement(List* list, int data) {
    Element* current_pos = list->head;
    Element* prev = NULL;

    while (current_pos != NULL && current_pos->data != data) {
        prev = current_pos;
        current_pos = current_pos->next;
    }

    if (current_pos == NULL) { 
        return;
    }

    if (prev == NULL) {
        list->head = current_pos->next;
    } else {
        prev->next = current_pos->next;
    }

    free(current_pos);
    list->size--;
}

//Function to shuffle all the elements of the list
void ShuffleList(Element** head) {
    int size = 0;
    Element* current = *head;
    while (current != NULL) {
        size++;
        current = current->next;
    }
    srand(time(NULL));
    for (int i = 0; i < size - 1; i++) {
        int j = i + rand() % (size - i);
        current = *head;
        for (int k = 0; k < i; k++) {
            current = current->next;
        }
        Element* element1 = current;
        for (int k = i; k < j; k++) {
            current = current->next;
        }
        Element* element2 = current;
        int tmp = element1->data;
        element1->data = element2->data;
        element2->data = tmp;
    }
}

//Function to print all the elements of the list
void PrintList(List* list) {
    Element* current_pos = list->head;
    while (current_pos != NULL) {
        printf("%d ", current_pos->data);
        current_pos = current_pos->next;
    }
    printf("\n");
}

int main() {
    List* list = CreateList();

    int elem1 = 1;
    int elem2 = 2;
    int elem3 = 3;
    int elem4 = 4;
    int elem5 = 5;

    PreInsertHead(list, elem1);
    PreInsertHead(list, elem2);
    PreInsertHead(list, elem3);
    PreInsertHead(list, elem4);
    PreInsertHead(list, elem5);

    Element* prevElement = list->head->next;
    InsertElementAfter(prevElement, 6);

    Element** head = &list->head;
    Element* nextElement = list->head;
    InsertElementBefore(head, nextElement, 7);


    printf("Elements added to the list: ");
    PrintList(list);

    RemoveElement(list, elem4);

    printf("Elements still contained after remove function: ");
    PrintList(list);


    printf("Shuffle List: ");
    ShuffleList(head);
    PrintList(list);
    
    return 0;
}