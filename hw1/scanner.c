#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TOKEN_LEN 100

// Token types
typedef enum {
    TYPE_TOKEN, MAIN_TOKEN, IF_TOKEN, ELSE_TOKEN, WHILE_TOKEN,
    ID_TOKEN, LITERAL_TOKEN,
    ASSIGN_TOKEN, EQUAL_TOKEN, GREATER_TOKEN, LESS_TOKEN,
    GREATEREQUAL_TOKEN, LESSEQUAL_TOKEN,
    PLUS_TOKEN, MINUS_TOKEN,
    LEFTPAREN_TOKEN, REFTPAREN_TOKEN,
    LEFTBRACE_TOKEN, REFTBRACE_TOKEN,
    SEMICOLON_TOKEN,
    UNKNOWN_TOKEN
} TokenType;

const char* get_token_name(TokenType type) {
    switch(type) {
        case TYPE_TOKEN: return "TYPE_TOKEN";
        case MAIN_TOKEN: return "MAIN_TOKEN";
        case IF_TOKEN: return "IF_TOKEN";
        case ELSE_TOKEN: return "ELSE_TOKEN";
        case WHILE_TOKEN: return "WHILE_TOKEN";
        case ID_TOKEN: return "ID_TOKEN";
        case LITERAL_TOKEN: return "LITERAL_TOKEN";
        case ASSIGN_TOKEN: return "ASSIGN_TOKEN";
        case EQUAL_TOKEN: return "EQUAL_TOKEN";
        case GREATER_TOKEN: return "GREATER_TOKEN";
        case LESS_TOKEN: return "LESS_TOKEN";
        case GREATEREQUAL_TOKEN: return "GREATEREQUAL_TOKEN";
        case LESSEQUAL_TOKEN: return "LESSEQUAL_TOKEN";
        case PLUS_TOKEN: return "PLUS_TOKEN";
        case MINUS_TOKEN: return "MINUS_TOKEN";
        case LEFTPAREN_TOKEN: return "LEFTPAREN_TOKEN";
        case REFTPAREN_TOKEN: return "REFTPAREN_TOKEN";
        case LEFTBRACE_TOKEN: return "LEFTBRACE_TOKEN";
        case REFTBRACE_TOKEN: return "REFTBRACE_TOKEN";
        case SEMICOLON_TOKEN: return "SEMICOLON_TOKEN";
        default: return "UNKNOWN_TOKEN";
    }
}

TokenType check_keyword(const char *str) {
    if (strcmp(str, "int") == 0) return TYPE_TOKEN;
    if (strcmp(str, "main") == 0) return MAIN_TOKEN;
    if (strcmp(str, "if") == 0) return IF_TOKEN;
    if (strcmp(str, "else") == 0) return ELSE_TOKEN;
    if (strcmp(str, "while") == 0) return WHILE_TOKEN;
    return ID_TOKEN;
}

void scan(FILE *file) {
    int ch;
    while ((ch = fgetc(file)) != EOF) {
        if (isspace(ch)) continue;

        // Identifier or keyword
        if (isalpha(ch)) {
            char buffer[MAX_TOKEN_LEN] = {0};
            int i = 0;
            buffer[i++] = ch;

            while ((ch = fgetc(file)) != EOF && (isalnum(ch) || ch == '_')) {
                buffer[i++] = ch;
            }
            buffer[i] = '\0';
            if (ch != EOF) ungetc(ch, file);

            TokenType type = check_keyword(buffer);
            printf("%s: %s\n", buffer, get_token_name(type));
        }

        // Integer literal
        else if (isdigit(ch)) {
            char buffer[MAX_TOKEN_LEN] = {0};
            int i = 0;
            buffer[i++] = ch;
            while ((ch = fgetc(file)) != EOF && isdigit(ch)) {
                buffer[i++] = ch;
            }
            buffer[i] = '\0';
            if (ch != EOF) ungetc(ch, file);

            printf("%s: LITERAL_TOKEN\n", buffer);
        }

        // Operators and symbols
        else {
            int next = fgetc(file);
            switch (ch) {
                case '=':
                    if (next == '=') printf("==: EQUAL_TOKEN\n");
                    else {
                        if (next != EOF) ungetc(next, file);
                        printf("=: ASSIGN_TOKEN\n");
                    }
                    break;
                case '>':
                    if (next == '=') printf(">=: GREATEREQUAL_TOKEN\n");
                    else {
                        if (next != EOF) ungetc(next, file);
                        printf(">: GREATER_TOKEN\n");
                    }
                    break;
                case '<':
                    if (next == '=') printf("<=: LESSEQUAL_TOKEN\n");
                    else {
                        if (next != EOF) ungetc(next, file);
                        printf("<: LESS_TOKEN\n");
                    }
                    break;
                case '+': printf("+: PLUS_TOKEN\n"); if (next != EOF) ungetc(next, file); break;
                case '-': printf("-: MINUS_TOKEN\n"); if (next != EOF) ungetc(next, file); break;
                case '(': printf("(: LEFTPAREN_TOKEN\n"); if (next != EOF) ungetc(next, file); break;
                case ')': printf("): REFTPAREN_TOKEN\n"); if (next != EOF) ungetc(next, file); break;
                case '{': printf("{: LEFTBRACE_TOKEN\n"); if (next != EOF) ungetc(next, file); break;
                case '}': printf("}: REFTBRACE_TOKEN\n"); if (next != EOF) ungetc(next, file); break;
                case ';': printf(";: SEMICOLON_TOKEN\n"); if (next != EOF) ungetc(next, file); break;
                default:
                    printf("%c: UNKNOWN_TOKEN\n", ch);
                    if (next != EOF) ungetc(next, file);
                    break;
            }
        }
    }
}

int main() {
    FILE *file = fopen("main.c", "r");  // Replace with your actual file
    if (!file) {
        perror("File open failed");
        return 1;
    }

    scan(file);
    fclose(file);
    return 0;
}
