#include <stdio.h>
#include <stdlib.h>

//Struct to define an Element
typedef struct Element {
    int data;
    struct Element* next;
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
    return element;
}

//Function to create a List
List* CreateList() {
    List* list = malloc(sizeof(List));
    list->head = NULL;
    list->size = 0;
    return list;
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

//Function to reverse the list
void ReverseList(List* list) {
    Element* current_pos = list->head;
    Element* prev = NULL;
    Element* next = NULL;

    while (current_pos != NULL) {
        next = current_pos->next;
        current_pos->next = prev;
        prev = current_pos;
        current_pos = next;
    }

    list->head = prev;
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

    printf("Elements added to the list: ");
    PrintList(list);

    Element* to_remove = list->head;
    RemoveElement(list, elem4);

    printf("Elements still contained after remove function: ");
    PrintList(list);


    printf("Reverse List: ");
    ReverseList(list);
    PrintList(list);
    
    return 0;
}