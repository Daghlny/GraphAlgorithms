
// author: Ritchie Lee
// date:   15-10-27
//

#ifndef __HEADERS__GRAPH__HPP__
#define __HEADERS__GRAPH__HPP__

#include"adjaList.hpp"
#include"types.hpp"
#include<vector>

class Graph{
	public:
		usize_t get_vertex_sum();
		
		//change or check the edges in the graph
		virtual void add_edge(vertex_id_t sour, vertex_id_t dest) = 0;
		virtual void del_edge(vertex_id_t sour, vertex_id_t dest) = 0;
		virtual bool find_edge(vertex_id_t sour, vertex_id_t dest) = 0;
		
		// some methods on adjalists
		usize_t get_adjalist_size(vertex_id_t sour);
		const adjaList& get_adjalist(vertex_id_t sour);
};

#endif



