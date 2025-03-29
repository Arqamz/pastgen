// src/main.c
#include <stdio.h>
#include "utils/file_io.h"

int main(int argc, char* argv[]) {
    const char* filename;
    if(argc > 1) {
        filename = argv[1];
    } else {
        // Use default file
        filename = "input/example1.cfg";
    }

    CFG* cfg = read_grammar(filename);
    if(!cfg) {
        fprintf(stderr, "Error reading grammar\n");
        return 1;
    }

    print_grammar(cfg);
    free_cfg(cfg);
    return 0;
}