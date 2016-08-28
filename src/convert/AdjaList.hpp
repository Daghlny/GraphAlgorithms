#ifndef __ADJALIST__H__
#define __ADJALIST__H__

#include<cstdint>
#include<iostream>

typedef uint64_t vertex_id_t;

class adjaNode{
	friend class AdjaList;
	public:
		adjaNode *next;
		vertex_id_t Nid;
};

class AdjaList{
	public:
		AdjaList():head(0), tail(0), num(0){}
		void addEdge(vertex_id_t destID);
		adjaNode *getHead(){ return head;}
		adjaNode *getTail(){ return tail;}
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
	if(tail != 0){
		tail->next = node;
		tail = node;
	}
	else{
		head = node;
		tail = node;
	}
	node->next = 0;
	num++;
}

#endif
