#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "task.h"
#include "cpu.h"
#include "schedulers.h"
#include "list.h"

#ifdef LIST_H
#define LIST_H
 struct  node;
#endif

int complete_time;
int waiting_time;
int task_id;
float avg_wait;
float avg_turna;
int t_complete_time;
void schedule(){
    avg_wait = ((float)waiting_time)/(float)task_id;
    avg_turna = ((float)t_complete_time)/(float)task_id;
    printf("\nAverage waiting time = %.2f \n",avg_wait);
    printf("Average turnaround time = %.2f \n",avg_turna);
    printf("Average response time = %.2f \n",avg_wait);
}

void add(char *name, int priority, int burst){
    struct task task;
    task.name=name;
    task_id++;
    task.tid=task_id;
    task.burst=burst;
    task.priority=priority;
    complete_time += burst;
    t_complete_time+=complete_time;
    waiting_time = waiting_time +complete_time -burst ;

    run(&task,task.burst);

}



