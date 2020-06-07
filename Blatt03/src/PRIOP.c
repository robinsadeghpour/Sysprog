#include "../lib/PRIOP.h"
#include <stdio.h>

int queue_add_sorted(process *arriving_process, queue_object* queue) {
    queue_object* new_queue_object= calloc(1,sizeof(queue_object));
    new_queue_object->object=arriving_process;
    
    // loop through loop while there are processes with prios less than the prio from new process
    queue_object* current=queue;
    while(current->next!=NULL && ((process*)(current->next->object))->priority < arriving_process->priority) {
        current = current->next;
    }

    if(current->next==NULL) {
        // new process has highest prio
        current->next = new_queue_object;
        new_queue_object->next = NULL;
    } else {
        // process has not highest prio so insert inbetween
        new_queue_object->next = current->next;
        current->next = new_queue_object;
    }

    return 0;
}


process *PRIOP_tick(process *running_process)
{
    //TODO
    if (running_process == NULL || running_process->time_left == 0)
    {
        // there is no running process or the running process finished
        // poll new process
        running_process = queue_poll(PRIOP_queue);
    }
    if (running_process != NULL)
    {
        process *last_item = queue_peek(PRIOP_queue);
        if (last_item!=NULL && last_item->priority > running_process->priority)
        {
            // new arriving process has higher prio
            // add running process back to queue and set running process ti the process with higher prio
            queue_add_sorted(running_process, PRIOP_queue);
            running_process = queue_poll(PRIOP_queue);
        }
        running_process->time_left--;
    }
    return running_process;
}

int PRIOP_startup()
{
    //TODO
    PRIOP_queue = new_queue();
    if (PRIOP_queue == NULL)
    {
        return 1;
    }
    return 0;
}

process *PRIOP_new_arrival(process *arriving_process, process *running_process)
{
    //TODO
    if (arriving_process != NULL)
    {
        queue_add_sorted(arriving_process, PRIOP_queue);
    }
    return running_process;
}



void PRIOP_finish()
{
    //TODO
    free_queue(PRIOP_queue);
}