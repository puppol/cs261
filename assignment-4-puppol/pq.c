/*
 * In this file, you will write the structures and functions needed to
 * implement a priority queue.  Feel free to implement any helper functions
 * you need in this file to implement a priority queue.  Make sure to add your
 * name and @oregonstate.edu email address below:
 *
 * Name: puppol@oregonstate.edu
 * Email: Luke Puppo
 */

#include <stdlib.h>
#include "pq.h"
#include "assert.h"
#include "dynarray.h"

 /*
  * This is the structure that represents a priority queue.  You must define
  * this struct to contain the data needed to implement a priority queue.
  */
struct pq {
	struct dynarray * values;
	struct dynarray * priorities;
};


void swap(struct pq* pq, int idx1, int idx2) {
	void * v1 = dynarray_get(pq->values, idx1);
	int p1 = dynarray_get(pq->priorities, idx1);

	dynarray_set(pq->values, idx1, dynarray_get(pq->values, idx2));
	dynarray_set(pq->priorities, idx1, dynarray_get(pq->priorities, idx2));

	dynarray_set(pq->values, idx2, v1);
	dynarray_set(pq->priorities, idx2, p1);
}


/*
 * This function should allocate and initialize an empty priority queue and
 * return a pointer to it.
 */
struct pq* pq_create() {
	struct pq * pq = malloc(sizeof(struct pq));
	pq->values = dynarray_create();
	pq->priorities = dynarray_create();

	return pq;
}


/*
 * This function should free the memory allocated to a given priority queue.
 * Note that this function SHOULD NOT free the individual elements stored in
 * the priority queue.  That is the responsibility of the caller.
 *
 * Params:
 *   pq - the priority queue to be destroyed.  May not be NULL.
 */
void pq_free(struct pq* pq) {
	assert(pq);
	dynarray_free(pq->values);
	dynarray_free(pq->priorities);
	free(pq);
}


/*
 * This function should return 1 if the specified priority queue is empty and
 * 0 otherwise.
 *
 * Params:
 *   pq - the priority queue whose emptiness is to be checked.  May not be
 *     NULL.
 *
 * Return:
 *   Should return 1 if pq is empty and 0 otherwise.
 */
int pq_isempty(struct pq* pq) {
	assert(pq);
	if (!dynarray_size(pq->values) && !dynarray_size(pq->priorities))
		return 1;
	if (dynarray_size(pq->values) != dynarray_size(pq->priorities))
		printf("Mismatched arrays");
	return 0;
}




/*
 * This function should insert a given element into a priority queue with a
 * specified priority value.  Note that in this implementation, LOWER priority
 * values are assigned to elements with HIGHER priority.  In other words, the
 * element in the priority queue with the LOWEST priority value should be the
 * FIRST one returned.
 *
 * Params:
 *   pq - the priority queue into which to insert an element.  May not be
 *     NULL.
 *   value - the value to be inserted into pq.
 *   priority - the priority value to be assigned to the newly-inserted
 *     element.  Note that in this implementation, LOWER priority values
 *     should correspond to elements with HIGHER priority.  In other words,
 *     the element in the priority queue with the LOWEST priority value should
 *     be the FIRST one returned.
 */
void pq_insert(struct pq* pq, void* value, int priority) {
	int currSize = dynarray_size(pq->values);
	int currIndex = currSize;
	int currParent; //Parent node

	dynarray_insert(pq->values, -1, value);
	dynarray_insert(pq->priorities, -1, priority);
	printf("%d\n", priority);
	currSize++;

	currParent = (currIndex - 1) / 2; //Parent node
	if (currSize > 1) {
		while (currParent > -1 && dynarray_get(pq->priorities, currParent) > priority) {
			swap(pq, currIndex, currParent);
			currIndex = currParent;
			currParent = (currParent - 1) / 2;
		}
	}
}


/*
 * This function should return the value of the first item in a priority
 * queue, i.e. the item with LOWEST priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   LOWEST priority value.
 */
void* pq_first(struct pq* pq) {
	return dynarray_get(pq->values, 0);
}


/*
 * This function should return the priority value of the first item in a
 * priority queue, i.e. the item with LOWEST priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a priority value.  May not be
 *     NULL or empty.
 *
 * Return:
 *   Should return the priority value of the first item in pq, i.e. the item
 *   with LOWEST priority value.
 */
int pq_first_priority(struct pq* pq) {
	return dynarray_get(pq->priorities, 0);
}


/*
 * This function should return the value of the first item in a priority
 * queue, i.e. the item with LOWEST priority value, and then remove that item
 * from the queue.
 *
 * Params:
 *   pq - the priority queue from which to remove a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   LOWEST priority value.
 */




void rebuild_min_heap(struct pq* pq, int index, int size) {
	int left = index * 2 + 1;
	int right = index * 2 + 2;
	int smallest;
	if (left <= size && dynarray_get(pq->priorities, left) < dynarray_get(pq->priorities, index))
		smallest = left;
	else
		smallest = index;
	if (right <= size && dynarray_get(pq->priorities, right) < dynarray_get(pq->priorities, smallest))
		smallest = right;
	if (smallest != index) {
		swap(pq, index, smallest);
		rebuild_min_heap(pq, smallest, size);
	}
}



void* pq_remove_first(struct pq* pq) {
	void * retValue = dynarray_get(pq->values, 0);

	int size = dynarray_size(pq->priorities) - 1;
	// printf("Before remove: ");
	// dynarray_print(pq->priorities);

	swap(pq, 0, size);
	// printf("Swap end to first: ");
	// dynarray_print(pq->priorities);

	dynarray_remove(pq->values, -1);
	dynarray_remove(pq->priorities, -1);
	// printf("Removed last element: ");
	// dynarray_print(pq->priorities);

	rebuild_min_heap(pq, 0, size - 1);

	// printf("\n After remove: ");
	// dynarray_print(pq->priorities);
	// printf("\n");

	//dynarray_print_pointers(pq->values);
	return retValue;
}
