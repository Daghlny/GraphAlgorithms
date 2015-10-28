
// author: Ritchie Lee
// date:   15-10-27
//

#ifndef __HEADERS__GRAPH__HPP__
#define __HEADERS__GRAPH__HPP__

#include"adjaList.hpp"
#include<vector>

class Graph{
	public:
		virtual void add_edge(vertex_id_t sour, vertex_id_t dest) = 0;
		virtual void del_edge(vertex_id_t sour, vertex_id_t dest) = 0;
		virtual bool find_edge(vertex_id_t sour, vertex_id_t dest) = 0;
}
