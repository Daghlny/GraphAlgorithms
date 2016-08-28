
#include "types.hpp"
#include "uGraph.hpp"

#include <set>
#include <algorithm>
#include <fstream>
#include <iostream>

// Global Vals

uint64_t clique_num;
uint64_t max_clique_size;
std::ofstream cfile;

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

    tasklist(task_t *h, task_t *t): head(h), tail(t), len(0){}

    void remove_tail(){
        
        --len;
        /*
        std::cout << "Cand: ";
        print_vlist(tail->cand);
        std::cout << std::endl;
        */

        if(tail == NULL && head == NULL){
            return ;
        } else if(tail != NULL && head != NULL && tail != head){
            tail->pre->next = NULL;
            tail = tail->pre;
        } else if(tail != NULL && head != NULL && tail == head){
            head = NULL;
            tail = NULL;
        } else {
            std::cout << "Remove Error" << std::endl;
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
    size_t len;
};

// some tools to deal with parameters of program
int         deal_parameters(size_t , char **);
std::string get_option_string(std::string);
int         get_option_int(std::string);


void        do_task( task_t   *t, 
                     tasklist &tasks, 
                     uGraph   *g,
                     void    (*output_func)(vlist *));

// return a new vlist that is the intersection of @v1 and @v2
vlist*   get_intsct(const vlist *v1, const vlist *v2);

// return a vlist that contains all elems in @vl and @v
vlist*   set_insert_copy(vlist *vl, vid_t v);
vlist*   set_insert_copy(vid_t v);

// release all memory of task_t
void     release_task(task_t *t);

// print a vlist in standard output
void     print_vlist(vlist *v);


// compute all maximal cliques with BFS method
// it means all cliques of size k is generated from size k-1
//
// all kinds of implementation of @output_func should delete the memory of vlist
void
clique_compute( uGraph *g,
                void (*output_func)(vlist *)){
    
    vlist allvtx;
    g->vertex_set(allvtx);

    tasklist tasks(NULL, NULL);

    for(vlist::const_iterator iter = allvtx.begin();
        iter != allvtx.end();
        ++iter){
    
        vlist *tmp_cand = new vlist(g->adjlist(*iter));
        task_t *tmp = new task_t( tmp_cand, set_insert_copy(*iter), *iter);
        tasks.insert_tail(tmp);
    }

    clique_num = 0;
    max_clique_size = 0;
    // main loop, keep process the tasks linkedlist until no tasks remain
    while( tasks.head != NULL ){
        
        std::cout << "remaining tasks: " << tasks.len << std::endl;
        task_t *new_task = tasks.head;
        tasks.remove_head();
        do_task( new_task, tasks, g, output_func );
    }
}

// finish one task
void
do_task( task_t   *t,
         tasklist &tasks,
         uGraph   *g,
         void    (*output_func)(vlist *) ){
    
    /* this section just for debugging
     *
    std::cout << " *** begin *** " << std::endl;
    print_vlist(t->c);
    print_vlist(t->cand);
    std::cout << " *** end *** " << std::endl;
    */

    if( t->cand->size() == 0 ){
        //std::cout << "hehe" << std::endl;
        clique_num++;
        output_func(t->c);
        max_clique_size = std::max(max_clique_size, t->c->size());
        release_task(t);
        return ;
    }

    for( vlist::const_iterator iter = t->cand->begin();
         iter != t->cand->end();
         ++iter ){

        //std::cout << t->flag << '\t' << *iter << std::endl;
        
        if( *iter < t->flag )
            continue;

        const vlist *adjl = &(g->adjlist(*iter));
        vlist *candidate = get_intsct(adjl, t->cand);

        if(candidate->size() != 0){
            vlist  *newc = set_insert_copy(t->c, *iter);
            task_t *tmp  = new task_t(candidate, newc, *iter);
            tasks.insert_tail(tmp);
        } else {
            vlist *res = set_insert_copy(t->c, *iter);
            max_clique_size = std::max(max_clique_size, t->c->size()+1);
            output_func( res );
            clique_num++;
            delete res;
            delete candidate;
        }

    }

    release_task(t);
}

vlist* 
get_intsct(const vlist *v1, const vlist *v2){
    
    vlist *res    = new vlist();
    const vlist *lo     = v1->size() > v2->size() ? v2 : v1;
    const vlist *check  = lo == v1 ? v2 : v1;

    for( vlist::const_iterator iter = lo->cbegin();
         iter != lo->cend();
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
    
    for(vlist::iterator iter = v->begin();
        iter != v->end();
        ++iter) 
        cfile << *iter << ' ';
    cfile << std::endl;
}

int
main(int argc, char **argv){
   
    uGraph *g = new uGraph(argv[1]);
    std::string filepath(argv[1]);
    filepath += ".bfs.clique";
    cfile.open(filepath.c_str());
    clique_compute(g, write_vlist);
    cfile.close();

    std::cout << "Total Clique Numbers: " << clique_num << std::endl;
    std::cout << "Maximum size of cliques: " << max_clique_size << std::endl;

    return 0;
}

