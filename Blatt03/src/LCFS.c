#include "../lib/LCFS.h"

int LCFS_startup()
{
    //TODO
    LCFS_queue = new_queue();
    if (LCFS_queue==NULL){
        return 1;
    }

    return 0;
}

// poll last came process
process *queue_poll_first(queue_object *queue)
{
    if (queue == NULL || queue->next == NULL)
    {
        return NULL;
    }
    process* object = queue->next->object;
    void* next_object = queue->next->next;
    free(queue->next);
    queue->next = next_object;
    return object;
}

process *LCFS_tick(process *running_process)
{
    //TODO
    // same as FCFS but polling last came process
    if (running_process == NULL || running_process->time_left == 0)
    {
        running_process = queue_poll_first(LCFS_queue);
    }
    if (running_process!=NULL){
        running_process->time_left--;
    }
    return running_process;
}

process *LCFS_new_arrival(process *arriving_process, process *running_process)
{
    //TODO
    if(arriving_process!=NULL){
        queue_add(arriving_process, LCFS_queue);
    }
    return running_process;
}

void LCFS_finish()
{
    //TODO
    free_queue(LCFS_queue);
}

