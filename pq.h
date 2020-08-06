#ifndef pq_h
#define pq_h

#include"task.h"
#include<stdio.h>
#include<stdlib.h>

typedef task elet;

typedef struct
{
	int size;
	int maxsize;
	elet *data;
}pqueue;

pqueue* create_node();
pqueue* create(elet);
int insert(pqueue*, elet);
int refactor(pqueue*);
int display(pqueue*);
int dele(pqueue*);
int swap(int i, pqueue*a );
int destroy(pqueue *);
int assign(elet *a, elet *b);
int compare(pqueue *a, int i, int j, char c[]);

#endif
