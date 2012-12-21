#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "freq_list.h"

#define DELIM " \f\n\r\t\v\b\\~!@#$%^&*()_-+=/*-+[];\',./{}:\"|\?"

char *convert_to_lower(char *word);

char word_lower[MAXWORD];

int main(int argc, char **argv) {
    Node *head = create_node("", 0, 0);
    char **filenames = init_filenames();
    char ch, line[MAXLINE], *token;
    char *indexfile = "index";
    char *namefile = "filenames";
    FILE *fp;

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

    while (optind < argc) {
	if ( (fp = fopen(argv[optind], "r")) == NULL) {
    		fprintf(stderr, "Cannot open file %s.\n", argv[optind]);
    	}
    	else {	
		while ( fgets(line, MAXLINE, fp) != NULL ) { 
			token = strtok(line, DELIM);
     			for(; token != NULL ;) {
				add_word(head, filenames, convert_to_lower(token), argv[optind]);
				token = strtok(NULL, DELIM);
			}
		}	
    		fclose(fp);
	}
    	optind++;
    }
    
    write_list(namefile, indexfile, head, filenames);
   
    return 0;
}

/* Return a pointer to a copy of the given string with all 
 * uppercase letters changed to lowercase letters.
 */
char *convert_to_lower(char *word) {
    int i;
    char *p = word_lower;
    
    strncpy(p, word, strlen(word));
    word_lower[strlen(word)] = '\0';

    for (i = 0; word_lower[i] != '\0'; i++) {
        if (isupper(word_lower[i])) { 
            word_lower[i] = tolower(word_lower[i]);
        }
    }
    return p;
}

