#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// **************************************
// **********   BLOCK_HEADER   **********
// **************************************
// block_size = header_size + payload_size + padding 
// block_size must be divisible by 16
// alloc_bit = 1 if allocated and 0 if free
// size_alloc = block_size + alloc_bit
// payload = size requested for payload by the user of an allocated block or available size of a free block (used for performance analysis)
// performance analysis is provided in Mem_Dump function
typedef struct{
    int size_alloc; 
    int payload;
} BLOCK_HEADER;

BLOCK_HEADER *first_header;

// return a pointer to the payload
// if a large enough free block isn't available, return NULL

void *Mem_Alloc(int size) {

    BLOCK_HEADER *current = first_header;
    int alloc, block_size, padding;

    while (1) { // find a free block that's big enough

        alloc = current->size_alloc & 1;
        block_size = current->size_alloc & 0xFFFFFFFE;

        // return NULL if we didn't find a block
        if (current->size_alloc == 1 && current->payload == 0) return NULL; // case 0: the end of linked list, cannot allocate, return NULL


        if (alloc == 0) { // found empty block

            if (current->payload >= size) {

                int round_up_block_size = 8 + size;
                while(round_up_block_size % 16)
                    round_up_block_size++;
                padding = block_size - round_up_block_size;


                // allocate the block
                current->payload = size;
                current->size_alloc = round_up_block_size;
                current->size_alloc = current->size_alloc | 0x1; // set alloc bit to 1


                // split if necessary (if padding size is greater than or equal to 16 split the block)
                if(padding >= 16){ // split a new block
                    BLOCK_HEADER * next = (BLOCK_HEADER *) ((unsigned long) current + round_up_block_size);
                    next->size_alloc = padding;
                    next->payload = padding - 8;
                }


                return (void *) ((unsigned long) current + 8); // return address of payload

            }
            // case 3: not big enough

        }
        // case 4: alloc = 1, occupied block


        // case 3 and 4 will search the next block
        current = (BLOCK_HEADER *) ((unsigned long) current + block_size);

    }
}

// return 0 on success
// return -1 if the input ptr was invalid

int Mem_Free(void *ptr) {



    BLOCK_HEADER *current = first_header;
    BLOCK_HEADER *prev = NULL;

    int alloc, block_size;

    while (1) {    // traverse the list and check all pointers to find the correct block

        alloc = current->size_alloc & 1;
        block_size = current->size_alloc & 0xFFFFFFFE;

        // if you reach the end of the list without finding it return -1
        if (current->size_alloc == 1 && current->payload == 0) return -1; // case 0: the end of linked list, didn't found ptr, return -1


        if (alloc == 1 && (unsigned long)ptr == (unsigned long)current + 8) { // block found

            // free the block
            current->size_alloc = current->size_alloc & 0xFFFFFFFE; // set alloc bit to 0

            // coalesce adjacent free blocks

            BLOCK_HEADER * next = (BLOCK_HEADER *) ((unsigned long) current + block_size);

            if (next->size_alloc == 1) next = NULL; // exclude end block

            int left_is_empty = (prev != NULL && (prev->size_alloc & 1) == 0);
            int right_is_empty = (next != NULL && (next->size_alloc & 1) == 0);
            if(left_is_empty && right_is_empty){ // coalesce 2 block
                prev->size_alloc += current->size_alloc + next->size_alloc;
                prev->payload += current->size_alloc + next->size_alloc;
            }
            if(left_is_empty && !right_is_empty){ // coalesce left block
                prev->size_alloc += current->size_alloc;
                prev->payload += current->size_alloc;
            }
            if(!left_is_empty && right_is_empty){ // coalesce right block
                current->size_alloc += next->size_alloc;
                current->payload += next->size_alloc;
            }
            return 0; // case 1: success
        }

        // search the next block
        prev = current;
        current = (BLOCK_HEADER *) ((unsigned long) current + block_size);
    }

}
