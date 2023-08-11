// Abhishek M J
// CS21B2018

#include <stdio.h>
#include <stdlib.h>

struct Process
{
    int pid;
    int at;
    int bt;
    int ft, tat, wt, rt;
    struct Process *next;
};

struct Process *head = NULL;
struct Process *tail = NULL;

void insertReadyQueue(struct Process *p)
{
    if (head == NULL)
    {
        head = p;
        tail = p;
    }
    else
    {
        tail->next = p;
        tail = p;
    }
}

struct Process *popReadyQueue()
{
    struct Process *p = head;
    if (head == tail)
    {
        head = tail = NULL;
    }
    else if (head != NULL)
    {
        head = head->next;
    }
    return p;
}

void fcfs()
{
    printf("\nFCFS\n");
    printf("P_id:  AT\tBT\tFT\tTAT\tWT\tRT\n");
    
    int n = 0;
    int current_time = 0;
    float total_wt = 0, total_tat = 0;
    struct Process *ptr = popReadyQueue();
    while (ptr != NULL)
    {
        printf("   %d:  ", ptr->pid);
        printf("%d\t%d\t", ptr->at, ptr->bt);
        
        if (current_time < ptr->at)
        {
            current_time = ptr->at;
        }
        
        int ft = current_time + ptr->bt;
        int tat = ft - ptr->at;
        int wt = tat - ptr->bt;
        int rt = current_time - ptr->at;
        
        printf("%d\t%d\t%d\t%d\n", ft, tat, wt, rt);
        
        total_wt += wt;
        total_tat += tat;
        current_time += ptr->bt;
        n++;
        
        ptr = popReadyQueue();
    }
    
    printf("Avg waiting time: %f\n", total_wt/n);
    printf("Avg turnaround time: %f\n", total_tat/n);
}

int main()
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    
    printf("Enter Arrival time and Burst time:\n");
    for (int i = 0; i < n; i++)
    {
        struct Process *p = malloc(sizeof(struct Process));
        p->pid = i+1;
        p->next = NULL;
        
        printf("For Process_id %d: ", p->pid);
        scanf("%d %d", &p->at, &p->bt);
        
        insertReadyQueue(p);
    }
    
    fcfs();
    
    return 0;
}