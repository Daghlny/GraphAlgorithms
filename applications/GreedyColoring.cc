
// author: Ritchie Lee

#include"GreedyColoring.hpp"
#include"../headers/Graph.hpp"
#include"../headers/AdjaList.hpp"

#include<vector>
#include<map>
#include<cstdint>
#include<utility>

int wp_cmp_func(const vseq_t &x, const vseq_t &y);

uint32_t
GreedyColoring::run_wp(){
	uint32_t color_num = 0;
	std::map<vertex_id_t, uint32_t> vtx_color;
	for(std::vector<vertex_id_t>::iterator iter = seq.begin();
		iter != seq.end();
		++iter){
		//these codes could be optimized
		//espacily the vtx_color default value
		if(vtx_color.find(*iter) == vtx_color.end()){
			vtx_color[*iter] = 0;
		}
		AdjaList &cur_adjalist = g->getAdjaList(*iter);
		adjaNode head = cur_adjalist.getHead();
		while(head != NULL){
			if(vtx_color.find(head->Nid) == vtx_color.end()){
				if(vtx_color.find(*iter) != 1)
					vtx_color[head->Nid] = 1;
				else
					vtx_color[head->Nid] = 0;
			}
		}
	}
}

void
GreedyColoring::init_wp_seq(){
	std::vector<std::pair<vertex_id_t, uint32_t>> tmp_vec(g->getVertexsNum());
	seq.clear();
	
	uint64_t g_size = g->getVertexsNum();
	for(vertex_id_t i = 0; i != g_size; ++i){
		tmp_vec.push_back(std::make_pair(i, g->getAdjaListSize(i)));
	}
	std::sort(tmp_v.begin(), tmp_v.end(), wp_cmp_func);
	
	for(std::vector<std::pair<vertex_id_t, uint32_t>>::iterator iter = tmp_vec.begin();
		iter != tmp_vec.end();
		++iter){
			seq.push_back(iter->first);
		}
	
}

bool
GreedyColoring::neibour_colors(std::vector<uint32_t> *colors,
			       vertex_id_t sour){
	colors.clear();
	const AdjaList &cur_alist = g->getAdjaList(sour);
	for(
}

uint32_t
GreedyColoring::get_color(vertex_id_t sour){
	std::vector<vertex_id_t>
	if((	
}
int wp_cmp_func(const vseq_t &x, const vseq_t &y){
	return x.second > y.second;
}





















