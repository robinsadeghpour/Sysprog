#include "../lib/SRTNP.h"

// add to queue ordered by remaining time
int time_queue_add(process *arriving_process, queue_object* queue) {
    queue_object* new_queue_object= calloc(1,sizeof(queue_object));
    new_queue_object->object=arriving_process;
    
    // loop through loop while there are processes with higher remaining time than new process
    queue_object* current=queue;
    while(current->next!=NULL && ((process*)(current->next->object))->time_left > arriving_process->time_left) {
        current = current->next;
    }

    if(current->next==NULL) {
        // new process has shortest remaining time
        current->next = new_queue_object;
        new_queue_object->next = NULL;
    } else {
        // process has not shortest remaining time so insert inbetween
        new_queue_object->next = current->next;
        current->next = new_queue_object;
    }

    return 0;
}

process* SRTNP_tick (process* running_process){
    //TODO
     if (running_process == NULL || running_process->time_left == 0)
    {
        // there is no running process or the running process finished
        // poll new process
        running_process = queue_poll(SRTNP_queue);
    }
    if (running_process != NULL)
    {
        process *last_item = queue_peek(SRTNP_queue);
        if (last_item!=NULL && last_item->time_left < running_process->time_left)
        {
            // new arriving process has shorter remaining time
            // add running process back to queue and set running process to the process with shorter remaining time
            time_queue_add(running_process, SRTNP_queue);
            running_process = queue_poll(SRTNP_queue);
        }
        running_process->time_left--;
    }
    return running_process;
}

int SRTNP_startup(){
    //TODO
    SRTNP_queue = new_queue();
    if (SRTNP_queue == NULL)
    {
        return 1;
    }
    return 0;
}

process* SRTNP_new_arrival(process* arriving_process, process* running_process){
    //TODO
    if (arriving_process != NULL)
    {
        time_queue_add(arriving_process, SRTNP_queue);
    }
    return running_process;
}

void SRTNP_finish(){
    //TODO
    free_queue(SRTNP_queue);
}