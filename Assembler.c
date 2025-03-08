#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"
#include "parser.h"

// Mnemônicos
const Instruction instructions[] = {
    {"NOP", 0x00},
    {"STA", 0x10},
    {"LDA", 0x20},
    {"ADD", 0x30},
    {"OR",  0x40},
    {"AND", 0x50},
    {"NOT", 0x60},
    {"JMP", 0x80},
    {"JN",  0x90},
    {"JZ",  0xA0},
    {"HLT", 0xF0}
};

const int NUM_INSTRUCTIONS = sizeof(instructions) / sizeof(Instruction);

int initialize_resources(FILE** input_file, Lexer** lexer, Parser** parser, const char* input_filename) {
    *input_file = fopen(input_filename, "r");
    if (!*input_file) {
        fprintf(stderr, "Error: Cannot open input file '%s'\n", input_filename);
        return 0;
    }

    *lexer = lexer_init(*input_file);
    if (!*lexer) {
        fprintf(stderr, "Error: Failed to initialize lexer\n");
        fclose(*input_file);
        return 0;
    }

    *parser = parser_init(*lexer, instructions, NUM_INSTRUCTIONS);
    if (!*parser) {
        fprintf(stderr, "Error: Failed to initialize parser\n");
        lexer_destroy(*lexer);
        fclose(*input_file);
        return 0;
    }

    return 1;
}

void cleanup_resources(FILE* input_file, Lexer* lexer, Parser* parser) {
    if (parser) parser_destroy(parser);
    if (lexer) lexer_destroy(lexer);
    if (input_file) fclose(input_file);
}

int assemble_file(const char* input_filename, const char* output_filename) {
    FILE* input_file = NULL;
    Lexer* lexer = NULL;
    Parser* parser = NULL;

    if (!initialize_resources(&input_file, &lexer, &parser, input_filename)) {
        return 1;
    }

    if (!parser_parse(parser)) {
        fprintf(stderr, "Error: Parsing failed\n");
        cleanup_resources(input_file, lexer, parser);
        return 1;
    }

    if (!parser_write_output(parser, output_filename)) {
        fprintf(stderr, "Error: Output file creation failed\n");
        cleanup_resources(input_file, lexer, parser);
        return 1;
    }

    cleanup_resources(input_file, lexer, parser);
    return 0;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s input_file output_file\n", argv[0]);
        return 1;
    }

    printf("Assembling file: %s\n", argv[1]);
    if (assemble_file(argv[1], argv[2])) {
        fprintf(stderr, "Assembly failed\n");
        return 1;
    }

    printf("Assembly completed successfully!\n");
    return 0;
}