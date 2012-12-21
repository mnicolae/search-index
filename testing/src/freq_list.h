#define MAXFILES 30
#define MAXWORD 40
#define MAXLINE 1024

struct node {
    char word[MAXWORD];
    int freq[MAXFILES];
    struct node *next;
};

typedef struct node Node; 

extern char *filenames[MAXFILES];

Node *create_node(char *word, int count, int filenum);
Node *add_word(Node *head, char **filenames, char *word, char *fname);
void print_list(FILE *fp, struct node *head);
char **init_filenames();
int get_filenum(char *fname, char **filenames);
void display_list(Node *head, char **filenames);
void write_list(char *namefile, char *listfile, Node *head, char **filenames);
void read_list(char *namefile, char *listfile, Node **head, char **filenames);
