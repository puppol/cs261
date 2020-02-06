/*
 * This is the file in which you'll write a function to reverse a linked list.
 * Make sure to add your name and @oregonstate.edu email address below:
 *
 * Name:
 * Email:
 */

#include <stdio.h>
#include "assert.h"

#include "list_reverse.h"

/*
 * In this function, you will be passed the head of a singly-linked list, and
 * you should reverse the linked list and return the new head.  The reversal
 * must be done in place, and you may not allocate any new memory in this
 * function.
 *
 * Params:
 *   head - the head of a singly-linked list to be reversed
 *
 * Return:
 *   Should return the new head of the reversed list.  If head is NULL, this
 *   function should return NULL.
 */
struct link* list_reverse(struct link* head) {
	if (head == NULL)
		return NULL;
	struct link* current_link = head;
	struct link* prev_link = NULL;
	struct link* next_link = NULL;

	while (current_link != NULL) {
		next_link = current_link->next;
		current_link->next = prev_link;
		prev_link = current_link;
		current_link = next_link;
	}
	head = prev_link;
}
