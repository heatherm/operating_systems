#include "oslabs.h"
#include "stdio.h"
#include "limits.h"
#include "stdlib.h"

struct RCB handle_request_arrival_fcfs(struct RCB request_queue[QUEUEMAX], int *queue_cnt, struct RCB current_request, struct RCB new_request, int timestamp){
  if (
      current_request.request_id == 0 &&
      current_request.arrival_timestamp == 0 &&
      current_request.cylinder == 0 &&
      current_request.address == 0 &&
      current_request.process_id == 0
  ) {
    return new_request;
  } else {
    request_queue[*queue_cnt] = new_request;
    (*queue_cnt)++;
    return current_request;
  }
}

struct RCB handle_request_completion_fcfs(struct RCB request_queue[QUEUEMAX],int *queue_cnt){
    if (*queue_cnt == 0){
        struct RCB NULLRCB;
        NULLRCB.request_id = 0;
        NULLRCB.arrival_timestamp = 0;
        NULLRCB.cylinder = 0;
        NULLRCB.address = 0;
        NULLRCB.process_id = 0;
        return NULLRCB;
    } else {
        int i;
        int smallest = INT_MAX;
        int smallest_arrival_time = 0;

        for(i = 0; i < (*queue_cnt)-1; i++){
            if(request_queue[i].arrival_timestamp < smallest){
                smallest = request_queue[i].arrival_timestamp;
                smallest_arrival_time = i;
            }
        }

        struct RCB found = request_queue[smallest_arrival_time];


        for (i = smallest_arrival_time; i < (*queue_cnt) - 1; i++) {
            request_queue[i] = request_queue[i+1];
        }
        (*queue_cnt)--;

        return found;
    }
}

struct RCB handle_request_arrival_sstf(struct RCB request_queue[QUEUEMAX],int *queue_cnt, struct RCB current_request, struct RCB new_request, int timestamp){
      if (
      current_request.request_id == 0 &&
      current_request.arrival_timestamp == 0 &&
      current_request.cylinder == 0 &&
      current_request.address == 0 &&
      current_request.process_id == 0
  ) {
    return new_request;
  } else {
    request_queue[*queue_cnt] = new_request;
    (*queue_cnt)++;
    return current_request;
  }
}

struct RCB handle_request_completion_sstf(struct RCB request_queue[QUEUEMAX],int *queue_cnt,int current_cylinder){
    if (*queue_cnt == 0){
        struct RCB NULLRCB;
        NULLRCB.request_id = 0;
        NULLRCB.arrival_timestamp = 0;
        NULLRCB.cylinder = 0;
        NULLRCB.address = 0;
        NULLRCB.process_id = 0;
        return NULLRCB;
    } else {
        int i;
        int closest = 0;
        int distance_from_cylinder = INT_MAX;

        for(i = 0; i < (*queue_cnt)-1; i++){
            int current_distance = abs(request_queue[i].cylinder - current_cylinder);
            if(current_distance < distance_from_cylinder){
                closest = i;
            } else if (current_distance == distance_from_cylinder){
                if (request_queue[i].arrival_timestamp < request_queue[closest].arrival_timestamp) {
                    closest = i;
                }
            }
        }

        struct RCB found = request_queue[closest];

        for (i = closest; i < (*queue_cnt) - 1; i++) {
            request_queue[i] = request_queue[i+1];
        }
        (*queue_cnt)--;

        return found;
    }
}

struct RCB handle_request_arrival_look(struct RCB request_queue[QUEUEMAX],int *queue_cnt, struct RCB current_request, struct RCB new_request, int timestamp){
      if (
      current_request.request_id == 0 &&
      current_request.arrival_timestamp == 0 &&
      current_request.cylinder == 0 &&
      current_request.address == 0 &&
      current_request.process_id == 0
  ) {
    return new_request;
  } else {
    request_queue[*queue_cnt] = new_request;
    (*queue_cnt)++;
    return current_request;
  }
}

struct RCB handle_request_completion_look(struct RCB request_queue[QUEUEMAX],int *queue_cnt, int current_cylinder, int scan_direction){
    if (*queue_cnt == 0){
        struct RCB NULLRCB;
        NULLRCB.request_id = 0;
        NULLRCB.arrival_timestamp = 0;
        NULLRCB.cylinder = 0;
        NULLRCB.address = 0;
        NULLRCB.process_id = 0;
        return NULLRCB;
    } else {
       int smallest = INT_MAX;
       int found = -1;
       int closest_large_one = INT_MAX;
       int closest_small_one = INT_MAX;
       int distance_from_cylinder = INT_MAX;
       int overall_closest = INT_MAX;
       int overall_found = -1;
       int found_large = -1;
       int found_small = -1;
       int picked = -1;
       int i;

       for(i = 0; i < (*queue_cnt)-1; i++){
            int current_distance = abs(request_queue[i].cylinder - current_cylinder);
            if (current_distance < overall_closest) {
                overall_closest = current_distance;
                overall_found = i;
            }

            if(request_queue[i].cylinder == current_cylinder){
                if (request_queue[i].arrival_timestamp < smallest) {
                    smallest = request_queue[i].arrival_timestamp;
                    found = i;
                }
                continue;
            }

            if (request_queue[i].cylinder > current_cylinder) {
                int current_distance = abs(request_queue[i].cylinder - current_cylinder);
                if (current_distance < closest_large_one) {
                    closest_large_one = current_distance;
                    found_large = i;
                }
            }

            if (request_queue[i].cylinder < current_cylinder) {
                int current_distance = abs(request_queue[i].cylinder - current_cylinder);
                if (current_distance < closest_small_one) {
                    closest_small_one = current_distance;
                    found_small= i;
                }
            }
        }

        if (found > -1) {
            picked = found;
        } else {
            if (scan_direction == 1){
                if (found_large > -1) {
                    picked =  found_large;
                }
                if (found_large == -1) {
                    picked =  overall_found;
                }
            } else if (scan_direction == 0){
               if (found_small > -1) {
                    picked =  found_small;
                }
                if (found_small == -1) {
                    picked =  overall_found;
                }
            }
        }

        struct RCB returnable = request_queue[picked];

        for (i = picked; i < (*queue_cnt) - 1; i++) {
            request_queue[i] = request_queue[i+1];
        }
        (*queue_cnt)--;

        return returnable;
    }
}