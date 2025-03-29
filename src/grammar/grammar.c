#include <stdio.h>
#include <stddef.h>
#include "grammar/grammar.h"

void print_grammar(const CFG* cfg) {
    if (!cfg) {
        fprintf(stderr, "Error: Cannot print NULL grammar.\n");
        return;
    }

    for (size_t i = 0; i < cfg->count; ++i) {
        NonTerminal* nt = cfg->non_terminals[i];
        if (!nt || !nt->name) {
            fprintf(stderr, "Warning: Skipping invalid non-terminal at index %zu.\n", i);
            continue;
        }

        printf("%s -> ", nt->name);

        for (size_t j = 0; j < nt->count; ++j) {
            Production* prod = nt->productions[j];
            if (!prod) {
                fprintf(stderr, "Warning: Skipping invalid production for non-terminal %s at index %zu.\n", nt->name, j);
                continue;
            }

            if (prod->length == 0) {
                printf("ε");
            } else {
                for (size_t k = 0; k < prod->length; ++k) {
                    if (!prod->symbols[k]) {
                        fprintf(stderr, "Warning: Skipping NULL symbol in production for %s at index %zu, symbol %zu.\n", nt->name, j, k);
                        printf("<?>"); // Missing symbol
                    } else {
                        printf("%s", prod->symbols[k]);
                    }
                    if (k < prod->length - 1) {
                        printf(" "); // Space between symbols
                    }
                }
            }


            if (j < nt->count - 1) {
                printf(" | "); // Separator between productions
            }
        }
        printf("\n"); // Newline after all productions for a non-terminal
    }
}