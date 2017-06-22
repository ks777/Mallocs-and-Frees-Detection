#ifndef SORTED_LIST_H
#define SORTED_LIST_H
#include <stdlib.h>
#include <stdio.h>

struct node
{
  int counter;
  void *content;
  struct node *next;
};
typedef struct node Node;

struct sorted_List
{
  struct node *start;
  int (* compareFunct) (void *, void *);
  void (* destroyFunct) (void *);
};
typedef struct sorted_List* sorted_List_Ptr;

struct sorted_List_Iterator
{
  struct node *curr;
  sorted_List_Ptr list;
};
typedef struct SortedListIterator* SortedListIteratorPtr;

typedef void (*DestructFuncT)( void * );
typedef int (*CompareFuncT)( void *, void * );
sorted_List_Ptr sorted_List_Create(CompareFuncT cf);
void sorted_List_Destroy(sorted_List_Ptr list);
void *sorted_List_Find(sorted_List_Ptr list, void *newObj);
int sorted_List_Insert(sorted_List_Ptr list, void *newObj);
int sorted_List_Remove(sorted_List_Ptr list, void *newObj);

#endif

