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
            return EXIT_FAILURE;
        }

        char *lineptr = calloc(BUFFER_SIZE_ASSEMBLER, 1);

        FILE *fout = fopen(argv[2], "wb");

        if (fout == NULL) {
            fclose(fin);
            fprintf(stderr, "File not found.\n");
            return EXIT_FAILURE;
        }

        while (fgets(lineptr, BUFFER_SIZE_ASSEMBLER, fin)) {
           
            lineptr[strlen(lineptr) - 1] = '\0';
            uint32_t instruction = assemble(lineptr);
            
            fwrite(&instruction, 1, 4, fout);
            log(("%x\n", instruction));
        }        

        fclose(fin);
        fclose(fout);

        return EXIT_SUCCESS;

    } else {
        
        perror("No enough arguments.\n");
        return EXIT_FAILURE;
    }

}
