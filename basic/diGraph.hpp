#ifndef __GA__DIGRAPH__HPP__
#define __GA__DIGRAPH__HPP__

#include<set>
#include<map>
#include<iostream>

#include"types.hpp"

typedef std::map<vid_t, adj_t> dig_t;

// the objects of this class represent a directed graph
// the class supply some basic operations
// data of a diGraph connot be changed after the building phase

class diGraph{
	public:
		diGraph(){}
		diGraph(char *file){ read_graph_data(file); }

		void  read_graph_data(char *file);

		usize_t       adj_size(vid_t sour);
		const adj_t&  get_adj(vid_t sour);
		usize_t       vtx_sum();
		
	private:
		dig_t data;

		void add_edg(vid_t sour, vid_t dest);

};


#endif

