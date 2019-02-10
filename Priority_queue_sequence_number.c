#include <stdio.h>
#include <stdlib.h>

// Priority Queue - Queue data structure where elements are arranged as per sequence number
// Since nodes are inserted in sorted order of sequence number, insertion operation is the key function.
// Dequeue is always done from the front of the queue.
// Enqueue is done in sorted manner

// Key data structures are as follows

struct node {
	int sequence_number;
	struct node *next;
};

struct priority_q {
	struct node *front;
	struct node *rear;
};

struct priority_q *pq_ds = NULL;

int init_queue()
{
    pq_ds = (struct priority_q *)malloc(sizeof(struct priority_q));
    if(pq_ds == NULL)
    {
        return -1;
    }
    else
    {
    	pq_ds->front = NULL;
    	pq_ds->rear = NULL;
    	return 0;
    }
}

struct node * create_node(int value)
{
	struct node *new_node = (struct node *)malloc(sizeof(struct node));
	if(new_node != NULL)
	{
		new_node->sequence_number = value;
		new_node->next = NULL;
		return new_node;
	}
	else
		return NULL;
}

int enqueue(int value)
{
	struct node *trav = NULL, *prev = NULL;
	struct node *nd = (struct node *)malloc(sizeof(struct node));
	if(nd != NULL)
	{
		nd->sequence_number = value;
		nd->next = NULL;
	}
	else
	{
		printf("Error inserting node - memory allocation failed\n");
		return -1;
	}
	
	if(pq_ds->front==pq_ds->rear && pq_ds->rear==NULL) // First Node
	{
		pq_ds->front = nd;
		pq_ds->rear = nd;
	}
	else
	{
		trav = pq_ds->front;

		while(trav != NULL && trav->sequence_number<=value)
		{
			prev = trav;
			trav = trav->next;
		}
		if(trav == pq_ds->front && prev == NULL)
		{
		    pq_ds->front = nd;
		    nd->next = trav;
		}
		else if(trav != NULL)
		{
			// prev is the node after which new node gets inserted.
			nd->next = prev->next;
			prev->next = nd;
		}
		else // if trav is NULL, it means we reached the end node.
		{
			prev->next = nd;
			nd->next = NULL;
			pq_ds->rear = nd; // Update rear
		}
	}
}

struct node * dequeue()
{
	struct node *nd = NULL;
	if(pq_ds->front != NULL)
	{
		nd = pq_ds->front;
		pq_ds->front = nd->next;
		return nd;
	}
	else
	{
		// empty queue
		return NULL;
	}
}

void print_q()
{
	struct node *nd = NULL;
	nd = dequeue();
	while(nd != NULL)
	{
		printf("Node Value: %d\n",nd->sequence_number);
		nd = dequeue();
	}
}

/* Test Code*/
int main()
{
	init_queue();
	enqueue(15);
	enqueue(10);
	enqueue(5);
	enqueue(50);
	enqueue(20);
	enqueue(25);
	enqueue(30);
	enqueue(22);
	enqueue(18);

	print_q();
}
