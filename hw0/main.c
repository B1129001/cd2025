#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char character;
    int count;
    struct Node *next;
} Node;

void insertOrUpdate(Node **head, char ch) {
    Node *current = *head;
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
    newNode->next = NULL;

    if (prev)
        prev->next = newNode;
    else
        *head = newNode;
}

void freeList(Node *head) {
    Node *temp;
    while (head) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

void printList(Node *head) {
    while (head) {
        if (head->character >= 32 && head->character <= 126)
            printf("%c: %d\n", head->character, head->count);
        head = head->next;
    }
}

int main() {
    FILE *file = fopen(__FILE__, "r");
    if (!file) {
        perror("File opening failed");
        return 1;
    }

    Node *head = NULL;
    int ch;

    while ((ch = fgetc(file)) != EOF) {
        if (ch >= 32 && ch <= 126)
            insertOrUpdate(&head, (char)ch);
    }

    fclose(file);
    printList(head);
    freeList(head);

    return 0;
}

