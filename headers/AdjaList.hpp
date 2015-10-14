#ifndef __HEADERS__ADJALIST__H__
#define __HEADERS__ADJALIST__H__

#include<cstdint>
#include<iostream>

typedef uint64_t vertex_id_t;

class adjaNode{
	friend class AdjaList;
	//friend GreedyColoring because in run_wp() needs visit the adjaNode's value
	friend class GreedyColoring;
	public:
		adjaNode *next;
		adjaNode *pre;
		vertex_id_t Nid;
};

class AdjaList{
	public:
		AdjaList():head(0), tail(0), num(0){}
		
		void addEdge(vertex_id_t destID);
		void deleteEdge(vertex_id_t destID);
		
		adjaNode *getHead(){ return head;}
		adjaNode *getTail(){ return tail;}
		adjaNode *findNode(vertex_id_t destID);
		
		size_t   size(){return num;}

	private:
		adjaNode *head;
		adjaNode *tail;
		size_t   num;
};

void
AdjaList::addEdge(vertex_id_t destID){
	adjaNode *node = new adjaNode();
	if(node == NULL) return;
	node->Nid = destID;
	
	if(tail != NULL){
		node->pre  = tail;
		tail->next = node;
		tail = node;
	}
	else{
		node->pre  = NULL;
		head       = node;
		tail       = node;
	}
	node->next = NULL;
	num++;
	
}

void
AdjaList::deleteEdge(vertex_id_t destID){
	adjaNode *pos = findNode(destID);
	if(pos == NULL) return;
	
	pos->pre->next = pos->next;
	pos->next->pre = pos->pre;
	
	delete pos;
	--num;
}

adjaNode*
AdjaList::findNode(vertex_id_t destID){
	adjaNode *cur = head;
	while(cur != NULL){
		if(cur->Nid == destID) return cur;
	}
	return NULL;
}

#endif
