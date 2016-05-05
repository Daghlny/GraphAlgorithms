
#include "types.hpp"
#include "uGraph.hpp"

#include <set>
#include <algorithm>
#include <fstream>
#include <iostream>


// type definitions

// @task_t represents a indenpendent task to compute cliques from @cand
// @flag is the biggest index of vertices having visited
struct task_t{

    task_t(vlist *x_cand, vid_t x_flag, task_t *x_pre = NULL, task_t *x_next = NULL): 
        cand(x_cand), flag(x_flag), pre(x_pre), next(x_next){}

    vlist   *cand;
    vid_t   flag;
    task_t  *pre;
    task_t  *next;
};

struct tasklist {

    tasklist(task_t h, task_t t): head(h), tail(t) {}

    void remove_tail(){

        if(tail == NULL)
            return;
        tail->pre->next = NULL;
        tail = tail->pre;
    }

    task_t *head;
    task_t *tail;
};

int         deal_parameters(size_t , char **);
std::string get_option_string(std::string);
int         get_option_int(std::string);


void   get_intsct(vlist *v1, vlist *v2);
void   print_vlist(vlist *v);


// compute all maximal cliques with BFS method
// it means all cliques of size k is generated from size k-1
void
clique_compute( uGraph *g,
                void (*output_func)(vlist *)){
    
    vlist *allvtx;
    vtx_set(allvtx);

    tasklist tasks(NULL, NULL);
    for(vlist::const_iterator iter = allvtx.begin();
        iter != allvtx.end();
        ++iter){
       
        task_t *tmp = new task_t(g->adjlist(*iter), *iter, tasks.tail);
        if( tasks.head == NULL )
            tasks.head = tmp; 

        tasks.tail = tmp;
    }

    // main loop, keep process the tasks linkedlist until no tasks remain
    while( tasks.tail != NULL ){
        
        task_t *new_task = tasks.tail;
        tasks.remove_tail();
    }
}

// finish one task
void
do_task( task_t *t ){
    
    if( t->cand.size() == 0 )
}





