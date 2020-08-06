#include"pq.h"

pqueue* create_node()
{
	pqueue* a;
	a = (pqueue*) malloc(sizeof(pqueue));
	a->data = (elet*) malloc(a->maxsize*sizeof(elet));
	a->data[0].p=333;
	a->size = 0;
	return a;	
}

pqueue* create(elet x)
{
	pqueue* a = create_node();
	a->data[1] = x;
	a->size++;
	return a;
}

int insert(pqueue* a, elet x)
{
	a->size++;
	a->data[a->size] = x; 
	if(a->size/2>=1)
		if(compare(a,a->size/2,a->size,">"))
			refactor(a);
	return 0;
}

int refactor(pqueue *a)
{
	int i = a->size;
	while(i>1)
	{
		if(compare(a,i/2,i,">"))
			swap(i,a);
		i=i/2;
	}
	return 0;
}

int display(pqueue* a)
{
	int i;
	for(i = 1;i <= a->size;i++)
		print(a->data[i]); 
	printf("\n");
	return 0;
}

int dele(pqueue* a)
{
	int min,i=1;
	a->data[i] = a->data[a->size--];
	while(2*i <= a->size)
	{
		min = i;
		if(compare(a,min,2*i,">"))
			min = 2*i;
		if(compare(a,min,2*i+1,">"))
			min = 2*i + 1;

		if(min!=i)
			swap(min,a);
		i=2*i;
	}
	return 0;
}

int swap(int i, pqueue*a )
{
	elet temp ;
	assign(&temp, &a->data[i]);
	assign(&a->data[i], &a->data[i/2]);
	assign(&a->data[i/2], &temp);
	return 0;
}

int assign(elet *a, elet *b)
{
	a->p = b->p;
	a->d = b->d;
	a->m = b->m;
	a->y = b->y;
	strcpy(a->t,b->t);
}

int destroy(pqueue *a)
{
	free(a->data);
}

int compare(pqueue *a, int i, int j, char c[])
{
	if(strcmp(c,">"))
		return(a->data[i].p>a->data[j].p);
}