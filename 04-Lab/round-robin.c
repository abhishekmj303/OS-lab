#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int pid;
    int at, bt;
    int priority;
    int start_time, run_time;
    int ft, tat, wt, rt;
} Process;

int n;
Process readyQueue[1000];
int q_size;
int arriving_size;

void copy(Process *a, Process *b)
{
    b->pid = a->pid;
    b->at = a->at;
    b->bt = a->bt;
    b->start_time = a->start_time;
    b->run_time = a->run_time;
    b->ft = a->ft;
    b->tat = a->tat;
    b->wt = a->wt;
    b->rt = a->rt;
}

void insertReadyQueue(Process *p)
{
    if (p == NULL)
        return;

    copy(p, &readyQueue[q_size]);
    q_size++;
}

Process *popReadyQueue()
{
    if (readyQueue == NULL)
        return NULL;
    
    Process *p = (Process *)malloc(sizeof(Process));
    copy(&readyQueue[0], p);
    q_size--;

    for (int i = 0; i < q_size; i++)
    {
        copy(&readyQueue[i+1], &readyQueue[i]);
    }
    return p;
}

Process *getProcessesAt(Process *processes, int time)
{
    // dynamically increase the size of the array
    Process *arr = NULL;
    arriving_size = 0;
    for (int i = 0; i < n; i++)
    {
        if (processes[i].at == time)
        {
            arr = (Process *)realloc(arr, (arriving_size + 1) * sizeof(Process));
            arr[arriving_size] = processes[i];
            arriving_size++;
        }
    }
    return arr;
}

int roundRobin(Process *processes, int quantum)
{
    int current_quantum = 0;
    int context_switch = 0;
    int completed = 0;
    Process *p = NULL;

    for (int time = 0; completed != n; time++)
    {
        Process *arrived = getProcessesAt(processes, time);
        for (int i = 0; i < arriving_size ; i++)
        {
            insertReadyQueue(&arrived[i]);
        }

        if (p != NULL && p->run_time == p->bt)
        {
            p->ft = time;
            p->tat = p->ft - p->at;
            p->wt = p->tat - p->bt;
            p->rt = p->start_time - p->at;
            copy(p, &processes[p->pid - 1]);

            completed++;
            context_switch++;
            p = NULL;
            current_quantum = 0;
        }

        if (p == NULL || current_quantum == quantum)
        {
            if (p != NULL)
            {
                insertReadyQueue(p);
                context_switch++;
            }
            p = popReadyQueue();
            if (p != NULL && p->run_time == 0)
            {
                p->start_time = time;
            }
            current_quantum = 0;
        }

        if (p != NULL)
        {
            p->run_time++;
            current_quantum++;
        }
    }
    return context_switch-1;
}

void print_result(Process *processes, int context_switch)
{
    printf("P_ID:  AT\tPR\tBT\tFT\tTAT\tWT\tRT\n");

    int total_wt = 0, total_tat = 0, total_rt = 0;
    for (int i = 0; i < n; i++)
    {
        printf("   %d:  %d\t%d\t%d\t%d\t%d\t%d\t%d\n", processes[i].pid, processes[i].at, processes[i].priority, processes[i].bt, processes[i].ft, processes[i].tat, processes[i].wt, processes[i].rt);

        total_wt += processes[i].wt;
        total_tat += processes[i].tat;
        total_rt += processes[i].rt;
    }

    printf("Average Waiting Time: %.2f\n", (float)total_wt / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_tat / n);
    printf("Average Response Time: %.2f\n", (float)total_rt / n);
    printf("Number of Context Switch: %d\n", context_switch);
}

int main()
{
    int quantum;
    printf("Enter the time quantum: ");
    scanf("%d", &quantum);

    printf("Enter the number of processes: ");
    scanf("%d", &n);
    
    printf("Enter Arrival time and Burst time:\n");
    Process *processes = (Process *)malloc(n * sizeof(Process));
    for (int i = 0; i < n; i++)
    {
        Process p;
        p.pid = i+1;
        p.run_time = 0;
        p.start_time = 0;
        
        printf("For Process_id %d: ", p.pid);
        scanf("%d %d", &p.at, &p.bt);
        
        processes[i] = p;
    }
    
    int context_switch = roundRobin(processes, quantum);
    print_result(processes, context_switch);

    free(processes);
    return 0;
}