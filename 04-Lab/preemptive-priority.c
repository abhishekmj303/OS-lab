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
    b->priority = a->priority;
    b->start_time = a->start_time;
    b->run_time = a->run_time;
    b->ft = a->ft;
    b->tat = a->tat;
    b->wt = a->wt;
    b->rt = a->rt;
}

void swap(Process *a, Process *b)
{
    Process *temp = (Process *)malloc(sizeof(Process));
    copy(a, temp);
    copy(b, a);
    copy(temp, b);
    free(temp);
}

void insertReadyQueue(Process *p)
{
    if (p == NULL)
        return;

    copy(p, &readyQueue[q_size]);
    q_size++;

    for (int i = q_size - 1; i > 0; i--)
    {
        if (readyQueue[i].priority < readyQueue[i - 1].priority)
        {
            swap(&readyQueue[i], &readyQueue[i - 1]);
        }
        else if (readyQueue[i].priority == readyQueue[i - 1].priority && readyQueue[i].pid < readyQueue[i - 1].pid)
        {
            swap(&readyQueue[i], &readyQueue[i - 1]);
        }
        else
        {
            break;
        }
    }
}

int highestPriority()
{
    return readyQueue[0].priority;
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

void roundRobin(Process *processes)
{
    int completed = 0;
    Process *p = NULL;

    for (int time = 0; completed != n; time++)
    {
        Process *arrived = getProcessesAt(processes, time);
        for (int i = 0; i < arriving_size ; i++)
        {
            insertReadyQueue(&arrived[i]);
        }

        if (q_size == 0)
        {
            continue;
        }

        if (p != NULL && p->bt == p->run_time)
        {
            p->ft = time;
            p->tat = p->ft - p->at;
            p->wt = p->tat - p->bt;
            p->rt = p->start_time - p->at;
            copy(p, &processes[p->pid - 1]);

            completed++;
            p = NULL;
        }

        if (p == NULL || highestPriority() < p->priority)
        {
            insertReadyQueue(p);
            p = popReadyQueue();
            if (p->start_time == 0)
                p->start_time = time;
        }

        p->run_time++;
    }
}

void print_result(Process *processes)
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
}

int main()
{
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    
    printf("Enter Arrival time, Priority and Burst time:\n");
    Process *processes = (Process *)malloc(n * sizeof(Process));
    for (int i = 0; i < n; i++)
    {
        Process p;
        p.pid = i+1;
        p.run_time = 0;
        p.start_time = 0;
        
        printf("For Process_id %d: ", p.pid);
        scanf("%d %d %d", &p.at, &p.priority, &p.bt);
        
        processes[i] = p;
    }
    
    roundRobin(processes);
    print_result(processes);

    free(processes);
    return 0;
}