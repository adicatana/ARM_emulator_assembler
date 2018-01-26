#include "input.h"
#include "types.h"
#include "pipeline_cycle.h"
#include "utils.h"

int main(int argc, char** argv) {

    if (argc > 1) {

        memory_t *memory = read_from_binary(argv[1]);

        if (memory == NULL) {
            perror("Erorr reading from binary\n");
            exit(EXIT_FAILURE);
        }

        memset(registers, INIT_REG_VALUE, NO_OF_REGISTERS);

        uint32_t current_instruction, to_decode;
        instruction to_execute;

        clear_cycle(&current_instruction, &to_decode, &to_execute);

        do {
            
            log(("%s%x\n", "Starting the cycle... at PC: ", registers[PC_REG]));        
            
            log(("%d\n", registers[PC_REG]));

            log(("%s\n", "Fetching..."));           
            current_instruction = fetch(memory, registers[PC_REG]);
            log(("%x fetched\n", current_instruction));

            log(("%s\n", "Decoding..."));
            instruction decoded = decode(to_decode);
            log(("%x decoded as a %s instruction\n", decoded.code, get_type(decoded.type)));            

            log(("%s %x\n", "Executing...", to_execute.code));          
            execute(to_execute, memory, registers);

            // if it is a successful branch operation, clear the instructions
            if (to_execute.type == BRANCH && cond_check(to_execute.code >> 28, *(registers + FLAG_REG))) {
                clear_cycle(&current_instruction, &to_decode, &to_execute);             
            } else {            
                to_execute = decoded;
                to_decode = current_instruction;
                registers[PC_REG] += 4;
            }

            log(("%s\n\n", "Cycle ended."));
            
        } while (to_execute.type != HALT);

        print_state(memory, registers);

        free(memory);

        return 0;
    
    } else {

        perror("No input file given.\n");   
        return -1;
    
    }

}
