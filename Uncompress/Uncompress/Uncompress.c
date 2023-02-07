/****************************************
Oct 10th, 2022
Patrick Wain

MorseDecoder.c
Main program containing entry point
****************************************/

#include "Uncompress.h"

FILE* infile;

int main(int argc, char* argv[])
{
	/*
	- open file in argv[i], reads and checks sentences
	- at EOF, stop reading and close
	- if only one argument (.exe name), stop executing
	*/

	/* check number of arguments */
	if (argc == 1)
	{
		printf("Missing file name\n");
		getchar();
		return -1;
	}

	for (int i = 1; i < argc; ++i)
	{
		/* argc >= 1, attempt to open file */
		if (fopen_s(&infile, argv[i], "r") != 0)
		{
			printf("Error opening file >%s< - possibly missing\n", argv[1]);
			getchar();
			return -1;
		}

		/* file is open */
		/* variables */
		char ch;
		char word[MAX_WORD_LEN];
		WORD* top_word = NULL;
		int j = 0;

		ch = fgetc(infile);

		while (ch != EOF && ch != '0')
		{
			if (isdigit(ch))
			{
				/*
				- is digit, indicates compression
				- find value of digit(s)
				- move indicated word to top of stack
				- word will be printed at next punctuation or space
				- must be run before other checks b/c updates ch
				- should never occur after an alpha
				- never needs to end word
				*/
				int val = 0;

				while (isdigit(ch))
				{
					val *= 10;
					val += (ch - ASCII_NUM_OFFSET);

					ch = fgetc(infile);
				}

				/*
				- adjust stack
				- reset j
				- j == 0 used as flag later
				*/
				top_word = to_top(val, top_word);
				print_top(top_word);
				j = 0;
			}


			if (isalpha(ch))
			{
				/* is alpha, add to word */
				word[j] = ch;
				j++;
			}
			else
			{
				/* not digit, not alpha */
				if (!j)
				{
					/* 
					- no word to update 
					- last char was non-alpha
					- print next non-alpha
					*/
					printf("%c", ch);
				}
				else
				{
					/*
					- end current word
					- push to stack
					- print top of stack
					- print current char
					- reset word
					*/
					word[j] = NUL;
					top_word = push_word(word, top_word);
					print_top(top_word);
					printf("%c", ch);
					j = 0;
				}
			}

			ch = fgetc(infile);
		}

		printf("\nfile complete");
		getchar();

		fclose(infile);
		printf("\n");
	}

	printf("Waiting to quit ...\n");
	getchar();

	return 0;
}