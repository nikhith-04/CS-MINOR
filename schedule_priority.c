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

int h_priority=-1000;
int complete_time;
int waiting_time;
float avg_wait;
float avg_turna;
int t_completet_time;

void schedule(){
    copy_head=malloc(sizeof(struct node));
    copy_head=head;
    struct task *h_p_task=malloc(100);

    while (head !=NULL) {
        while (head!= NULL) {
            if (head->task->priority >= h_priority) {
                h_priority = head->task->priority;
                h_p_task=head->task;
//                memcpy(h_p_task,head->task,100);
            }
            head = head->next;
        }
        run(h_p_task,h_p_task->burst);
        complete_time += h_p_task->burst;
        t_completet_time+=complete_time;
        waiting_time = waiting_time +complete_time -h_p_task->burst ;
        delete(&copy_head,h_p_task);
        head=copy_head;
        h_priority=-1000;
    }
    avg_wait = ((float)waiting_time)/(float)task_id;
    avg_turna = ((float)t_completet_time)/(float)task_id;
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



