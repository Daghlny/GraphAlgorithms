
// author: Ritchie Lee

#include"GreedyColoring.hpp"
#include"../headers/Graph.hpp"
#include"../headers/AdjaList.hpp"

#include<vector>
#include<map>
#include<set>
#include<cstdint>
#include<utility>

int wp_cmp_func(const vseq_t &x, const vseq_t &y);

size_t
GreedyColoring::run_wp(){
	size_t color_num = 0;
	
	//vtx_color is replaced by colors
	//std::map<vertex_id_t, uint32_t> vtx_color;
	
	for(std::vector<vertex_id_t>::iterator iter = seq.begin();
		iter != seq.end();
		++iter){
		//these codes could be optimized
		//espacily the colors default value
		
		color_t curColor = get_first_avail_color(*iter);
		colors.insert(std::make_pair(*iter, curColor));

	}
	return get_color_sum(colors);
}

//initial the sequence that indicates the order of vertexs for coloring
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

//replaced by get_first_avail_color(vertex_id_t sour)

color_t
GreedyColoring::get_first_avail_color(vertex_id_t sour){
	
	const AdjaList &c_alist = g->getAdjaList(sour);
	adjaNode *head = c_alist.getHead();
	std::set<color_t> no_colors;
	std::vector<vertex_id_t>::iterator pos;
	
	//add all adjaceny vertexs into the no_colors to avoid the conflict
	while(head != NULL){
		if((pos = colors.find(head->Nid)) != colors.end())
			no_colors.insert(pos->second);
	}
	
	//check the smallest color donesn't exist in the @no_colors;
	for(color_t i = 0;; ++i){
		if(no_colors.count(i) == 0)
			return i;
	}
}

int wp_cmp_func(const vseq_t &x, const vseq_t &y){
	return x.second > y.second;
}

color_t
GreedyColoring::get_color_sum(std::map<vertex_id_t, color_t> colors){
	color_t max_color = 0;
	for(std::map<vertex_id_t, color_t>::iterator iter = colors.begin();
		iter != colors.end();
		++iter){
			max_color = max_color > iter->second ?
						max_color : iter->second;
		}
	return max_color;
}




















