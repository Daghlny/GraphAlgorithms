
#ifndef __GA__UGRAPH__HPP__
#define __GA__UGRAPH__HPP__

#include <set>
#include <map>
#include <string>

#include "types.hpp"
#include "Graph.hpp"

typedef std::map<vid_t, vlist> ug_t;

// the objects of this class represent a undirected graph
// the class supply some basic operations
// data of a uGraph connot be changed after the building phase
//
// @Warning: recommand @adjlist(vid_t) instead of @get_adj(vid_t)
class uGraph: public Graph{
	public:
		uGraph(){}
		uGraph(const char *file){read_graph_data(file);}

		usize_t           adj_size(vid_t sour) const;
		const vlist&      get_adj (vid_t sour) const;
        const vlist&      adjlist(vid_t v) const;
        vlist *           adjlist_ptr (vid_t v);
		usize_t           vertex_num() const;
        usize_t           edge_num() const;
		void              vertex_set(std::set<vid_t>& vs) const;
        bool              if_connect(vid_t v, vid_t u) const;
        void              clear_data();

    protected:
		void  read_graph_data(const char *file);
        void  add_edge(vid_t sour, vid_t dest);
		
	private:
		ug_t data;

};


#endif

