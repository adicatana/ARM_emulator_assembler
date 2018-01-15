#include "input.h"
#include "types.h"

int main(int argc, char** argv) {

    if (argc > 1) {

		memory *mem = read_from_binary(argv[1]);

		int count = 0;
		    
		while (mem->addr[count]) {
		    printf("%x\n", mem->addr[count++]);
	    }

        return 0;
    
    } else {
    
        return -1;
    
    }

}
