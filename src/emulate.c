#include <stdio.h>
#include <stdlib.h>

#define MEMORY_SIZE 65536
#define BUFFER_SIZE 256

typedef struct {

    int addr[MEMORY_SIZE];

} memory;

int main(int argc, char** argv) {

    if (argc > 1) {

        FILE *f;
    
        f = fopen(argv[0], "rb");

        if (f == NULL) {
		    fprintf(stderr, "File not found.\n");
		    return -1;
	    }

        int buffer[BUFFER_SIZE];
        
        memset(buffer, 0, BUFFER_SIZE);

        memory *mem = calloc(sizeof(memory), 1);

        int *ptr = mem;

        while (fread(buffer, 1, BUFFER_SIZE, f)) {
            memcpy(ptr, buffer, BUFFER_SIZE);
            ptr += BUFFER_SIZE;
        }

        fclose(f);

        return 0;
    
    } else {
    
        return -1;
    
    }

}
