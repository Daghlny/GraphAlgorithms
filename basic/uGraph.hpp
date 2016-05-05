
#ifndef __GA__UGRAPH__HPP__
#define __GA__UGRAPH__HPP__

#include<set>
#include<map>
#include<string>

#include"types.hpp"
//#include"Graph.hpp"

//#include"Graph.hpp"

typedef std::map<vid_t, vlist> ug_t;

// the objects of this class represent a undirected graph
// the class supply some basic operations
// data of a uGraph connot be changed after the building phase
class uGraph{
	public:
		uGraph(){}
		uGraph(const char *file){read_graph_data(file);}

		void  read_graph_data(const char *file);

		usize_t           adj_size(vid_t sour);
		const vlist&      get_adj (vid_t sour);
        vlist *           adjlist (vid_t v);
		usize_t           vtx_sum();
		void              vtx_set(std::set<vid_t>* vs);
		
	private:
		ug_t data;

		void add_edg(vid_t sour, vid_t dest);

};


#endif

