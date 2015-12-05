#ifndef __HEADERS__GRAPH__H__
#define __HEADERS__GRAPH__H__

#include"AdjaList.hpp"
#include<vector>
#include<deque>
#include<iostream>
#include<cstdint>
#include<algorithm>

class Graph{
	public:
		Graph(uint64_t vertex_num): nList(vertex_num){}
		
		uint64_t         getVertexsNum() { return nList.size();}
		const AdjaList&  getAdjaList(vertex_id_t sour);
		size_t           getAdjaListSize(vertex_id_t sour){ return nList[sour].size();}

		void             addEdge(vertex_id_t sour, vertex_id_t dest);
		void             deleteEdge(vertex_id_t sour, vertex_id_t dest);
		
		friend class buildGraph;

	private:
		std::vector<AdjaList> nList;
};

const AdjaList& 
Graph::getAdjaList(vertex_id_t sour){
	return nList[sour];
}

void
Graph::addEdge(vertex_id_t sour, vertex_id_t dest){
	nList[sour].addEdge(dest);

}

void
Graph::deleteEdge(vertex_id_t sour, vertex_id_t dest){
	nList[sour].deleteEdge(dest);
}


#endif





