//List.c 
//Aaron Hom
//pa2
//List ADT round 2 ft. C language

#include<stdio.h>
#include<stdlib.h>
#include "List.h"

// structs --------------------------------------------------------------------

// private NodeObj type
typedef struct NodeObj{
  int data;
  struct NodeObj* next;
  struct NodeObj* prev;
} NodeObj;

// private Node type
typedef NodeObj* Node;

// private ListObj type
typedef struct ListObj{
  Node front;
  Node back;
  Node cursor;
  int length;
  int cursorIndex;
} ListObj;

// Constructors-Destructors ---------------------------------------------------

// newNode()
// Returns reference to new Node object. Initializes next and data fields.
// Private.
Node newNode(int data){
  Node N = malloc(sizeof(NodeObj));
  N->data = data;
  N->next = NULL;
  N->prev = NULL;
  return(N);
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
// Private.
void freeNode(Node* pN){
  if( pN!=NULL && *pN!=NULL ){
    free(*pN);
    *pN = NULL;
  }
}

// newList()
// Returns reference to new empty Queue object.
List newList(void){
  List L;
  L = malloc(sizeof(ListObj));
  L->front = L->back = L->cursor = NULL;
  L->length = 0;
  L->cursorIndex = -1;
  return(L);
}

// freeList()
// Frees all heap memory associated with Queue *pQ, and sets *pQ to NULL.S
void freeList(List* pL){
  if(pL != NULL && *pL != NULL) {
    Node stay = (*pL)->front;  
    while(stay != NULL){
      Node go = stay;
      stay = stay->next;
      free(go);
    } 
  free(*pL);
  *pL = NULL;
  }
}

// Access functions -----------------------------------------------------------

// length()
// Returns the length of Q.
int length(List L){
  if(L == NULL){
    printf("List Error: calling length() on NULL List reference\n");
    exit(1);
  }
  return(L->length);
}

//index()
//Returns index of cursor in L
//Pre: !isEmpty(L)
int index(List L){
  if(L == NULL){
    printf("List Error: calling index() on NULL List reference\n");
    exit(1);
  }
  if(L->length <= 0){
    printf("List Error: calling index() on an empty List\n");
    exit(1);
  }
  return(L->cursorIndex);
}

// front()
// Returns the value at the front of L.
// Pre: !isEmpty(L)
int front(List L){
  if(L == NULL){
    printf("List Error: calling front() on NULL List reference\n");
    exit(1);
  }
  if(L->length <= 0){
    printf("List Error: calling front() on an empty List\n");
    exit(1);
  }
  return(L->front->data);
}

// back()
// Returns the value at the back of L.
// Pre: !isEmpty(L)
int back(List L){
  if(L == NULL){
    printf("List Error: calling back() on NULL List reference\n");
    exit(1);
  }
  if(L->length <= 0){
    printf("List Error: calling back() on an empty List\n");
    exit(1);
  }
  return(L->back->data);
}

// get()
// Returns cursor element
// Pre: length() > 0, index() >= 0
int get(List L){
  if(L == NULL){
    printf("List Error: calling get() on NULL List reference\n");
    exit(1);
  }
  if(L->length <= 0){
    printf("List Error: calling get() on an empty List\n");
    exit(1);
  }
  return(L->cursor->data);
}

//equals()
// returns true (1) if A is identical to B, false (0) otherwise
int equals(List A, List B){  
  Node N = NULL;
  Node M = NULL;
  if(A == NULL||B == NULL){
    printf("List Error: calling equals() on NULL List reference\n");
    exit(1);
  }
  N = A->front;
  M = B->front;
  while(M->next != NULL && N->next != NULL){
    if(M->data != N->data){
      return(0);
    }
      M = M->next;
      N = N->next;
  }
    return(1);
}

// isEmpty()
// Returns true (1) if Q is empty, otherwise returns false (0)
int isEmpty(List L){
  if(L == NULL){
    printf("List Error: calling isEmpty() on NULL List reference\n");
    exit(1);
  }
  if(L->length == 0){
    return(1);
  }else{
    return(0);
  }
}


// Manipulation procedures ----------------------------------------------------

//clear()
//Resets list to original empty state
void clear(List L){
  if(L == NULL){
    printf("List Error: clear() called on NULL list reference\n");
    exit(1);
  }
  Node collect = L->front;
  while(collect != NULL){
    Node sweep = collect;
    collect = collect->next;
    free(sweep);
  }
  L->front = L->back = L->cursor = NULL;
  L->cursorIndex = -1;
  L->length = 0;
}

//moveFront()
//If list is non empty, places cursor under front element, does nothing otherwise
void moveFront(List L){
  if(isEmpty(L) == 1){
    printf("List Error: calling moveFront() on an empty List\n");
    exit(1);
  }
  if(L == NULL){
    printf("List Error: calling moveFront() on an NULL List reference\n");
    exit(1);
  }else if(L->length > 0){
  L->cursorIndex = 0;
  L->cursor = L->front;
  }
}

//moveBack()
//If list is non empty, places cursor under back element, does nothing otherwise
void moveBack(List L){
  if(isEmpty(L) == 1){
    printf("List Error: calling moveBack() on an empty List\n");
    exit(1);
  }
    if(L == NULL){
      printf("List Error: calling moveBack() on an empty List\n");
      exit(1);
    }else if(L->length > 0){
    L->cursorIndex = length(L) - 1;
    L->cursor = L->back;
  }
}

//movePrev()
//If cursor is defined and not at front, moves cursor one step toward
//front of this List, if cursor is defined and at front, cursor becomes
//undefined, if cursor is undefined does nothing.
void movePrev(List L){
  if(L == NULL){
    printf("List Error: calling get() on an NULL List reference\n");
    exit(1);
  }
  if(L->cursor->prev != NULL){
    L->cursor = L->cursor->prev;
    L->cursorIndex--;
  }else{
    L->cursor = NULL;
    L->cursorIndex = -1;
  }
}

//moveNext()
//If cursor is defined and not at back, moves cursor one step toward
//back of this List, if cursor is defined and at back, cursor becomes
//undefined, if cursor is undefined does nothing.
void moveNext(List L){
  if(L == NULL){
    printf("List Error: calling get() on an NULL List reference\n");
    exit(1);
  }
  if(L->cursor->next != NULL && L->cursorIndex != L->length -1){
    L->cursor = L->cursor->next;
    L->cursorIndex++;
  }else if(L->cursor != NULL && L->cursorIndex == L->length -1){
    L->cursor = NULL;
    L->cursorIndex = -1;
  }
}

//prepend()
//Insert new element into this List. If List is non-empty,
//insertion takes place before front element
void prepend(List L, int data){
  if(L == NULL){
    printf("List Error: calling get() on an NULL List reference\n");
    exit(1);
  }
  Node element = newNode(data);
  if(length(L) <= 0){
    L->front = L->back = element;
  }else{
    element->prev = NULL;
    element->next = L->front;
    L->front->prev = element;
    L->front = element;
  }
  L->length++;
}

// append()
// Places new data element at the end of L
void append(List L, int data){
  if(L == NULL){
    printf("List Error: calling get() on an NULL List reference\n");
    exit(1);
  }
  Node element = newNode(data);
  if(length(L) <= 0){
    L->front = L->back = element;
  }else{
    element->prev = L->back;
    element->next = NULL;
    L->back->next = element;
    L->back = element;
  }
  L->length++;
}

// insertBefore()
// Insert new element before cursor.
// Pre: length()>0, index()>=0
void insertBefore(List L, int data){
  if(L == NULL){
    printf("List Error: calling get() on an NULL List reference\n");
    exit(1);
  }  
  if(length(L) <= 0 || L->cursorIndex < 0){
    printf("List Error: calling insertBefore() on empty list\n");
    exit(1);
  }
  Node element = newNode(data);
  if(index(L) == 0){
    prepend(L, data);
  }else{
    element->next = L->cursor;
    element->prev = L->cursor->prev;
    L->cursor->prev->next = element;
    L->cursor->prev = element;
    L->length++;
    L->cursorIndex++;
  }
}
 
//insertAfter()
// Insert new element after cursor.
// Pre: length()>0, index()>=0
void insertAfter(List L, int data){
  if(L == NULL){
    printf("List Error: calling get() on an NULL List reference\n");
    exit(1);
  }
  if(length(L) <= 0 || index(L) < 0){
    printf("List Error: calling insertAfter() on empty list\n");
    exit(1);
  }else if(L->cursorIndex > length(L)){
    printf("List Error: calling insertAfter() on empty list\n");
  }
  Node element = newNode(data);
  if(index(L) == length(L) - 1){
    append(L, data);
  }else{
    element->next = L->cursor->next;
    element->prev = L->cursor;
    L->cursor->next = element;
    L->cursorIndex++;
    L->length++;
  } 
}

// deleteFront()
// Deletes element at front of L
// Pre: !isEmpty(L)
void deleteFront(List L){
 if(L == NULL){
    printf("List Error: calling deleteFront() on NULL List reference\n");
    exit(1);
  }
 if(isEmpty(L) == 1){
    printf("List Error: calling deleteFront() on an empty List\n");
    exit(1);
  }
 Node F = L->front;
  F = L->front;
  if(L->length <= 0) { 
    L->front = L->front->next; 
  }else{ 
    L->front = L->back = NULL; 
  }
  L->length--;
  freeNode(&F);
}

//deleteBack()
//Deletes the back element. Pre: length()>0
void deleteBack(List L){
  if(L == NULL){
    printf("List Error: calling deleteBack() on NULL List reference\n");
    exit(1);
  }
  if(isEmpty(L) == 1){
    printf("List Error: calling deleteBack() on an empty List\n");
    exit(1);
  }
  Node B = L->back;
  if(length(L) > 1) {
    L->back = L->back->prev;
  }else{
    L->front = L->back = NULL;
  }
  L->length--;
  freeNode(&B);
}

//delete()
//Deletes cursor element, making cursor undefined.
//Pre: length()>0, index()>=0
 void delete(List L){
   if(length(L) <= 0){
    printf("List Error: delete() called on empty list\n");
    exit(1);
  }
   if(index(L) < 0){
     printf("List Error: delete() called on undefined cursor\n");
     exit(1);
   }
   if(L == NULL){
     printf("List Error: delete() called on NULL list reference\n");
     exit(1);
   }
  Node tempCursor = L->cursor;
  L->cursor->prev->next = L->cursor->next;
  L->cursor->next->prev = L->cursor->prev;
  freeNode(&tempCursor);
  L->cursor = NULL;
  L->cursorIndex = -1;
  L->length--;
}

// Other operations -----------------------------------------------------------

//printList()
//Prints list to out file
void printList(FILE* out, List L){
  Node display = L->front;
  while(display != NULL){
    printf("%d\n", display->data);
    display = display->next;
  }
}

//copyList()
//Returns a new List representing the same integer sequence as this
//List. The cursor in the new list is undefined, regardless of the
//state of the cursor in this List. This List is unchanged.
List copyList(List L){
  List dupe = newList();
  Node temp = L->front;
  while(temp != NULL){
    append(dupe, temp->data);
    temp = temp->next;
  }
  return dupe;
}

