//List.h
//Aaron Hom
//pa2
//Header file for List ADT

#ifndef _LIST_H_INCLUDE_
#define _LIST_H_INCLUDE_

//Exported type----------------------------------------------------------------
typedef struct ListObj* List;

// Constructors-Destructors ---------------------------------------------------

//newList()
//Creates new empty list
List newList(void);

//freeList()
//Frees all heap memory associated with List *pL and sets *pL to NULL
void freeList(List* pL);

// Access functions -----------------------------------------------------------

//length()
//Returns length
int length(List L);

//index()
//Returns cursor index, otherwise returns -1
int index(List L);

//front()
//Returns front element of list
//Pre: length() > 0
int front(List L);

//back()
//Returns back element of list
//Pre: length() > 0
int back(List L);

//get()
//Returns cursor element
//Pre: length() > 0, index() >= 0
int get(List L);

//equals
//Returns true if A and B are same integer sequence, cursor ignored
int equals(List A, List B);

// Manipulation procedures ----------------------------------------------------

//clear()
//Resets list to original empty state
void clear(List L);

//moveFront()
//If list is non empty, places cursor under front element, does nothing otherwise
void moveFront(List L);

//moveBack()
//If list is non empty, places cursor under back element, does nothing otherwise
void moveBack(List L);

//movePrev()
//If cursor is defined and not at front, moves cursor one step toward
//front of this List, if cursor is defined and at front, cursor becomes
//undefined, if cursor is undefined does nothing.
void movePrev(List L);

//moveNext()
//If cursor is defined and not at back, moves cursor one step toward
//back of this List, if cursor is defined and at back, cursor becomes
//undefined, if cursor is undefined does nothing.
void moveNext(List L);

//prepend()
//Insert new element into this List. If List is non-empty,
//insertion takes place before front element
void prepend(List L, int data);

//append()
//Insert new element into this List. If List is non-empty,
//insertion takes place after back  element
void append(List L, int data);

//insertBefore()
//Insert new element before cursor.
//Pre: length()>0, index()>=0
void insertBefore(List L, int data);

//insertAfter()
//Inserts new element after cursor.
//Pre: length()>0, index()>=0
void insertAfter(List L, int data);

//deleteFront()
//Deletes the front element. Pre: length()>0
void deleteFront(List L);

//deleteBack()
//Deletes the back element. Pre: length()>0
void deleteBack(List L);

//delete()
//Deletes cursor element, making cursor undefined.
//Pre: length()>0, index()>=0
void delete(List L);

// Other operations -----------------------------------------------------------

//printList()
//Prints list to out file
void printList(FILE* out, List L);

//copyList()
//Returns a new List representing the same integer sequence as this
//List. The cursor in the new list is undefined, regardless of the
//state of the cursor in this List. This List is unchanged.
List copyList(List L);

#endif
