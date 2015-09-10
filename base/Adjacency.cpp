#include"Adjacency.hpp"

template<typename vertexT> adjaNode&
base::adjaNode<typename>::getNext(){
	return *next;
}

template<typename vertexT> void
base::adjaNode<typename>::addNext(vertex_t id){
	adjaNode *tmp = new adjaNode(id);
	this->next = tmp;
}

template<typename vertexT> void
base::AdjaList<typename>::addEdge(vertex_t id){
	num++;
	if(head == NULL && tail == NULL){
		adjaNode tmp = new adjaNode(id);
		head = tmp;
		tail = tmp;
		return;
	}	

	tail->addNext(id);
}

template<typename vertexT> void*
base::AdjaList<typename>::findVertex(vertex_t id){
	adjaNode *curr = head;
	while(curr != NULL){
		if(curr->vertexID == id)
			return std::static_cast<void *>(curr);
		curr = curr->next;
	}
	return NULL;
}

template<typename vertexT> void
base::AdjaList<typename>::deleteEdge(vertex_t id){
	adjaNode *pre = head, *curr = head;
	/* something need done future */
	while(curr != NULL){
		
	}
}






















