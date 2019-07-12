#include "oslabs.h"
#include "stdio.h"
#include "limits.h"

struct PCB handle_process_arrival_pp(struct PCB ready_queue[QUEUEMAX], int *queue_cnt, struct PCB current_process, struct PCB new_process, int timestamp) {
    if (current_process.process_id == 0 &&
        current_process.arrival_timestamp == 0 && 
        current_process.total_bursttime == 0 &&
        current_process.execution_starttime == 0 &&
        current_process.execution_endtime == 0 &&
        current_process.remaining_bursttime == 0 && 
        current_process.process_priority == 0) {
        new_process.execution_starttime = timestamp;
        new_process.execution_endtime = timestamp + new_process.total_bursttime;
        new_process.remaining_bursttime = new_process.total_bursttime;
        return new_process;
    } else {
        if (new_process.process_priority > current_process.process_priority) {
            new_process.execution_starttime = 0;
            new_process.execution_endtime = 0;
            new_process.remaining_bursttime = new_process.total_bursttime;
            // (*queue_cnt)++;
            ready_queue[*queue_cnt] = new_process;
            return current_process;
        } else {
            new_process.execution_starttime = timestamp;
            new_process.execution_endtime = timestamp + new_process.total_bursttime;
            new_process.remaining_bursttime = new_process.total_bursttime;
            current_process.execution_endtime = 0;
            current_process.remaining_bursttime = current_process.total_bursttime;
            ready_queue[*queue_cnt] = current_process;
            (*queue_cnt)++;
            return new_process;
        }
    }
}

struct PCB handle_process_completion_pp(struct PCB ready_queue[QUEUEMAX], int *queue_cnt, int timestamp){ 
    struct PCB NULLPCB;
    NULLPCB.process_id = 0;
    NULLPCB.arrival_timestamp = 0;
    NULLPCB.total_bursttime = 0;
    NULLPCB.execution_starttime = 0;
    NULLPCB.execution_endtime = 0;
    NULLPCB.remaining_bursttime = 0; 
    NULLPCB.process_priority = 0;

    if ((*queue_cnt) == 0) {
        return NULLPCB;
    } else {
        int i;
        int biggest = INT_MAX;
        int highest_priority_position = 0;

        // printf("before-");
        // for (i = 0; i < (*queue_cnt); i++) {
        //     printf("%d-%d,", ready_queue[i].process_id, ready_queue[i].process_priority);
        // }

        for(i = 0; i < (*queue_cnt)-1; i++){
            if(ready_queue[i].process_priority < biggest){
                biggest = ready_queue[i].process_priority;
                highest_priority_position = i;
            }
        }

        // printf("highest-%d-", highest_priority_position);
        struct PCB winner = ready_queue[highest_priority_position];
        winner.execution_starttime = timestamp;
        winner.execution_endtime = timestamp + winner.remaining_bursttime;

        for (i = highest_priority_position; i < (*queue_cnt) - 1; i++) {
            ready_queue[i] = ready_queue[i+1];
        }
        (*queue_cnt)--;

        // printf("after-");
        // for (i = 0; i < (*queue_cnt); i++) {
        //     printf("%d-%d,", ready_queue[i].process_id, ready_queue[i].process_priority);
        // }

        // printf("q-%d", (*queue_cnt));

        return winner;
    }
}

struct PCB handle_process_arrival_srtp(struct PCB ready_queue[QUEUEMAX], int *queue_cnt, struct PCB current_process, struct PCB new_process, int time_stamp){
    if (current_process.process_id == 0 &&
        current_process.arrival_timestamp == 0 && 
        current_process.total_bursttime == 0 &&
        current_process.execution_starttime == 0 &&
        current_process.execution_endtime == 0 &&
        current_process.remaining_bursttime == 0 && 
        current_process.process_priority == 0) {
        new_process.execution_starttime = time_stamp;
        new_process.execution_endtime = time_stamp + new_process.total_bursttime;
        new_process.remaining_bursttime = new_process.total_bursttime;
        return new_process;
    } else {
        if (new_process.total_bursttime >= current_process.remaining_bursttime) {
            new_process.execution_starttime = 0;
            new_process.execution_endtime = 0;
            new_process.remaining_bursttime = new_process.total_bursttime;
            ready_queue[*queue_cnt] = new_process;
            (*queue_cnt)++;
            return current_process;
        } else {
            new_process.execution_starttime = time_stamp;
            new_process.execution_endtime = time_stamp + new_process.total_bursttime;
            new_process.remaining_bursttime = new_process.total_bursttime;

            current_process.execution_starttime = 0;
            current_process.execution_endtime = 0;
            current_process.remaining_bursttime = current_process.total_bursttime;

            ready_queue[*queue_cnt] = current_process;
            (*queue_cnt)++;
            return new_process;
        }
    }
}

struct PCB handle_process_completion_srtp(struct PCB ready_queue[QUEUEMAX], int *queue_cnt, int timestamp){
    struct PCB NULLPCB;
    NULLPCB.process_id = 0;
    NULLPCB.arrival_timestamp = 0;
    NULLPCB.total_bursttime = 0;
    NULLPCB.execution_starttime = 0;
    NULLPCB.execution_endtime = 0;
    NULLPCB.remaining_bursttime = 0; 
    NULLPCB.process_priority = 0;

    if ((*queue_cnt) == 0) {
        return NULLPCB;
    } else {
        int i;
        int smallest = INT_MAX;
        int smallest_burst_time = 0;

        for(i = 0; i < (*queue_cnt)-1; i++){
            if(ready_queue[i].remaining_bursttime < smallest){
                smallest = ready_queue[i].remaining_bursttime;
                smallest_burst_time = i;
            }
        }

        struct PCB winner = ready_queue[smallest_burst_time];
        winner.execution_starttime = timestamp;
        winner.execution_endtime = timestamp + winner.remaining_bursttime;

        for (i = smallest_burst_time; i < (*queue_cnt) - 1; i++) {
            ready_queue[i] = ready_queue[i+1];
        }
        (*queue_cnt)--;

        return winner;
    }
}

struct PCB handle_process_arrival_rr(struct PCB ready_queue[QUEUEMAX], int *queue_cnt, struct PCB current_process, struct PCB new_process, int timestamp, int time_quantum){
    if (current_process.process_id == 0 &&
        current_process.arrival_timestamp == 0 && 
        current_process.total_bursttime == 0 &&
        current_process.execution_starttime == 0 &&
        current_process.execution_endtime == 0 &&
        current_process.remaining_bursttime == 0 && 
        current_process.process_priority == 0) {
        new_process.execution_starttime = timestamp;
        int smallest = (time_quantum < new_process.total_bursttime) ? time_quantum : new_process.total_bursttime;
        new_process.execution_endtime = timestamp + smallest;
        new_process.remaining_bursttime = new_process.total_bursttime;
        return new_process;
    } else {
        new_process.execution_starttime = 0;
        new_process.execution_endtime = 0;
        new_process.remaining_bursttime = new_process.total_bursttime;

        ready_queue[*queue_cnt] = new_process;
        (*queue_cnt)++;
        return current_process;
    }
}

struct PCB handle_process_completion_rr(struct PCB ready_queue[QUEUEMAX], int *queue_cnt, int time_stamp, int time_quantum){
    struct PCB NULLPCB;
    NULLPCB.process_id = 0;
    NULLPCB.arrival_timestamp = 0;
    NULLPCB.total_bursttime = 0;
    NULLPCB.execution_starttime = 0;
    NULLPCB.execution_endtime = 0;
    NULLPCB.remaining_bursttime = 0; 
    NULLPCB.process_priority = 0;

    if ((*queue_cnt) == 0) {
        return NULLPCB;
    } else {
        int i;
        int earliest = INT_MAX;
        int earliest_arrival_time = 0;

        for(i = 0; i < (*queue_cnt)-1; i++){
            if(ready_queue[i].arrival_timestamp < earliest){
                earliest = ready_queue[i].arrival_timestamp;
                earliest_arrival_time = i;
            }
        }

        struct PCB winner = ready_queue[earliest_arrival_time];
        winner.execution_starttime = time_stamp;
        int smallest = (time_quantum < winner.total_bursttime) ? time_quantum : winner.total_bursttime;
        winner.execution_endtime = time_stamp + smallest;

        for (i = earliest_arrival_time; i < (*queue_cnt) - 1; i++) {
            ready_queue[i] = ready_queue[i+1];
        }
        (*queue_cnt)--;

        return winner;
    }
}