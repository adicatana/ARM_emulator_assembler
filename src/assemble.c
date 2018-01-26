#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "encode.h"

int main(int argc, char** argv) {

    if (argc > 2) {

        FILE *fin = fopen(argv[1], "r");

        if (fin == NULL) {
            fprintf(stderr, "File not found.\n");
            return -1;
        }

        char *lineptr = (char *)calloc(512, 1);

        while (fgets(lineptr, 511, fin)) {
            lineptr[strlen(lineptr) - 1] = '\0';
            execute(lineptr);
        }        

        FILE *fout = fopen(argv[2], "wb");
        return 0;

    } else {
        
        return -1;
    }

}
