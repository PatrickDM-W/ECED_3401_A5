#pragma once
/****************************************
Oct 11th, 2022
Patrick Wain

MorseDecoder.h
Header file containing common files and definitions
****************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_WORD_LEN 64
#define NUL '\0'
#define ASCII_NUM_OFFSET 48

typedef struct word WORD;

extern void print_top(WORD* top);
extern WORD* to_top(int rewind, WORD* top_word);
extern WORD* push_word(char word[], WORD* top_word);
extern WORD* new_word(char word[]);

struct word 
{
	char word[MAX_WORD_LEN];
	WORD* next_word;
};