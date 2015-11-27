
// author: Ritchie Lee
// date:   15-10-21

#ifndef __HEADERS__D__GRAPH__HPP__
#define __HEADERS__D__GRAPH__HPP__

#include"AdjaList.hpp"
#include"Graph.hpp"
#include<vector>
#include<deque>
#include<map>
#include<iostream>
#include<cstdint>
#include<algorithm>

// class represents an directd graph
// the attribute @adjalists means the adjalists of all vertexs

class dGraph: public Graph{
public:
	dGraph(){}
	dGraph(usize_t vertexSum): nList(vertex_num){}

	uint64_t get_vertex_sum();

	const  AdjaList& get_adjaList(vertex_id_t sour);
	size_t adjaList_size(vertex_id_t sour);

	void add_edge(vertex_id_t sour, vertex_id_t dest);
	void del_edge(vertex_id_t sour, vertex_id_t dest);
	bool find_edge(vertex_id_t sour, vertex_id_t dest);

private:
	std::map<vertex_id_t, adjaList> alists;

};

void
dGraph::add_edge(vertex_id_t sour, vertex_id_t dest){
	alists[sour].add_edge(dest);
}

void
dGraph::del_edge(vertex_id_t sour, vertex_id_t dest){
	alists[sour].del_edge(dest);
}


































#endif


