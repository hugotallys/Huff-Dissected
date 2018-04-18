typedef struct lnode
{
	int bit;
	struct lnode* next;
}lnode;

typedef struct list
{
	lnode* head;
}list;

list* create_list()
{
	list* l = malloc(sizeof(list*));
	l->head = 0;
	return l;
}

lnode* create_lnode(int bit)
{
	lnode* n = malloc(sizeof(lnode));
	n->bit = bit;
	n->next = NULL;
	return n;
}

void add_end(list* l, lnode* n)
{
	if(!l->head)
	{
		l->head = n;
	}
	else
	{
		lnode* temp = l->head;

		while(temp->next)
		{
			temp = temp->next;
		}

		temp->next = n;
	}
}