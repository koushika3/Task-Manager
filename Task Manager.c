#include"pq.h"

int print(elet x);
int checkequal(elet x, elet y);
int dosum( date **D, elet x, int m);
int timemang(pqueue *a);
int isdue(elet x);
int isdate_equal(date d, elet y);
elet getdate(elet x);
elet scan();
int get_hours_diff(date x, date y);


int get_hours_diff(date x, date y)
{
	return (abs( x.dd -  y.dd) * 24  + abs(x.mm - y.mm) * 24);
}

int print(elet x)
{	
	static int i = 1;
	if(x.flagod == 0)
	{
		printf("\nTask %d: %s", i ,x.t);
	}
	
    else
	{
		printf("\nTask %d: %s - OVERDUE", i ,x.t);
	}

	i++;

	return 0;
}

int checkequal(elet x, elet y)
{

	if (x.d == y.d)
		if(x.m == y.m)
			if(x.y == y.y)
				return 1;
	
	else
		return 0;
	
}

int timemang(pqueue *a)
{
	int i,j,m=0;
	time_t t = time(NULL);
  	struct tm l = *localtime(&t);
	date D[15];
	for(i = 1; i<=a->size; i++)
	{
		for(j = 1; j<i; j++)
		{
			elet x = a->data[i];
			elet y = a->data[j];
			if(checkequal(a->data[i],a->data[j]))
				break;	
		}

		if(i == j)
		{
			
			D[m].dd = a->data[i].d;
			D[m].mm = a->data[i].m;
			D[m].yy = a->data[i].y;
			D[m].hours = 0;
			m++;
		}	
	}

	for(i = 0; i<m; i++)
	{
		for(j = 1; j<=a->size ; j++)
		{

			if(isdate_equal(D[i],a->data[j]) && a->data[j].visitfl == 0)
			{
				D[i].hours += a->data[j].hrs;
				a->data[j].visitfl = 1;
			}
				
		}
	}
	
	int h = 0;

	for(i = 0; i < m; i++)
	{
		h += D[i].hours;
		date s;
		s.dd = l.tm_mday;
		s.yy = l.tm_year;
		s.mm = l.tm_mon + 1;
		
		if(get_hours_diff(D[i],s) < h - (24 - l.tm_hour))
		{
			printf("\nInsufficient time for tasks on %d/%d/%d!\n", D[i].dd, D[i].mm, D[i].yy);
		}
	}
}

int isdue(elet x)
{
	time_t t = time(NULL);
  	struct tm l = *localtime(&t);
	if(x.y == l.tm_year+1900)
	{
		if(x.m == l.tm_mon+1)
		{
			if((x.d-l.tm_mday)*24 +( 24 - l.tm_hour) >= x.hrs )
			{
				return 0;
			}
		}

		else if(x.m > l.tm_mon+1)
			return 0;
	}

	else if(x.y > l.tm_year+1900)
		return 0;

	else
	{
		return 1;
	}
}

elet getdate(elet x)
{
	printf("To be done by (dd/mm/yyyy):");
    scanf("%d/%d/%d",&x.d,&x.m,&x.y);
	return x;
}

elet scan()
{
	elet x; int b;
    printf("\nEnter task:");
	char a = getchar();
    scanf("%[^\n]", x.t);
	x = getdate(x);
	printf("Number of hours needed to do the task:");
	scanf("%d",&x.hrs);
	x.flagod = isdue(x);
	printf("Enter importance level (1-8):");
	scanf("%d", &x.il);
	x.visitfl = 0;
    x.p = x.d*24 + x.m*31*24 + x.y*365*24 - (x.hrs) - (x.il*3);
	return x;
}

int isdate_equal(date d, elet y)
{
	return(d.mm == y.m && d.dd == y.d && d.yy == y.y );
}

int main()
{
	printf("\n\n\t\t\t\t\t\t\t\tWELCOME TO TASK MANAGER\n\n");
	pqueue* a = (pqueue*) malloc(sizeof(pqueue));
	int i,n;
	printf("Enter the maximum  number of tasks you might do:");
	scanf("%d", &a->maxsize);
	printf("\nNumber of tasks at hand:");
	scanf("%d", &n);
	a = create_node();
	for(i = 0; i<n; i++)
	{
		elet x;
		x = scan();
		insert(a,x);
	}
	printf("\nTASK ORDER\n");
	display(a);
	timemang(a);
	destroy(a);
	return 0;
}
