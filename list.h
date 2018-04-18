#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct _node
{
	unsigned char data;
	unsigned int frequency;
	struct _node* next;
	struct _node* left;
	struct _node* right;

}HUFFNODE;

typedef struct _list
{
	HUFFNODE* head;
	unsigned int size;
}HUFFLIST;

HUFFLIST* create_linked_list ()
{
	HUFFLIST* newList = (HUFFLIST*) malloc (sizeof (HUFFLIST));
	newList->head = NULL;
	newList->size = 0;

	return newList;
}

HUFFNODE* create_node (unsigned char data, unsigned int frequency)
{
	HUFFNODE* newNode = (HUFFNODE*) malloc (sizeof(HUFFNODE));
	newNode->data = data;
	newNode->frequency = frequency;

	newNode->next = NULL;
	newNode->left = NULL;
	newNode->right = NULL;

	return newNode;
}

HUFFNODE* remove_head (HUFFLIST* list)
{
	if (list->head == NULL) return NULL;

	HUFFNODE* temp = list->head;
	list->head = list->head->next;

	temp->next = NULL;

	list->size--;

	return temp;
}

void insert_with_priority (HUFFLIST* list, HUFFNODE* node)
{
	list->size++;

	if (!list->head)
	{
		list->head = node;

		return;
	}
	else
	{
		HUFFNODE* temp = list->head;
		
		if (node->frequency <= temp->frequency)
		{
			node->next = list->head;
			list->head = node;

			return;
		}
		else
		{
			while (temp->next != NULL)
			{
				if (node->frequency <= temp->next->frequency)
				{
					node->next = temp->next;
					temp->next = node;

					return;
				}
				temp = temp->next;
			}

			temp->next = node;

			return;
		}
	}
}

void print_linked_list (HUFFLIST* list)
{
	HUFFNODE* temp = list->head;

	while (temp)
	{
		printf("%c(%d) ", temp->data, temp->frequency);
		temp = temp->next;
	}
	printf("\n");
}

void print_pre_order (HUFFNODE* root)
{
	if (root)
	{
		printf("%c", root->data);
		print_pre_order (root->left);
		print_pre_order (root->right);
	}
}

HUFFNODE* merge (HUFFNODE* secondNode, HUFFNODE* firstNode)
{	
	HUFFNODE* mergedNode = create_node ('*', firstNode->frequency + secondNode->frequency);
	mergedNode->left = firstNode;
	mergedNode->right = secondNode;

	return mergedNode;
}