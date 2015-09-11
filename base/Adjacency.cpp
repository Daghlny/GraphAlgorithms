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
		if(curr->vid == id)
			return std::static_cast<void *>(curr);
		curr = curr->next;
	}
	return NULL;
}

template<typename vertexT> bool
base::AdjaList<typename>::deleteEdge(vertex_t vid){
	adjaNode *pre = head, *curr = head;
	if(vid == val)
		return false;
	if(vid == head->vid){
		head = head->next;
		delete head;
		num--;
		return true;
	}
	
	adjaNode *pre  = head;
	adjaNode *curr = head->next;

	while(curr != NULL){
		if(curr->vid == vid){
			pre->next = curr->next;
			delete curr;
			num--;
			return true;
		}
		pre = pre->next;
		curr = curr->next;
	}
	
	return false;
}






















