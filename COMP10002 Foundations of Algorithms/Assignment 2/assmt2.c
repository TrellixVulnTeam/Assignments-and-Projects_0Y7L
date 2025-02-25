/* File name: assmt2.c
   Author: Lai Nge Nern 639702
   Date: 10/6/17
   Function: named-entity-algorithm(NER) based on a dictionary.
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>

/* Stage formatting */
#define STAGE_ONE 1
#define STAGE_TWO 2
#define STAGE_THREE 3
#define STAGE_FOUR 4
#define STAGE_FIVE 5
#define HEADING "========================="

#define READ_SUCCESS 1
#define READ_FAILED 0
#define MAX_WORD_LEN 30
#define MAX_NUM_NAME 100
#define NUM_PERCENT_CHAR 10

typedef struct word_node word_node_t;
typedef struct sentence_node sentence_node_t;
typedef struct sentence_list sentence_list_t;

struct word_node{
	char word[MAX_WORD_LEN];
	int prob_first, prob_last, prob_non;
};

struct sentence_node{
	char word[MAX_WORD_LEN];
	sentence_node_t *next;
};

struct sentence_list{
	sentence_node_t *head;
};

int read_one_word(word_node_t *node);
int get_word(char W[], int limit);
int comp(const void *a, const void *b);
double calc_average_char(word_node_t word_node[], int counter);
sentence_list_t read_sentence();
void print_labels(sentence_node_t *current_word, word_node_t *word);
void print_word_stats(word_node_t word_node[], int num_words);
void read_dictionary(word_node_t word_node[], int *counter);
void print_stage(int stage_num);
void print_name_and_probability(word_node_t word_node);
void free_memory(sentence_list_t list_info);


/* void print_dictionary(word_node_t word_node[],int counter); */

int main(int argc, char *argv[]){
	word_node_t word_properties[MAX_NUM_NAME];
	word_node_t *word;
	sentence_node_t *current_word;
	sentence_list_t list_info;
	
	int dict_len = 0;

	/* Stage One */
	if (read_one_word(&word_properties[dict_len]) == READ_SUCCESS){
		print_stage(STAGE_ONE);
		print_name_and_probability(word_properties[dict_len]);
		dict_len++;
	}else{
		exit(EXIT_FAILURE);
	}
	
	/* Stage Two */
	print_stage(STAGE_TWO);
	read_dictionary(word_properties, &dict_len);
	print_word_stats(word_properties, dict_len);
	
	/* Stage Three */
	print_stage(STAGE_THREE);
	list_info = read_sentence();
	current_word = list_info.head; /* point to list head */
	
	while(current_word != NULL){
		printf("%s\n", current_word->word);
		current_word = current_word->next;
	}
	printf("\n");
	
	/* Stage Four */
	print_stage(STAGE_FOUR);
	current_word = list_info.head; /* return to head */
	
	while(current_word != NULL){
		/* bsearch for word properties in word_nodes array */
		word = (word_node_t*)bsearch(current_word->word,
		word_properties, dict_len, sizeof(word_node_t), comp);
		
		print_labels(current_word, word);
		current_word = current_word->next;
	}
	printf("\n");
	
	/* Stage Five */
	print_stage(STAGE_FIVE);
	
	
	
	free_memory(list_info);
	
	return 0;

}

int read_one_word(word_node_t *node){
	char hash;
	
	if(scanf(" %c", &hash) == READ_SUCCESS){
		if (scanf("%s %d %d %d", node->word, &node->prob_first,
		&node->prob_last, &node->prob_non) == (READ_SUCCESS * 4)){	
			return READ_SUCCESS;
		}
		else{
			return READ_FAILED;
		}
	}
	return READ_FAILED;

}

void read_dictionary(word_node_t word_node[], int *counter){

	while(read_one_word(&word_node[*counter]) == READ_SUCCESS){
		(*counter)++;
	}
}

double calc_average_char(word_node_t word_node[], int counter){
	int i;
	double sum = 0;
	
	assert(counter > 0);
	
	for(i = 0; i < counter; i++){
		sum += strlen(word_node[i].word);
	}
	
	return sum/counter;
}

void print_stage(int stage_num){

	printf("%s", HEADING);
	printf("Stage %d", stage_num);
	printf("%s\n", HEADING);

}

void print_name_and_probability(word_node_t node){
	static int i = 0;

	printf("Word %d: %s\n", i++, node.word);
	printf("Label probabilities: %d%% %d%% %d%%\n\n", node.prob_first,
		node.prob_last, node.prob_non);
}

void print_word_stats(word_node_t word_node[], int num_words){
	
	printf("Number of words: %d\n", num_words);
	printf("Average number of characters per word: %.2lf\n\n"
	, calc_average_char(word_node, num_words));
}

sentence_list_t read_sentence(){
	char current_word[MAX_WORD_LEN];
	sentence_list_t list_info;
	
	sentence_node_t *word_previous = NULL;
	sentence_node_t *word_head;
	sentence_node_t *word_new;
	
	while(get_word(current_word, MAX_WORD_LEN) == READ_SUCCESS){
		
		word_new = (sentence_node_t*)malloc(sizeof(sentence_node_t));
		strcpy(word_new->word, current_word);
		word_new->next = NULL;
		
		if(word_previous != NULL){
			word_previous->next = word_new;
			word_previous = word_new;
		}
		else{
			word_head = word_new;
			word_previous = word_new;
		}
	}
	list_info.head =  word_head;
	return list_info;
}

int get_word(char W[], int limit) {
/* =====================================================================
   Program written by Alistair Moffat, as an example for the book
   "Programming, Problem Solving, and Abstraction with C", Pearson
   Custom Books, Sydney, Australia, 2002; revised edition 2012,
   ISBN 9781486010974.

   See http://people.eng.unimelb.edu.au/ammoffat/ppsaa/ for further
   information.

   Prepared December 2012 for the Revised Edition.
   ================================================================== */

	int c, len=0;
	/* first, skip over any non alphabetics */
	while ((c=getchar())!=EOF && !isalpha(c)) {
		/* do nothing more */
	}
	if (c==EOF) {
		return EOF;
	}
	/* ok, first character of next word has been found */
	W[len++] = c;
	while (len<limit && (c=getchar())!=EOF && isalpha(c)) {
		/* another character to be stored */
		W[len++] = c;
	}
	/* now close off the string */
	W[len] = '\0';
	return READ_SUCCESS;
}

int comp(const void *a, const void *b){
	
	word_node_t *second_arg = (word_node_t*)b;
	
	return strncmp(a, second_arg->word, MAX_WORD_LEN);
}

void print_labels(sentence_node_t *current_word, word_node_t *word){
	
	if (word){
		printf("%-32s", current_word->word);
		
		if(word->prob_first && word->prob_last){
			printf("FIRST_NAME, LAST_NAME\n");
		}
		else if(word->prob_first){
			printf("FIRST_NAME\n");
		}
		else{
			printf("LAST_NAME\n");
		}
	}
	else{
		printf("%-32s", current_word->word);
		printf("NOT_NAME\n");
	}
}

void free_memory(sentence_list_t list_info){
	sentence_node_t *head, *next;
	head = list_info.head;
	
	while(head != NULL){
		next = head->next;
		free(head);
		head = next;
	}
}
/*
void print_dictionary(word_node_t word_node[],int counter){

	int i;
	
	for(i = 0;i < counter; i++){
		printf("Name: %s\n", word_node[i].name);
		printf("prob_first: %d\n", word_node[i].prob_first);
		printf("prob_last: %d\n", word_node[i].prob_last);
		printf("prob_non: %d\n", word_node[i].prob_non);
		printf("\n");
		
	}
}
*/
