#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "freq_list.h"

Node *find_word_node(Node *head, char *word);
void print_query(Node *node, char **filenames);
void bubble_sort(int numbers[], int indexes[], int array_size);
void init_indexes(int indexes[], int array_size);

int main(int argc, char **argv) {
    Node **head = malloc(sizeof(Node *));
    Node *word_node;
    char **filenames = init_filenames();
    char ch;
    char *indexfile = "index";
    char *namefile = "filenames";
    char *word;

    while((ch = getopt(argc, argv, "i:n:")) != -1) {
    	switch (ch) {
            case 'i':
            	indexfile = optarg;
            	break;
            case 'n':
                namefile = optarg;
                break;
            default:
                fprintf(stderr, "Usage: indexfile [-i FILE] [-n FILE ] FILE...\n");
                exit(1);
        }
    }
    
    if (argv[optind] == NULL) { // No word arguments were given.
	fprintf(stderr, "Usage: indexfile [-u FILE] [-n FILE] FILE...\n");
	exit(1);
    }

    word = argv[optind];
    read_list(namefile, indexfile, head, filenames);
    word_node = find_word_node(*head, word);
    
    if (word_node != NULL) {
    	print_query(word_node, filenames);      
    }
    else { // The word does not exist in the linked list.
	printf("indexfile %s: word not found\n", argv[optind]);
    }

    return 0;
}

/* Return a pointer to the node that contains the given word or 
 * NULL of if it doesn't exist. 
 */
Node *find_word_node(Node *head, char *word) {
    Node *nextNode = head;

    while (strcmp(nextNode->word, word) < 0 && nextNode->next != NULL) {
    	nextNode = nextNode->next;
    }

    if (strcmp(nextNode->word, word) == 0) {   
    	return nextNode;
    }
    else {
        return NULL;
    }
}

/* Write to standard output the list of files containing the word 
 * at the given node ordered by the number of occurrences of the 
 * word in the file.
 */
void print_query(Node *node, char **filenames) {
    int i;
    int indexes[MAXFILES];

    init_indexes(indexes, MAXFILES);
    bubble_sort(node->freq, indexes, MAXFILES);

    for (i = 0; i < MAXFILES; i++) {
    	if (node->freq[indexes[i]] == 0) {
		break;
        }
	else {
		printf("%d %s\n", node->freq[indexes[i]], filenames[indexes[i]]);
        } 
    }
}

/* Initialize an array of size n with the numbers from 0 to n-1. */
void init_indexes(int indexes[], int array_size) {
    int i;
    for (i = 0; i < array_size; i++) {
        indexes[i] = i;
    }
}

/* A modified version of bubble sort that does not modify the numbers array, but instead
 * it stores the indexes of the numbers if they were in sorted order.
 * 
 * For example, if numbers = {10, 2, 5, 12} then indexes will become {2, 0, 1, 3}.
 */
void bubble_sort(int numbers[], int indexes[], int array_size) {
    int i, j, temp;
 
    for (i = (array_size - 1); i > 0; i--) {
        for (j = 1; j <= i; j++) {
            if (numbers[indexes[j-1]] < numbers[indexes[j]]) {
                temp = indexes[j-1];
	        indexes[j-1] = indexes[j];
	        indexes[j] = temp;
            }
        }
    }
}
   
