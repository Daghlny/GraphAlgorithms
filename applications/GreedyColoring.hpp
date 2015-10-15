
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
		typedef std::pair<vertex_id_t, color_t> vseq_t;
		typedef uint32_t color_t;
		GreedyColoring(Graph *x_g): g(x_g){}
		
		size_t run_wp();
		//size_t run_br();
		
		color_t get_color_sum(std::map<vertex_id_t, color_t> colors);
		
	private:
		void init_wp_seq();
		//void init_br_seq();

		color_t get_first_avail_color(vertex_id_t sour);
		
		// the @seq is the sequence of coloring
		// the @colors stores the colors and vertexs
		Graph *g;
		std::vector<vertex_id_t> seq;
		std::map<vertex_id_t, color_t> colors;
}

#endif
