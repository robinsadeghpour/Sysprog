#include "prio_q.h"

// creates new priority queue
struct prio_q *prio_q_create()
{
	// initialize new priority queue
	struct prio_q *new_list = malloc(sizeof(struct prio_q));
	new_list->front = NULL;
	new_list->size = 0;

	return new_list;
}

// enqueues element
void prio_q_enqueue(struct prio_q *q, void *data, int prio)
{
	// initialize new element
	struct prio_q_elem *new_elem = malloc(sizeof(struct prio_q_elem));
	new_elem->data = data;
	new_elem->priority = prio;
	new_elem->next = NULL;

	// if the queue is empty insert the new element
	if (q->size == 0)
	{
		q->front = new_elem;
		q->size++;

		return;
	}

	// queue is not empty
	struct prio_q_elem *current_elem = q->front;
	struct prio_q_elem *previos_elem = NULL;

	// iterate through queue until elemt to prepend to is found
	while (current_elem != NULL && current_elem->priority >= prio)
	{
		previos_elem = current_elem;
		current_elem = current_elem->next;
	}
	if (previos_elem != NULL)
	{
		// we found an element that is > prio and prepend new element to it		
		new_elem->next = previos_elem->next;	// new element points to current element
		previos_elem->next = new_elem;			// previous element points to new element

		q->size++;

		return;
	}
	// previous element is null and new element has higher priority
	new_elem->next = current_elem;
	q->front = new_elem;
	q->size++;

}

// dequeues element and returns data pointer of it
void *prio_q_dequeue(struct prio_q *q)
{
	if (q->size == 0)
	{
		// queue is empty
		return NULL;
	}
	else
	{
		// queue is not empty
		// store pointer to data of dequeued element and element itself
		struct arb_data *data = q->front->data;
		struct prio_q_elem *tmp_elem = q->front;

		// shift front pointer to next element and decrease size counter
		q->front = q->front->next;
		q->size--;
		free(tmp_elem);

		return data;
	}
}

// return data of front element
void *prio_q_front(struct prio_q *q)
{
	return q->front->data;
}

// frees priority queue
int prio_q_destroy(struct prio_q *q, void **data)
{
	struct prio_q_elem *tmp;
	int i = 0;
	int data_count = 0;

	// iterate through queue and free elements
	while (q->front != NULL)
	{
		tmp = q->front->next;

		if (data != NULL)
		{
			// store data pointer in data[]
			data[i] = q->front->data;
			data_count++;
		}
		free(q->front);

		q->front = tmp;
		i++;
	}
	free(q);

	return data_count;
}

// print all the elements in the queue to stdout
void prio_q_print(struct prio_q *q, void (*print_data)(void *))
{
	// Implementierung dieser Funktion ist OPTIONAL und wird daher NICHT BEWERTET!
	struct prio_q_elem *tmp = q->front;

	// iterate through priority queue and print data
	while (tmp != NULL)
	{
		print_data(tmp->data);
		tmp = tmp->next;
	}
}
