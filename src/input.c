#include "input.h"

memory_t *read_from_binary(const char * const name) {

    FILE *f = fopen(name, "rb");

    if (f == NULL) {
        fprintf(stderr, "File not found.\n");
	    return NULL;
	}

    int buffer[BUFFER_SIZE];
        
    memset(buffer, 0, BUFFER_SIZE);

    memory_t *mem = (memory_t *)calloc(sizeof(memory_t), 1);

	if (mem == NULL) {
		fprintf(stderr, "Fatal: failed to allocate %zu bytes.\n", sizeof(memory_t));
	}

    memory_t *ptr = mem;

    while (fread(buffer, 1, BUFFER_SIZE, f) > 0) {

		if (ferror(f)){
			perror("Error reading from stream.\n");
		}
		
        memcpy(ptr, buffer, BUFFER_SIZE);
        ptr += BUFFER_SIZE;
    }

    fclose(f);
	
	return mem;

}
