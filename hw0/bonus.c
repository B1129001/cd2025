#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 256

typedef struct Node {
    char character;
    int count;
    struct Node *next;
} Node;

Node *hashTable[TABLE_SIZE] = {NULL};

unsigned int hash(char ch) {
    return (unsigned int)ch % TABLE_SIZE;
}

void insertOrUpdate(Node **head, char ch) {
    unsigned int index = hash(ch);
    Node *current = hashTable[index];
    Node *prev = NULL;
    
    while (current) {
        if (current->character == ch) {
            current->count++;
            return;
        }
        prev = current;
        current = current->next;
    }
    
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (!newNode) {
        perror("Memory allocation failed");
        exit(1);
    }
    newNode->character = ch;
    newNode->count = 1;
    newNode->next = hashTable[index];
    hashTable[index] = newNode;
}

void freeList() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node *current = hashTable[i];
        while (current) {
            Node *temp = current;
            current = current->next;
            free(temp);
        }
        hashTable[i] = NULL;
    }
}

void printList() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node *current = hashTable[i];
        while (current) {
            if (current->character >= 32 && current->character <= 126)
                printf("%c: %d\n", current->character, current->count);
            current = current->next;
        }
    }
}

int main() {
    FILE *file = fopen(__FILE__, "r");
    if (!file) {
        perror("File opening failed");
        return 1;
    }
    
    int ch;
    while ((ch = fgetc(file)) != EOF) {
        if (ch >= 32 && ch <= 126)
            insertOrUpdate(NULL, (char)ch);
    }
    
    fclose(file);
    printList();
    freeList();
    
    return 0;
}
