#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lexer.h"

Lexer* lexer_init(FILE* input) {
    Lexer* lexer = (Lexer*)malloc(sizeof(Lexer));
    if (!lexer) return NULL;
    
    lexer->input_file = input;
    lexer->line[0] = '\0';
    lexer->line_ptr = lexer->line;
    lexer->line_number = 0;
    lexer->in_comment = 0;
    
    return lexer;
}

void lexer_destroy(Lexer* lexer) {
    if (lexer) {
        free(lexer);
    }
}

int is_delimiter(char c) {
    return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == ';');
}

int is_comment(const char* line) {
    while (*line && (*line == ' ' || *line == '\t')) {
        line++;
    }
    return (*line == ';');
}

char* read_token(Lexer* lexer) {
    char* token_start = lexer->line_ptr;
    
    while (*(lexer->line_ptr) && !is_delimiter(*(lexer->line_ptr))) {
        (lexer->line_ptr)++;
    }
    
    if (*(lexer->line_ptr)) {
        *(lexer->line_ptr) = '\0'; // Termina o token
        (lexer->line_ptr)++; // Avança para o próximo caractere
    }
    
    return token_start;
}

TokenType determine_token_type(const char* token_start) {
    if (token_start[0] == '.') {
        return TOKEN_DIRECTIVE;
    } else if (isdigit(token_start[0]) || 
              (token_start[0] == '0' && (token_start[1] == 'x' || token_start[1] == 'X'))) {
        return TOKEN_NUMBER;
    } else {
        return TOKEN_MNEMONIC;
    }
}

Token* lexer_next_token(Lexer* lexer) {
    Token* token = (Token*)malloc(sizeof(Token));
    if (!token) return NULL;
    
    token->type = TOKEN_NONE;
    token->value = NULL;
    token->line_number = lexer->line_number;

    if (*(lexer->line_ptr) == '\0') {
        if (fgets(lexer->line, MAX_LINE_LENGTH, lexer->input_file) == NULL) {
            token->type = TOKEN_EOF;
            return token;
        }
        
        lexer->line_ptr = lexer->line;
        lexer->line_number++;

        if (is_comment(lexer->line)) {
            free(token);
            return lexer_next_token(lexer);
        }
        
        token->line_number = lexer->line_number;
    }

    while (*(lexer->line_ptr) && is_delimiter(*(lexer->line_ptr))) {
        if (*(lexer->line_ptr) == ';') {
            *(lexer->line_ptr) = '\0';
            token->type = TOKEN_EOL;
            return token;
        }
        (lexer->line_ptr)++;
    }

    if (*(lexer->line_ptr) == '\0') {
        token->type = TOKEN_EOL;
        return token;
    }

    char* token_start = read_token(lexer);
    token->type = determine_token_type(token_start);
    token->value = strdup(token_start);
    
    return token;
}

void token_destroy(Token* token) {
    if (token) {
        if (token->value) {
            free(token->value);
        }
        free(token);
    }
}

int parse_number(const char* str) {
    if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X')) {
        return strtol(str + 2, NULL, 16); // Converte hexadecimal para inteiro
    }
    return atoi(str); // Converte decimal para inteiro
}