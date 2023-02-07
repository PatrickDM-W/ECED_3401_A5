#include "Uncompress.h"

void print_top(WORD* top)
{
	printf("%s", top->word);
	return;
}

WORD* to_top(int rewind, WORD* top_word) 
{
	/* for node traversal */
	WORD* curr = top_word;
	WORD* prev = top_word;

	if (rewind > 1)
	{
		for (int i = 1; i < rewind; i++)
		{
			prev = curr;
			curr = curr->next_word;
		}

		/* update stack */
		prev->next_word = curr->next_word;
		curr->next_word = top_word;
	}

	return curr;
}

WORD* push_word(char word[], WORD* top_word)
{
	WORD* new_top = new_word(word);

	new_top->next_word = top_word;

	return new_top;
}

WORD* new_word(char word[])
{
	/*
	- create a new node for the stack
	- return NULL if malloc() fails
	- return node otherwise
	- code adapted from code by Dr. Hughes
	*/

	WORD* new;

	if ((new = malloc(sizeof(WORD))) == NULL)
		return NULL;

	/* Update data and links */
	strcpy_s(new->word, MAX_WORD_LEN, word);
	new->next_word = NULL;
	return new;
}