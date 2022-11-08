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
int t_burst_t=0;
int total_burtst_time;
int shortest_time=100000;
int complete_time;
int t_complete_time;
int waiting_time;
float avg_wait;
float avg_turna;
int h_priority=-1000;
int t_response;
float avg_t_resp;
int last_prior=-1000;

//reverse list
struct node * reverse(struct  node *p_head){
    struct node *r_head=NULL;
    while(p_head!=NULL){
        insert(&r_head,p_head->task);
        p_head = p_head->next;
    }

    return r_head;
}

int has_task(struct node *n,struct task *t){
    while (n!=NULL){
        if(n->task==t) {
            return 1;
        }
        else{
            n=n->next;
        }
    }
    return 0;
}

//return the highest priority task
void h_task(){
    int if_unique=1;
    struct node *same_p = NULL;
    h_priority=-1000;
    struct node *local_head =NULL;
    local_head=head;
    struct task *h_task = malloc(100);
    while(head!=NULL){
        if (head->task->priority > h_priority) {
            h_priority = head->task->priority;
            h_task=head->task;
        }
        head=head->next;
    }
    //find if there are tasks with same priority
    head = local_head;
    while(head!=NULL){
        if (head->task->priority == h_priority && head->task!=h_task) {
            if_unique=0;
            insert(&same_p,head->task);
        }
        if (head->task->priority == h_priority && head->task==h_task) {

            insert(&same_p,head->task);
        }
        head=head->next;
    }
    same_p=reverse(same_p);
    while (same_p!=NULL && if_unique==0) {
        if (last_prior!=h_priority){
            t_response+=complete_time;

        }
        if (same_p->task->burst > 10 ) {
            run(same_p->task, 10);
            same_p->task->burst-=10;
            complete_time += 10;

        } else if (same_p->task->burst > 0 && same_p->task->burst <= 10) {
            complete_time += same_p->task->burst;
            run(same_p->task, same_p->task->burst);
            t_complete_time += complete_time;
            if (has_task(copy_head, same_p->task)) {
                delete(&copy_head, same_p->task);
            }
        }
        same_p=same_p->next;
    }

    if (if_unique==1){
        t_burst_t +=h_task->burst;
        run(h_task, h_task->burst);
        complete_time+=h_task->burst;
        t_response+=complete_time;
        t_complete_time += complete_time;
        if (has_task(copy_head,h_task)){
            delete(&copy_head,h_task);
        }
    }



}



void schedule(){

    copy_head=malloc(sizeof(struct node));
    copy_head=reverse(head);
    head=reverse(head);



    while (copy_head !=NULL) {
        h_task();
        last_prior=h_priority;
        head=copy_head;
    }
    waiting_time = t_complete_time-total_burtst_time;
    t_response-=t_burst_t;
    avg_wait = ((float)waiting_time)/(float)task_id;
    avg_turna = ((float)t_complete_time)/(float)task_id;
    avg_t_resp = ((float) t_response/(float)task_id);

    printf("\nAverage waiting time = %.2f \n",avg_wait);
    printf("Average turnaround time = %.2f \n",avg_turna);
    printf("Average response time = %.2f \n",avg_t_resp);

}

void add(char *name, int priority, int burst){
    struct task *task=malloc(sizeof(struct task));
    task->name=name;
    task_id++;
    task->tid=task_id;
    task->burst=burst;
    task->priority=priority;
    //calculate total burst time
    total_burtst_time+=task->burst;
    insert(&head,task);
}







