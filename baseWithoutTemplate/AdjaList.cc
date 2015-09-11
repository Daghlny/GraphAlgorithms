#include"AdjaList.hpp"

void
base::AdjaList::addEdge(Graph::vertex_t dest){
	if(head == NULL && tail == NULL){
		AdjaNode *tmp = new AdjaNode(dest);
		head = tmp;
		tail = tmp;
		node_sum++;
		return;
	}
	
	AdjaNode *tmp = new AdjaNode(dest);
	tmp->next = head;
	head = dest;
	node_sum++;
	return;
}

bool
base::AdjaList::findNode(Graph::vertex_t dest){
	AdjaNode *cur = head;
	while(cur != NULL){
		if(cur->vid == dest)
			return true;
		cur = cur->next;
	}
	return false;
}

/* delete the node with the ID @dest, return false if the Node   doesn't exist*/
bool
base::AdjaList::deleteNode(Graph::vertex_t dest){
	if(head->vid == dest){
		AdjaNode *tmp = head;
		head = head->next;
		delete tmp;
		node_sum--;
		return true;
	}
	AdjaNode *cur = head->next, *pre = head;
	while(cur != NULL){
		if(cur->vid == dest){
			pre->next = cur->next;
			delete cur;
			node_sum--;
			return true;
		}
		cur = cur->next;
		pre = pre->next;
	}
	return false;
}












