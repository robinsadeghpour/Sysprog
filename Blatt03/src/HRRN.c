#include "../lib/HRRN.h"
#include <stdio.h>

// calculate response ratio
float calculate_rr(process *my_process) {
    if(my_process==NULL || my_process->time_left==0) {
        return -1;
    }

    float waitingtime = current_tick-my_process->start_time;
    float runtime = ((float)my_process->time_left);
    //float ratio = 1.0 + ((current_tick - my_process -> start_time) / my_process -> time_left);
    return (waitingtime+runtime) / runtime;
}

// add to queue ordered by response ratio
int rr_queue_add(process *arriving_process, queue_object* queue) {
    queue_object* new_queue_object= calloc(1,sizeof(queue_object));
    new_queue_object->object=arriving_process;
    
    // loop through loop while there are processes with rr less than the rr from new process
    queue_object* current=queue;
    while(current->next!=NULL && calculate_rr((process*)(current->next->object)) < calculate_rr(arriving_process)) {
        current = current->next;
    }

    if(current->next==NULL) {
        // new process has highest rr
        current->next = new_queue_object;
        new_queue_object->next = NULL;
    } else {
        // process has not highest rr so insert inbetween
        new_queue_object->next = current->next;
        current->next = new_queue_object;
    }

    return 0;
}

// sort the queue 
queue_object* sort_queue_rr_inplace(queue_object* queue) {
    queue_object* sorted_queue = new_queue();

    process* my_process;
    while((my_process= queue_poll(queue))!=NULL) {
        rr_queue_add(my_process, sorted_queue);
    }  
    free(queue);
    return sorted_queue;  
}

process* HRRN_tick (process* running_process) {
    if (running_process == NULL || running_process->time_left == 0)
    {
        // there is no running process or the running process finished
        // poll new process
        HRRN_queue = sort_queue_rr_inplace(HRRN_queue);
        running_process = queue_poll(HRRN_queue);
    }
    if (running_process != NULL)
    {
        running_process->time_left--;
    }
    
    current_tick+= 1.0;
    
    return running_process;
}

int HRRN_startup(){
    HRRN_queue = new_queue();
    current_tick = 0.0;
    if (HRRN_queue == NULL)
    {
        return 1;
    }
    return 0;
}

process* HRRN_new_arrival(process* arriving_process, process* running_process){
     if (arriving_process != NULL)
    {
        rr_queue_add(arriving_process, HRRN_queue);
    }
    return running_process;
}

void HRRN_finish(){
    free_queue(HRRN_queue);
}