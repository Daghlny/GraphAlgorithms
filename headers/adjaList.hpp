
// author: Ritchie Lee
// date:   15-10-21

#ifndef __HEADERS__ADJALIST__HPP__
#define __HEADERS__ADJALIST__HPP__

#include"types.hpp"

// a_node is the node stored in adjacency list in types.hpp
// @adjaList is one adjacency list in a graph
class adjaList{
public:
	adjaList():head(NULL), tail(NULL), num(0){}

	void add_edge(vertex_id_t u);
	void del_edge(vertex_id_t u);
	void find_edge(vertex_id_t u);

	usize_t size(){return num;}

private:
	a_node  *head;
	a_node  *tail;
	usize_t num;
};

void
adjaList::add_edge(vertex_id_t u){
	a_node *new_node = new a_node();
	new_node->nid = u;
	if( head == NULL && tail == NULL){
		head = new_node;
		tail = new_node;
		return;
	}
	tail->next = new_node;
	new_node->next = NULL;
	tail = new_node;
}

a_node*
adjaList::find_edge(vertex_id_t u){
	a_node *cur = head;
	while(cur != NULL){
		if(cur->nid == u)
			return cur;
	}
	return NULL;
}

void
adjaList::del_edge(vertex_id_t u){
	a_node *pos = find_edge(u);
	if(pos == NULL) return;

	pos->pre->next = pos->next;
	pos->next->pre = pos->pre;

	delete pos;
	--num;
}




















#endif

