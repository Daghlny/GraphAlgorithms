
#include "types.hpp"
#include "uGraph.hpp"

#include <set>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <pthread.h>
#include <stdlib.h>

// Global Vals

uint64_t clique_num;
uint64_t max_clique_size;
std::ofstream cfile;
pthread_mutex_t *f_lock;

void     print_vlist(vlist *v);

// type definitions

// @task_t represents a indenpendent task to compute cliques from @cand
// @flag is the biggest index of vertices having visited
struct task_t{

    task_t( vlist *x_cand, vlist *x_c, vid_t x_flag,
            task_t *x_pre = NULL, task_t *x_next = NULL): 
        cand(x_cand), c(x_c), flag(x_flag), pre(x_pre), next(x_next){}

    vlist   *cand;
    vlist   *c;
    vid_t   flag;
    task_t  *pre;
    task_t  *next;
};

struct tasklist {

    tasklist(task_t *h, task_t *t): head(h), tail(t), len(0){
        //t_lock = (pthread_mutex_t)(malloc(sizeof(pthread_mutex_t)));
        if( pthread_mutex_init(&t_lock, NULL) != 0 && 
            pthread_mutex_init(&h_lock, NULL) != 0 ) {
            std::cout << "The Pthread Lock in Tasklist is Wrong" << std::endl;
            exit(0);
        }
    }

    void insert_tail( task_t *tmp ){
        
        ++len;

        if( head == NULL && tail == NULL ){
            head = tmp;
            tail = tmp;
            tmp->pre = NULL;
            tmp->next = NULL;
        } else if(head != NULL && tail != NULL){
            tmp->pre = tail;
            tail->next = tmp;
            tail = tmp;
            tmp->next = NULL;
        } else {
            std::cout << "Error: " << std::endl;
        }

    }

    void remove_head() {

        --len;
        
        if(tail == NULL && head == NULL){
            return ;
        } else if (tail != NULL && head != NULL && tail != head) {
            head->next->pre = NULL;
            head = head->next;
        } else if (tail != NULL && head != NULL && tail == head) {
            head = NULL;
            tail = NULL;
        } else {
            std::cout << "Remove queue's head Error" << std::endl;
            exit(0);
        }
    }

    task_t *head;
    task_t *tail;
    pthread_mutex_t h_lock;
    pthread_mutex_t t_lock;
    size_t len;
};

struct thread_busy_count {
    
    thread_busy_count(){
        cnt = 0;
        pthread_mutex_init(&lock, NULL);
    }
    size_t cnt;
    pthread_mutex_t lock;
};

struct thread_task {

    thread_task( uGraph* xg, 
                 tasklist *xtl, 
                 thread_busy_count *xtc, 
                 void (*xoutput)(vlist*)):
        g(xg), tl(xtl), tbc(xtc), output(xoutput){}

    uGraph *g;
    tasklist *tl;
    thread_busy_count *tbc;
    void (*output)(vlist *);
};

// some tools to deal with parameters of program
int         deal_parameters(size_t , char **);
std::string get_option_string(std::string);
int         get_option_int(std::string);


void        do_task( task_t   *t, 
                     tasklist *tasks, 
                     uGraph   *g,
                     void    (*output_func)(vlist *));

void*       thread_compute_clique( void *thread_info_ptr );

// return a new vlist that is the intersection of @v1 and @v2
vlist*   get_intsct(vlist *v1, vlist *v2);

// return a vlist that contains all elems in @vl and @v
vlist*   set_insert_copy(vlist *vl, vid_t v);
vlist*   set_insert_copy(vid_t v);

// release all memory of task_t
void     release_task(task_t *t);

// print a vlist in standard output
void     print_vlist(vlist *v);


// compute all maximal cliques with BFS method
// it means all cliques of size k is generated from size k-1

// all kinds of implementation of @output_func should delete the memory of vlist
void
clique_compute( uGraph *g,
                void (*output_func)(vlist *),
                int  thread_num){
    
    vlist *allvtx = new vlist();
    g->vtx_set(allvtx);

    tasklist tasks(NULL, NULL);

    for(vlist::const_iterator iter = allvtx->begin();
        iter != allvtx->end();
        ++iter){
    
        vlist *tmp_cand = new vlist( *(g->adjlist(*iter)) );
        task_t *tmp = new task_t( tmp_cand, set_insert_copy(*iter), *iter);
        tasks.insert_tail(tmp);
    }

    // Create @thread_num Threads to Compute Maximal Cliques

    thread_busy_count *t_count = new thread_busy_count();
    pthread_t **threads = (pthread_t **)(malloc(sizeof(pthread_t *) * thread_num));

    for(int i = 0; i != thread_num; ++i){
        thread_task *thread_info_ptr = new thread_task(g, &tasks, t_count, output_func);
        threads[i] = (pthread_t *)(malloc(sizeof(pthread_t)));
        if((pthread_create( threads[i], 
                            NULL, 
                            thread_compute_clique, 
                            (void*)thread_info_ptr ) ) != 0 ) {
            std::cout << "Thread Creating has wrong" << std::endl;
            i--;
        }
    }

    while(true){
        if( t_count->cnt == thread_num && tasks.head == NULL ){
            std::cout << "All works have been done" << std::endl;
            break;
        }
    } 

    return ;
}


void*
thread_compute_clique(void *thread_info_ptr){

    thread_task *tt = (thread_task *)(thread_info_ptr);
    tasklist *tasks = (tasklist *)(tt->tl);
    uGraph   *g     = (uGraph *)(tt->g);
    thread_busy_count *tbc = (thread_busy_count *)(tt->tbc);

    while(true){

        pthread_mutex_lock(&tbc->lock);
        tbc->cnt++;
        pthread_mutex_unlock(&tbc->lock);

        pthread_mutex_lock(&tasks->h_lock);
        while( tasks->head == NULL );
        pthread_mutex_lock(&tasks->t_lock);

        pthread_mutex_lock(&tbc->lock);
        tbc->cnt--;
        pthread_mutex_unlock(&tbc->lock);

        task_t *t = tasks->head;
        tasks->remove_head();

        pthread_mutex_unlock(&tasks->t_lock);
        pthread_mutex_unlock(&tasks->h_lock);

        do_task(t, tasks, g, tt->output);
    }
    
    return NULL;
}


// finish one task
void
do_task( task_t   *t,
         tasklist *tasks,
         uGraph   *g,
         void    (*output_func)(vlist *) ){
    
    if( t->cand->size() == 0 ){
        output_func(t->c);
        release_task(t);
        return ;
    }

    for( vlist::const_iterator iter = t->cand->begin();
         iter != t->cand->end();
         ++iter ){

        if( *iter < t->flag )
            continue;

        vlist *adjl = g->adjlist(*iter);
        vlist *candidate = get_intsct(adjl, t->cand);

        if(candidate->size() != 0){
            vlist  *newc = set_insert_copy(t->c, *iter);
            task_t *tmp  = new task_t(candidate, newc, *iter);
            pthread_mutex_lock(&tasks->t_lock);
            tasks->insert_tail(tmp);
            pthread_mutex_unlock(&tasks->t_lock);
        } else {
            vlist *res = set_insert_copy(t->c, *iter);
            output_func( res );
            delete res;
        }

    }

    release_task(t);
}

vlist* 
get_intsct(vlist *v1, vlist *v2){
    
    vlist *res    = new vlist();
    vlist *lo     = v1->size() > v2->size() ? v2 : v1;
    vlist *check  = lo == v1 ? v2 : v1;

    for( vlist::const_iterator iter = lo->begin();
         iter != lo->end();
         ++iter )
        if( check->find(*iter) != check->end() )
            res->insert(*iter);

    return res;
}

/*
vlist*
get_intsct(vlist *v1, vlist *v2){
    
    vlist *res = new vlist();
    vlist *lo  = v1->size() > v2->size() ? v2 : v1;
    vlist *ch  = lo == v1 ? v2 : v1;

    for( vlist::const_iterator iter = lo->begin();
         iter != lo->end();
         ++iter)
        if( e )
}
*/

void
release_task(task_t *t){
   
    delete t->cand;
    delete t->c;
    delete t;
}

vlist*
set_insert_copy( vlist* vl, vid_t v){
    
    vlist *res = new vlist(*vl);
    res->insert(v);
    return res;
}

vlist*
set_insert_copy( vid_t v ){
    
    vlist *res = new vlist();
    res->insert(v);
    return res;
}

// some implementations of global functions whose duty is to store all cliques
void
print_vlist(vlist *v){
   
    for(vlist::iterator iter = v->begin();
        iter != v->end();
        ++iter )
        std::cout << *iter << ' ';
    std::cout << std::endl;
}

void
write_vlist(vlist *v){

    pthread_mutex_lock(f_lock);
    
    for(vlist::iterator iter = v->begin();
        iter != v->end();
        ++iter) 
        cfile << *iter << ' ';
    cfile << std::endl;
    pthread_mutex_unlock(f_lock);
}

int
main(int argc, char **argv){
   
    if( argc ==  0) {
        std::cout << "The Program needs two parameters." << std::endl;
        std::cout << "1 - The input Graph File" << std::endl;
        std::cout << "2 - The Thread's Number" << std::endl;
        return 0;
    }
    uGraph *g = new uGraph(argv[1]);
    std::string filepath(argv[1]);
    filepath += ".bfs.multithreads.clique";
    cfile.open(filepath.c_str());

    f_lock = (pthread_mutex_t *)(malloc(sizeof(pthread_mutex_t)));
    pthread_mutex_init(f_lock, NULL);

    int thread_num = atoi(argv[2]);

    clique_compute(g, write_vlist, thread_num);

    cfile.close();

    //std::cout << "Total Clique Numbers: " << clique_num << std::endl;
    //std::cout << "Maximum size of cliques: " << max_clique_size << std::endl;

    return 0;
}

