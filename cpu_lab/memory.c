#include "oslabs.h"
#include "stdio.h"
#include "limits.h"

struct MEMORY_BLOCK best_fit_allocate(int request_size, struct MEMORY_BLOCK memory_map[MAPMAX],int *map_cnt, int process_id){
    struct MEMORY_BLOCK NULLBLOCK;
    NULLBLOCK.start_address = 0;
    NULLBLOCK.end_address = 0;
    NULLBLOCK.segment_size = 0;
    NULLBLOCK.process_id= 0;
    int i;
    int closest_fit = INT_MAX;
    int best_block_position = -1;
    for(i = 0; i < (*map_cnt); i++){
        if(memory_map[i].process_id == 0){
            if (memory_map[i].segment_size == request_size) {
                memory_map[i].process_id = process_id;
                (*map_cnt)++;
                return memory_map[i];
            }
            if (memory_map[i].segment_size > request_size) {
                if ((memory_map[i].segment_size - request_size) < closest_fit){
                    closest_fit = (memory_map[i].segment_size - request_size);
                    best_block_position = i;
                }
            }
        }
    }
    if (best_block_position >= 0){
        struct MEMORY_BLOCK best_block = memory_map[best_block_position];
        int old_start = best_block.start_address;
        int old_end = best_block.end_address;
        int old_segment = best_block.segment_size;

        for (i = best_block_position; i < (*map_cnt) - 1; i++) {
            memory_map[i+1] = memory_map[i];
        }

        struct MEMORY_BLOCK NEWBLOCK;
        NEWBLOCK.start_address = old_start;
        NEWBLOCK.end_address = old_start + request_size - 1;
        NEWBLOCK.segment_size = request_size;
        NEWBLOCK.process_id = process_id;

        memory_map[best_block_position] = NEWBLOCK;
        (*map_cnt)++;

        memory_map[best_block_position+1].start_address = NEWBLOCK.end_address + 1;
        memory_map[best_block_position+1].end_address = old_end;
        memory_map[best_block_position+1].segment_size = old_segment - request_size;

        return NEWBLOCK;
    }
    return NULLBLOCK;
}

struct MEMORY_BLOCK first_fit_allocate(int request_size, struct MEMORY_BLOCK memory_map[MAPMAX],int *map_cnt, int process_id){
    struct MEMORY_BLOCK NULLBLOCK;
    NULLBLOCK.start_address = 0;
    NULLBLOCK.end_address = 0;
    NULLBLOCK.segment_size = 0;
    NULLBLOCK.process_id= 0;

    int i;
    int j;
    int closest_fit = INT_MAX;
    int best_block_position = -1;
    for(i = 0; i < (*map_cnt); i++){
        if(memory_map[i].process_id == 0){
            if (memory_map[i].segment_size == request_size) {
                memory_map[i].process_id = process_id;
                (*map_cnt)++;
                return memory_map[i];
            }
            if (memory_map[i].segment_size > request_size) {
                if ((memory_map[i].segment_size - request_size) < closest_fit){
                    struct MEMORY_BLOCK best_block = memory_map[i];
                    int old_start = best_block.start_address;
                    int old_end = best_block.end_address;
                    int old_segment = best_block.segment_size;

                    for (j = i; j < (*map_cnt) - 1; j++) {
                        memory_map[j+1] = memory_map[j];
                    }

                    struct MEMORY_BLOCK NEWBLOCK;
                    NEWBLOCK.start_address = old_start;
                    NEWBLOCK.end_address = old_start + request_size - 1;
                    NEWBLOCK.segment_size = request_size;
                    NEWBLOCK.process_id = process_id;

                    memory_map[i] = NEWBLOCK;
                    (*map_cnt)++;

                    memory_map[i+1].start_address = NEWBLOCK.end_address + 1;
                    memory_map[i+1].end_address = old_end;
                    memory_map[i+1].segment_size = old_segment - request_size;

                    return NEWBLOCK;                    
                }
            }
        }
    }
    return NULLBLOCK;
}

struct MEMORY_BLOCK worst_fit_allocate(int request_size, struct MEMORY_BLOCK memory_map[MAPMAX],int *map_cnt, int process_id){
    struct MEMORY_BLOCK NULLBLOCK;
    NULLBLOCK.start_address = 0;
    NULLBLOCK.end_address = 0;
    NULLBLOCK.segment_size = 0;
    NULLBLOCK.process_id= 0;
    int i;
    int largest_free = INT_MIN;
    int best_block_position = -1;
    for(i = 0; i < (*map_cnt); i++){
        if(memory_map[i].process_id == 0){
            if (memory_map[i].segment_size == request_size) {
                memory_map[i].process_id = process_id;
                (*map_cnt)++;
                return memory_map[i];
            }
            if (memory_map[i].segment_size > request_size) {
                if (memory_map[i].segment_size > largest_free){
                    largest_free = memory_map[i].segment_size;
                    best_block_position = i;
                }
            }
        }
    }
    if (best_block_position >= 0){
        struct MEMORY_BLOCK best_block = memory_map[best_block_position];
        int old_start = best_block.start_address;
        int old_end = best_block.end_address;
        int old_segment = best_block.segment_size;

        for (i = best_block_position; i < (*map_cnt) - 1; i++) {
            memory_map[i+1] = memory_map[i];
        }

        struct MEMORY_BLOCK NEWBLOCK;
        NEWBLOCK.start_address = old_start;
        NEWBLOCK.end_address = old_start + request_size - 1;
        NEWBLOCK.segment_size = request_size;
        NEWBLOCK.process_id = process_id;

        memory_map[best_block_position] = NEWBLOCK;
        (*map_cnt)++;

        memory_map[best_block_position+1].start_address = NEWBLOCK.end_address + 1;
        memory_map[best_block_position+1].end_address = old_end;
        memory_map[best_block_position+1].segment_size = old_segment - request_size;

        return NEWBLOCK;
    }
    return NULLBLOCK;
}

struct MEMORY_BLOCK next_fit_allocate(int request_size, struct MEMORY_BLOCK   memory_map[MAPMAX],int *map_cnt, int process_id, int last_address){
    struct MEMORY_BLOCK NULLBLOCK;
    NULLBLOCK.start_address = 0;
    NULLBLOCK.end_address = 0;
    NULLBLOCK.segment_size = 0;
    NULLBLOCK.process_id= 0;
    int i;
    int j;
    int best_block_position = -1;
    for(i = last_address; i < (*map_cnt); i++){
        if(memory_map[i].process_id == 0){
            if (memory_map[i].segment_size == request_size) {
                memory_map[i].process_id = process_id;
                (*map_cnt)++;
                return memory_map[i];
            }
            if (memory_map[i].segment_size > request_size) {
                struct MEMORY_BLOCK best_block = memory_map[i];
                int old_start = best_block.start_address;
                int old_end = best_block.end_address;
                int old_segment = best_block.segment_size;

                for (j = i; j < (*map_cnt) - 1; j++) {
                    memory_map[i+1] = memory_map[i];
                }

                struct MEMORY_BLOCK NEWBLOCK;
                NEWBLOCK.start_address = old_start;
                NEWBLOCK.end_address = old_start + request_size - 1;
                NEWBLOCK.segment_size = request_size;
                NEWBLOCK.process_id = process_id;

                memory_map[i] = NEWBLOCK;
                (*map_cnt)++;

                memory_map[i+1].start_address = NEWBLOCK.end_address + 1;
                memory_map[i+1].end_address = old_end;
                memory_map[i+1].segment_size = old_segment - request_size;

                return NEWBLOCK;
            }
        }
    }
    return NULLBLOCK;
}

void release_memory(struct MEMORY_BLOCK freed_block, struct MEMORY_BLOCK memory_map[MAPMAX],int *map_cnt){
    int i;
    int freed_block_position = -1;
    for(i = 0; i < (*map_cnt); i++){
        if (memory_map[i].process_id == freed_block.process_id){
            freed_block_position = i;
        }
    }

    if ((memory_map[freed_block_position-1].process_id == 0) && (memory_map[freed_block_position+1].process_id == 0)){
        memory_map[freed_block_position-1].end_address = memory_map[freed_block_position+1].end_address;
        memory_map[freed_block_position-1].segment_size = memory_map[freed_block_position-1].segment_size + memory_map[freed_block_position].segment_size + memory_map[freed_block_position+1].segment_size;

        for (i = freed_block_position; i < (*map_cnt) - 2; i++) {
            memory_map[i] = memory_map[i+2];
        }

        (*map_cnt)--;
        (*map_cnt)--;
    } else if (memory_map[freed_block_position-1].process_id == 0) {
        // add freed to -1 
        // remove freed
    } else if (memory_map[freed_block_position+1].process_id == 0) {
        // add +1 to freed
        // remove +1
    }
}