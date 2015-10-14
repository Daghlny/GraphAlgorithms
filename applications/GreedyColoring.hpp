
// author: Ritchie Lee

#ifndef __APP__GREEDYCOLORING__HPP__
#define __APP__GREEDYCOLORING__HPP__

#include"../headers/Graph.hpp"
#include"../headers/AdjaList.hpp"

#include<iostream>
#include<cstdint>
#include<vector>
#include<map>

class GreedyColoring{
	public:
		typedef std::pair<vertex_id_t, uint32_t> vseq_t;
		GreedyColoring(Graph *x_g): g(x_g){}
		
		uint32_t run_wp();
		uint32_t run_br();
		
	private:
		void init_wp_seq();
		void init_br_seq();
	
		Graph *g;
		std::vector<vertex_id_t> seq;
}

#endif
