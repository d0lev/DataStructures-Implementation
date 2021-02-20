#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "TrieTree.h"

// a global variable that counter the number of the nodes in the trie
int num_of_Words = 0;

// this struct represent a node in a trie trie data structure
struct Node
{
    char data;
    int counter;
    int endWord;
    char *word;
    Node *chilldren[NUM_LETTERS];
};

//this method append single char into string (array of char) by using realloc method
char *append(char *str, char c)
{
    int len = strlen(str);
    char *str2 = (char *)(realloc(str, len + 2));
    if (str2 == NULL)
        exit(1);
    str2[len] = c;
    str2[len + 1] = '\0';
    return str2;
};

//this method create a new node in the tree and initialize all the data members of the struct
Node *newNode(char data)
{
    Node *node = (Node *)(calloc(1, sizeof(Node)));
    if (node != NULL)
    {
        for (int i = 0; i < NUM_LETTERS; i++)
            node->chilldren[i] = NULL;

        node->counter = 0;
        node->endWord = 0;
        node->data = data;
        return node;
    }
    exit(1);
};

// this method get the "path" as paramter of string and traverse the tree untill the path ends.
// then mark the end of the word by symbol (number 1) and also counter the occurrences of the word
void insertWord(Node *root, char *word, int length)
{
    Node *current = root;
    for (int i = 0; word[i] != '\0'; i++)
    {
        int index = (int)(word[i] - 'a');
        if (current->chilldren[index] == NULL)
        {
            current->chilldren[index] = newNode(word[i]);
        }
        current = current->chilldren[index];
    }
    current->endWord = 1;
    current->counter++;
    current->word = (char *)(realloc(current->word, length + 2));
    if (current->word == NULL)
        exit(1);
    strcpy(current->word, word);
    current->word[length + 1] = '\0';
    // after the word enters the tree , reset the path.
    word[0] = '\0';
    num_of_Words++;
};

// this method free all the allocations in the trie tree
void triefree(Node *current)
{
    for (int i = 0; i < NUM_LETTERS; i++)
    {
        if (current->chilldren[i] != NULL)
        {
            triefree(current->chilldren[i]);
        }
    }
    free(current);
}

// this method divides the "ASCII" table into three parts :
// if the method return 1: then the letter is an alpahbetic
// if the method return 2: then the letter is a non alphabetic character
// if the method return 0: the the letter is seperated words or end of file or end of line
int isValid(char letter)
{
    if ((letter >= 'a' && letter <= 'z') || (letter >= 'A' && letter <= 'Z'))
        return 1;

    else if (letter != '\n' && letter != ' ' && letter != '\t' && letter != EOF)
        return 2;

    return 0;
}

//this method print the words in lexicographic order by using recursion that ensures that the prefix word printed first.
// the method also free the alocated memory of the data member (node->word)
void lexicographic(Node *current)
{

    if (current == NULL)
    {
        return;
    }
    if (current->endWord == 1)
    {
        printf("%s %d\n", current->word, current->counter);
        free(current->word);
    }
    for (int i = 0; i < NUM_LETTERS; i++)
        lexicographic(current->chilldren[i]);
}

//this method print the words in unlexicographic order by using recursion that ensures that the prefix word printed after the whole word.
// the method also free the alocated memory of the data member (node->word)

void unlexicographic(Node *current)
{
    if (current == NULL)
    {
        return;
    }
    for (int i = NUM_LETTERS - 1; i >= 0; i--)
        unlexicographic(current->chilldren[i]);

    if (current->endWord == 1)
    {
        printf("%s %d\n", current->word, current->counter);
        free(current->word);
    }
}

//this method get a character from the standart input, and also ensure that the words that enters the trie are valid.
void insertWords(Node *root)
{
    char letter;
    char *word = (char *)calloc(1, sizeof(char));
    if (word == NULL)
        exit(1);
    int length = 0;
    Node *current = root;
    while ((letter = getc(stdin)) != EOF)
    {

        // get a character from the standart input until the character doesnt alphabetic
        while (isValid(letter) == 1)
        {
            word = append(word, tolower(letter));
            length++;
            letter = getc(stdin);
        }

        // ignore the characters that nor alphabetic and continue the while loop
        if (isValid(letter) == 2 || length == 0)
            continue;

        // mark the end of the word
        word[length] = '\0';
        insertWord(current, word, length);
        length = 0;
    }
    // this term check if the last word are enters the trie
    if (length > 0 && letter == EOF)
    {
        word[length] = '\0';
        insertWord(current, word, length);
        free(word);
    }
    else
    {
        free(word);
    }
}

int main(int argc, char *agrcv[])
{
    Node *root = newNode(0);
    if (argc == 1)
    {
        insertWords(root);
        lexicographic(root);
        triefree(root);
    }
    else if (*agrcv[1] == 'r')
    {
        insertWords(root);
        unlexicographic(root);
        triefree(root);
    }
}