
#ifndef __GA__GRAPH__HPP__
#define __GA__GRAPH__HPP__

#include <set>
#include <map>
#include <string>

#include "types.hpp"

class Graph{
    public:
        Graph(){}
        Graph(const Graph& g){};

        virtual usize_t            adj_size(vid_t v) const = 0;
        virtual const vlist&       get_adj(vid_t v) const = 0;
        virtual const vlist&       adjlist(vid_t v) const = 0;
        virtual vlist *            adjlist_ptr(vid_t v) = 0;

        virtual usize_t            vertex_num() const = 0;
        virtual usize_t            edge_num() const = 0;
        virtual void               vertex_set(std::set<vid_t>& vs) const = 0;
        virtual void               clear_data() = 0;


    protected:
        virtual void       read_graph_data(const char *file) = 0;
        virtual void       add_edge(vid_t sour, vid_t dest) = 0 ;

};

#endif

