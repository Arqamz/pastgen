#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utils/file_io.h"
#include "grammar/grammar.h"

static char* trim(char* str) {
    while(isspace(*str)) str++;
    if(*str == 0) return str;
    
    char* end = str + strlen(str) - 1;
    while(end > str && isspace(*end)) end--;
    *(end+1) = 0;
    return str;
}

static char** split_string(const char* input, const char* delimiter, size_t* count) {
    char* str = strdup(input);
    char* token;
    char** tokens = NULL;
    size_t tokens_count = 0;
    
    token = strtok(str, delimiter);
    while(token != NULL) {
        tokens = realloc(tokens, sizeof(char*) * (tokens_count + 1));
        tokens[tokens_count++] = strdup(trim(token));
        token = strtok(NULL, delimiter);
    }
    
    free(str);
    *count = tokens_count;
    return tokens;
}

CFG* read_grammar(const char* filename) {
    FILE* file = fopen(filename, "r");
    if(!file) {
        perror("Error opening file");
        return NULL;
    }

    CFG* cfg = calloc(1, sizeof(CFG));
    char line[256];
    
    while(fgets(line, sizeof(line), file)) {
        char* pos = strstr(line, "::=");
        if(!pos) continue;
        
        // Split non-terminal and productions
        *pos = '\0';
        char* nt_name = trim(line);
        char* productions_str = trim(pos + 3);

        // Split individual productions
        size_t prods_count;
        char** prods = split_string(productions_str, "|", &prods_count);
        
        // Create NonTerminal
        NonTerminal* nt = calloc(1, sizeof(NonTerminal));
        nt->name = strdup(nt_name);
        nt->productions = calloc(prods_count, sizeof(Production*));
        nt->count = prods_count;
        
        // Process each production
        for(size_t i = 0; i < prods_count; i++) {
            size_t symbols_count;
            char** symbols = split_string(prods[i], " ", &symbols_count);
            
            Production* prod = calloc(1, sizeof(Production));
            prod->symbols = symbols;
            prod->length = symbols_count;
            nt->productions[i] = prod;
            
            free(prods[i]);
        }
        
        // Add to CFG
        cfg->non_terminals = realloc(cfg->non_terminals, sizeof(NonTerminal*) * (cfg->count + 1));
        cfg->non_terminals[cfg->count++] = nt;
        
        free(prods);
    }
    
    fclose(file);
    return cfg;
}

void free_production(Production* prod) {
    if (!prod) return;
    for (size_t i = 0; i < prod->length; i++) {
        free(prod->symbols[i]);
    }
    free(prod->symbols);
    free(prod);
}

void free_non_terminal(NonTerminal* nt) {
    if (!nt) return;
    for (size_t i = 0; i < nt->count; i++) {
        free_production(nt->productions[i]);
    }
    free(nt->productions);
    free(nt->name);
    free(nt);
}

void free_cfg(CFG* cfg) {
    if (!cfg) return;
    for (size_t i = 0; i < cfg->count; i++) {
        free_non_terminal(cfg->non_terminals[i]);
    }
    free(cfg->non_terminals);
    free(cfg);
}