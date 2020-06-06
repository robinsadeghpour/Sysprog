#include "../lib/PRIOP.h"
#include <stdio.h>

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
        if (last_item != NULL && last_item->priority > running_process->priority && running_process->time_left != 0)
        {
            queue_add(running_process, PRIOP_queue);
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