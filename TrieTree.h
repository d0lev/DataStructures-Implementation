#define NUM_LETTERS 26
typedef struct Node Node;
char *append(char *str, char c);
Node *newNode(char data);
void insertWord(Node *root, char *word, int length);
void triefree(Node *current);
int isValid(char letter);
void lexicographic(Node *current);
void unlexicographic(Node *current);
void insertWords(Node *root);