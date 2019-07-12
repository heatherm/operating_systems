#include "oslabs.h"
#include "stdio.h"
#include "limits.h"


// [IV:false,FN:-1,ATS:-1,LATS:-1,RC:-1]
// [IV:false,FN:-1,ATS:-1,LATS:-1,RC:-1]
// [IV:true,FN:10,ATS:3,LATS:3,RC:1]
// [IV:false,FN:-1,ATS:-1,LATS:-1,RC:-1]
// [IV:false,FN:-1,ATS:-1,LATS:-1,RC:-1]
// [IV:true,FN:20,ATS:2,LATS:4,RC:2]
// [IV:false,FN:-1,ATS:-1,LATS:-1,RC:-1]
// [IV:true,FN:30,ATS:1,LATS:1,RC:1]


// [IV:true,FN:30,ATS:1,LATS:1,RC:1]
// [IV:false,FN:-1,ATS:-1,LATS:-1,RC:-1]
// [IV:true,FN:10,ATS:3,LATS:3,RC:1]
// [IV:false,FN:-1,ATS:-1,LATS:-1,RC:-1]
// [IV:false,FN:-1,ATS:-1,LATS:-1,RC:-1]
// [IV:true,FN:20,ATS:2,LATS:4,RC:2]
// [IV:false,FN:-1,ATS:-1,LATS:-1,RC:-1]
// [IV:false,FN:-1,ATS:-1,LATS:-1,RC:-1]

int process_page_access_fifo(struct PTE page_table[TABLEMAX],int *table_cnt, int page_number, int frame_pool[POOLMAX],int *frame_cnt, int current_timestamp){
    if (page_table[page_number].is_valid == 1){
        page_table[page_number].last_access_timestamp = current_timestamp;
        page_table[page_number].reference_count = 000;
       return page_table[page_number].frame_number;
    } else if ((*frame_cnt) > 0) {
        int free_frame_num = frame_pool[*frame_cnt];
    } else {
        int i;
        int smallest_arrival = INT_MAX;
        int smallest_position = -1;
        for(i = 0; i < (*table_cnt); i++){
            if (page_table[i].is_valid == 1){
                if (page_table[i].arrival_timestamp < smallest_arrival) {
                    smallest_arrival = page_table[i].arrival_timestamp;
                    smallest_position = i;
                }
            }
        }

        int old_frame = page_table[smallest_position].frame_number;
        page_table[smallest_position].arrival_timestamp = 0;
        page_table[smallest_position].last_access_timestamp = 0;
        page_table[smallest_position].reference_count = 0;
        page_table[0].frame_number = old_frame;
        page_table[0].is_valid = 1;
        page_table[0].arrival_timestamp = current_timestamp;
        page_table[0].last_access_timestamp = current_timestamp;
        page_table[0].reference_count = 1;
        page_table[smallest_position].is_valid = 0;
        return page_table[smallest_position].frame_number;
    } 
    return (*frame_cnt);
}

int count_page_faults_fifo(struct PTE page_table[TABLEMAX],int table_cnt, int refrence_string[REFERENCEMAX],int reference_cnt,int frame_pool[POOLMAX],int frame_cnt){
    int page_faults = 0;
    int i;

    int timestamp = 0;
    for(i = 0; i < (table_cnt); i++){
        timestamp++;
        if (page_table[i].is_valid == 1){
// TODO

        } else if ((frame_cnt) > 0) {
            int free_frame_num = frame_pool[frame_cnt];
// TODO
            page_faults++;

        } else {
            int i;
            int smallest_arrival = INT_MAX;
            int smallest_position = -1;
            for(i = 0; i < (table_cnt); i++){
                if (page_table[i].is_valid == 1){
                    if (page_table[i].arrival_timestamp < smallest_arrival) {
                        smallest_arrival = page_table[i].arrival_timestamp;
                        smallest_position = i;
                    }
                }
            }

            int old_frame = page_table[smallest_position].frame_number;
            page_table[smallest_position].arrival_timestamp = 0;
            page_table[smallest_position].last_access_timestamp = 0;
            page_table[smallest_position].reference_count = 0;
            page_table[smallest_position].is_valid = 0;
            page_faults++;

       }
    }


    return page_faults;
}

int process_page_access_lru(struct PTE page_table[TABLEMAX],int *table_cnt, int page_number, int frame_pool[POOLMAX],int *frame_cnt, int current_timestamp){
    if (page_table[page_number].is_valid == 1){
        page_table[page_number].last_access_timestamp = current_timestamp;
        page_table[page_number].reference_count = 000;
       return page_table[page_number].frame_number;
    } else if ((*frame_cnt) > 0) {
        int free_frame_num = frame_pool[*frame_cnt];
        return page_table[page_number].frame_number;
    } else {
        int i;
        int smallest_arrival = INT_MAX;
        int smallest_position = -1;
        for(i = 0; i < (*table_cnt); i++){
            if (page_table[i].is_valid == 1){
                if (page_table[i].arrival_timestamp < smallest_arrival) {
                    smallest_arrival = page_table[i].arrival_timestamp;
                    smallest_position = i;
                }
            }
        }

        int old_frame = page_table[smallest_position].frame_number;
        page_table[smallest_position].arrival_timestamp = 0;
        page_table[smallest_position].last_access_timestamp = 0;
        page_table[smallest_position].reference_count = 0;
        page_table[0].frame_number = old_frame;
        page_table[0].is_valid = 1;
        page_table[0].arrival_timestamp = current_timestamp;
        page_table[0].last_access_timestamp = current_timestamp;
        page_table[0].reference_count = 1;
        page_table[smallest_position].is_valid = 0;
        return page_table[smallest_position].frame_number;
    }
    return (*frame_cnt);
}

int count_page_faults_lru(struct PTE page_table[TABLEMAX],int table_cnt, int refrence_string[REFERENCEMAX],int reference_cnt,int frame_pool[POOLMAX],int frame_cnt){
    int page_faults = 1;
    int i;

    int timestamp = 0;
    for(i = 0; i < (table_cnt); i++){
        timestamp++;
        if (page_table[i].is_valid == 1){
            page_table[i].last_access_timestamp = 0;
            page_table[i].reference_count = 0;
            continue;
        } else if ((frame_cnt) > 0) {
            int free_frame_num = frame_pool[frame_cnt];
// TODO
            page_faults++;

        } else {
            int i;
            int smallest_arrival = INT_MAX;
            int smallest_position = -1;
            for(i = 0; i < (table_cnt); i++){
                if (page_table[i].is_valid == 1){
                    if (page_table[i].arrival_timestamp < smallest_arrival) {
                        smallest_arrival = page_table[i].arrival_timestamp;
                        smallest_position = i;
                    }
                }
            }

            int old_frame = page_table[smallest_position].frame_number;
            page_table[smallest_position].arrival_timestamp = 0;
            page_table[smallest_position].last_access_timestamp = 0;
            page_table[smallest_position].reference_count = 0;
            page_table[smallest_position].is_valid = 0;
            page_faults++;

       }
    }


    return page_faults;
}

int process_page_access_lfu(struct PTE page_table[TABLEMAX],int *table_cnt, int page_number, int frame_pool[POOLMAX],int *frame_cnt, int current_timestamp){
    if (page_table[page_number].is_valid == 1){
        page_table[page_number].last_access_timestamp = current_timestamp;
        page_table[page_number].reference_count = 000;
       return page_table[page_number].frame_number;
    } else if ((*frame_cnt) > 0) {
        int free_frame_num = frame_pool[*frame_cnt];
        return page_table[page_number].frame_number;
    } else {
        int i;
        int smallest_arrival = INT_MAX;
        int smallest_position = -1;
        for(i = 0; i < (*table_cnt); i++){
            if (page_table[i].is_valid == 1){
                if (page_table[i].arrival_timestamp < smallest_arrival) {
                    smallest_arrival = page_table[i].arrival_timestamp;
                    smallest_position = i;
                }
            }
        }

        int old_frame = page_table[smallest_position].frame_number;
        page_table[smallest_position].arrival_timestamp = 0;
        page_table[smallest_position].last_access_timestamp = 0;
        page_table[smallest_position].reference_count = 0;
        page_table[0].frame_number = old_frame;
        page_table[0].is_valid = 1;
        page_table[0].arrival_timestamp = current_timestamp;
        page_table[0].last_access_timestamp = current_timestamp;
        page_table[0].reference_count = 1;
        page_table[smallest_position].is_valid = 0;
        return page_table[smallest_position].frame_number;
    }
}

int count_page_faults_lfu(struct PTE page_table[TABLEMAX],int table_cnt, int refrence_string[REFERENCEMAX],int reference_cnt,int frame_pool[POOLMAX],int frame_cnt){
    int page_faults = 2;
    int i;

    int timestamp = 0;
    for(i = 0; i < (table_cnt); i++){
        timestamp++;
        if (page_table[i].is_valid == 1){
            page_table[i].last_access_timestamp = 0;
            page_table[i].reference_count = 0;
            continue;
        } else if ((frame_cnt) > 0) {
            int free_frame_num = frame_pool[frame_cnt];
// TODO
            page_faults++;

        } else {
            int i;
            int smallest_arrival = INT_MAX;
            int smallest_position = -1;
            for(i = 0; i < (table_cnt); i++){
                if (page_table[i].is_valid == 1){
                    if (page_table[i].arrival_timestamp < smallest_arrival) {
                        smallest_arrival = page_table[i].arrival_timestamp;
                        smallest_position = i;
                    }
                }
            }

            int old_frame = page_table[smallest_position].frame_number;
            page_table[smallest_position].arrival_timestamp = 0;
            page_table[smallest_position].last_access_timestamp = 0;
            page_table[smallest_position].reference_count = 0;
            page_table[smallest_position].is_valid = 0;
            page_faults++;

       }
    }


    return page_faults;
}