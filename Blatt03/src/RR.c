#include "../lib/RR.h"
#include <stdio.h>

process *RR_tick(process *running_process)
{
    //TODO

    if (running_process == NULL || running_process->time_left == 0)
    {
        // there is no running process or the running process finished
        // reset time_left_quantum and get new process
        running_process = queue_poll(RR_queue);
        time_left_quantum = this_quantum;
    }
    if (running_process != NULL)
    {
        if (time_left_quantum == 0 && running_process->time_left != 0)
        {
            // process not finished but quantum finished
            // add process to back to queue, start next process and reset time_left_quantum
            queue_add(running_process, RR_queue);
            running_process = queue_poll(RR_queue);
            time_left_quantum = this_quantum;
        }
        if (time_left_quantum > 0 && running_process->time_left > 0)
        {   
            // process not finished and quantum not finished so make tick
            running_process->time_left--;
            time_left_quantum--;
        }
    }

    return running_process;
}

int RR_startup(int quantum)
{
    //TODO
    RR_queue = new_queue();
    this_quantum = quantum;
    if (RR_queue == NULL)
    {
        return 1;
    }
    return 0;
}

process *RR_new_arrival(process *arriving_process, process *running_process)
{
    if (arriving_process != NULL)
    {
        queue_add(arriving_process, RR_queue);
    }
    return running_process;
}

void RR_finish()
{
    //TODO
    free(RR_queue);
}