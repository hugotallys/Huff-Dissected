#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "list.h"
#include "encoding.h"

#define ASCII_SIZE 256

struct stream {
	unsigned char* string;
	unsigned int size;
	unsigned int freq[ASCII_SIZE];
};

void read_stream (struct stream * myStream, unsigned char character)
{
		myStream->size++;
		myStream->string = (unsigned char*) realloc (myStream->string, myStream->size * sizeof (unsigned char));
		myStream->string[myStream->size - 1] = character;
		myStream->freq[character]++;	
}

int main ( )
{
	FILE* file = fopen ("test.txt", "rb");
	FILE* pict = fopen ("snake.jpeg", "rb");
	FILE* copy = fopen ("descubra.jpg", "wb");

	int i;
	unsigned char character;
	struct stream myStream;

	myStream.string = NULL;
	for (i = 0; i < ASCII_SIZE; ++i)
	{
		myStream.freq[i] = 0;
	}
	myStream.size = 0;

	while (fscanf (pict, "%c", &character) != EOF)
	{
		read_stream (&myStream, character);	
	}
	
	HUFFLIST* myList = create_linked_list ();

	for (i = 0; i < ASCII_SIZE; ++i)
	{
		if (myStream.freq[i])
		{
			insert_with_priority (myList, create_node(i, myStream.freq[i]));
		}
	}

	while (myList->size > 1)
	{
		insert_with_priority (myList, merge (remove_head(myList), remove_head(myList)));
	}

	for(i = 0;i < myStream.size;i++)
	{
		fprintf(copy, "%c", myStream.string[i]);
	}

	//print_pre_order (myList->head);
	//printf("\n");

	fclose(file);
	fclose(copy);
	fclose(pict);

	return 0;
}

