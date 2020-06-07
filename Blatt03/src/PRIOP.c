#include "../lib/PRIOP.h"
#include <stdio.h>

// add to queue ordered by priority
int prio_queue_add(process *arriving_process, queue_object *queue, int readd)
{
    queue_object *new_queue_object = calloc(1, sizeof(queue_object));
    new_queue_object->object = arriving_process;

    // loop through loop while there are processes with prios less than the prio from new process
    queue_object *current = queue;

    if (readd == 1)
    {
        // we want to add an previously removed item again in order by prio but by keeping first come first serve principle
        while (current->next != NULL && ((process *)(current->next->object))->priority <= arriving_process->priority)
        {
            current = current->next;
        }
    }
    else
    { // add complete new item to queue
        while (current->next != NULL && ((process *)(current->next->object))->priority < arriving_process->priority)
        {
            current = current->next;
        }
    }
    if (current->next == NULL)
    {
        // new process has highest prio
        current->next = new_queue_object;
        new_queue_object->next = NULL;
    }
    else
    {
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
        if (last_item != NULL && last_item->priority > running_process->priority)
        {
            // new arriving process has higher prio
            // add running process back to queue and set running process ti the process with higher prio
            prio_queue_add(running_process, PRIOP_queue, 1);
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
        prio_queue_add(arriving_process, PRIOP_queue, 0);
    }

    return running_process;
}

void PRIOP_finish()
{
    //TODO
    free_queue(PRIOP_queue);
}