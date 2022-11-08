#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "task.h"
#include "cpu.h"
#include "schedulers.h"
#include "list.h"


int task_id;
struct node *head = NULL;
struct node *copy_head;

int shortest_time=100000;
int complete_time;
int waiting_time;
float avg_wait;
float avg_turna;
int t_complete_time;

void schedule(){
    copy_head=malloc(sizeof(struct node));

    copy_head=head;
    struct task *shortest_task=malloc(100);

    while (head !=NULL) {
        while (head!= NULL) {
            if (head->task->burst <= shortest_time) {
                shortest_time = head->task->burst;
                memcpy(shortest_task,head->task,100);
            }
            head = head->next;
        }
        run(shortest_task,shortest_task->burst);
        complete_time += shortest_task->burst;
        t_complete_time += complete_time;
        waiting_time = waiting_time +complete_time -shortest_task->burst ;
        delete(&copy_head,shortest_task);
        head=copy_head;
        shortest_time=10000;
    }
    avg_wait = ((float)waiting_time)/(float)task_id;
    avg_turna = ((float)t_complete_time)/(float)task_id;
    printf("\nAverage waiting time = %.2f \n",avg_wait);
    printf("Average turnaround time = %.2f \n",avg_turna);
    printf("Average response time = %.2f \n",avg_wait);
}

void add(char *name, int priority, int burst){
    struct task *task=malloc(sizeof(struct task));
    task->name=name;
    task_id++;
    task->tid=task_id;
    task->burst=burst;
    task->priority=priority;

    insert(&head,task);
}

