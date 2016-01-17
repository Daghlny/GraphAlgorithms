#ifndef __GRAPH__H__
#define __GRAPH__H__

#include"AdjaList.hpp"
#include<vector>
#include<deque>
#include<iostream>
#include<cstdint>
#include<algorithm>

class Graph{
	public:
		Graph(uint64_t vertex_num): nList(vertex_num){}
		void addEdge(vertex_id_t sour, vertex_id_t dest);
		void BFS(vertex_id_t sour);
		uint64_t getVertexsNum(){ return nList.size();}

		friend class buildGraph;
	private:
		std::vector<AdjaList> nList;
};

void
Graph::addEdge(vertex_id_t sour, vertex_id_t dest){
	nList[sour].addEdge(dest);

}

void
Graph::BFS(vertex_id_t sour){
	typedef char flag_t;
	uint64_t index = 1;

	std::vector<flag_t> marked(getVertexsNum(), 0);
	std::deque<vertex_id_t> wait_q;
	
	wait_q.push_back(sour);

	while(wait_q.size() != 0){
		
		vertex_id_t curr_n = wait_q.front();
		wait_q.pop_front();
		if(marked[curr_n] == 0)
			std::cout << index++ << "node_id: " << curr_n << std::endl;
		marked[curr_n] = 1;
		adjaNode *node_v = nList[curr_n].getHead();

		while(node_v != 0){
			if(marked[node_v->Nid] == 0){
				marked[node_v->Nid] = 1;
				std::cout << index++ << "node_id: " << node_v->Nid << std::endl;
				wait_q.push_back(node_v->Nid);
			}
			node_v = node_v->next;

		}
	}
	
	//std::vector<flag_t>::iterator pos = find(marked.begin(), marked.end(), 0);
	//if(pos != marked.end())
		//BFS(*pos);
}

#endif





