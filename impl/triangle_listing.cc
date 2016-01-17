#include<iostream>
#include<set>
#include<map>

#include"types.hpp"
#include"uGraph.hpp"
#include"diGraph.hpp"

#include"algorithms_types.hpp"


size_t
tc_for_ugraph(std::set<tri_t> *res,uGraph* ug){
	std::set<vid_t>* vs = new std::set<vid_t>();
	ug->vtx_set(vs);

	for(typename std::set<vid_t>::iterator iter = vs->begin();
		iter != vs->end();
		++iter){

		const adj_t& tmp_adj = ug->get_adj(*iter);
		for(typename adj_t::iterator pos = tmp_adj.begin();
			pos != tmp_adj.end();
			++pos){
			const adj_t& _tmp_adj = ug->get_adj(*pos);
			for(typename adj_t::iterator _pos = _tmp_adj.begin();
				_pos != _tmp_adj.end();
				++_pos){
				if(tmp_adj.find(*_pos) != tmp_adj.end()){
					tri_t* new_tri = new tri_t(*iter, *pos, *_pos);
					res->insert(*new_tri);
					delete new_tri;
				}
			}
		}
	}

	delete vs;

	return res->size();	

}
