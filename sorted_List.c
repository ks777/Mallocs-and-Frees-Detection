#include "sorted_List.h"
#include <stdlib.h>
#include <stdio.h>

sorted_List_Ptr sorted_List_Create(CompareFuncT cf) {
	sorted_List_Ptr point;
	point = (struct sorted_List *)malloc(sizeof(struct sorted_List));
	if (point == NULL) {
		printf("Error: No more memory.\n");
		return NULL;
	}
	point->compareFunct = cf;
	return point;
}

void sorted_List_Destroy(sorted_List_Ptr list) {
	Node *temp;
	while (list->start != NULL) {
		temp = list->start;
		list->start = list->start->next;
		list->destroyFunct(temp->content);
		free(temp);
	}
	free(list);
}

void *sorted_List_Find(sorted_List_Ptr list, void *newObj){
	Node *curr;
	curr = list->start;
	if (list->start == NULL) {
		return NULL;
	}
	while (curr != NULL) {
		if (list->compareFunct(curr->content, newObj) == 0) {
			return curr->content;
		}
		else {
			curr = curr->next;
		}
	}
	return NULL;
}

int sorted_List_Insert(sorted_List_Ptr list, void *newObj) {
	Node *new;
	Node *curr;
	Node *prev;
	curr = list->start;
	prev = NULL;
	new = (Node *)malloc(sizeof(Node));
	if (new == NULL) {
		printf("Error: No more memory.\n");
		return 0;
	}
	new->content = newObj;
	new->counter = 0;
	if (list->start == NULL) {
		list->start = new;
		new->counter++;
		new->next = NULL;
		return 1;
	}
	while (curr != NULL) {
		if (list->compareFunct(curr->content, newObj) == 0) {
			printf("Error: Cannot insert duplicates.\n");
			return 0;
		} else if (list->compareFunct(curr->content, newObj) > 0) {
			if (prev == NULL) {
				list->start = new;
				new->counter++;
				new->next = curr;
				return 1;
			} else {
				prev->next = new;
				new->counter++;
				new->next = curr;
				return 1;
			}
		} else {
			prev = curr;
			curr = curr->next;
		}
	}

	if (curr == NULL && prev != NULL) {
		prev->next = new;
		new->counter++;
		new->next = curr;
		return 1;
	}
	return 0;
}

int sorted_List_Remove(sorted_List_Ptr list, void *newObj) {
	Node *curr;
	Node *prev;
	curr = list->start;
	prev = NULL;
	while (curr != NULL) {
		if (list->compareFunct(curr->content, newObj) == 0) {
			if (prev == NULL) {
				list->start = curr->next;
				curr->counter--;
				if (list->start != NULL) {
					list->start->counter++;
				}
			}
			else {
				prev->next = curr->next;
				curr->counter--;
				if (prev->next != NULL) {
					prev->next->counter++;
				}
			}
			if (curr->counter <= 0) {
				list->destroyFunct(curr->content);
				if (curr->next != NULL) {
					curr->next->counter--;
				}
				free(curr);
			}
			return 1;
		} else if (list->compareFunct(curr->content, newObj) > 0) {
			prev = curr;
			curr = curr->next;
		} else {
			return 0;
		}
	}
	return 0;
}
