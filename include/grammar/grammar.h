#ifndef GRAMMAR_H
#define GRAMMAR_H

#include <stddef.h>

typedef struct {
    char** symbols;                 // Array of symbols in the production
    size_t length;                  // Number of symbols in the production
} Production;

typedef struct {
    char* name;                     // Non-terminal name
    Production** productions;       // Array of productions
    size_t count;                   // Number of productions
} NonTerminal;

typedef struct {
    NonTerminal** non_terminals;    // Array of non-terminals
    size_t count;                   // Number of non-terminals
} CFG;

void print_grammar(const CFG* cfg);

#endif