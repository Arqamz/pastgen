#ifndef FILE_IO_H
#define FILE_IO_H

#include "grammar/grammar.h"

CFG* read_grammar(const char* filename);
void free_production(Production* prod);
void free_non_terminal(NonTerminal* nt);
void free_cfg(CFG* cfg);

#endif