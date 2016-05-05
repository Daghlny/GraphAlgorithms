
#ifndef __GA__GRAPH__HPP__
#define __GA__GRAPH__HPP__

class Graph{
    public:
        Graph(){}
        Graph(const Graph& g);

        virtual void       read_graph_data(char *file);

        usize_t            adj_size(vid_t sour);
        const adj_t&       get_adj(vid_t sour);
        usize_t            vtx_num();
        void               vtx_set(std::set<vid_t>* vs);


    protected:
        usize_t            edge_num;

        virtual void       add_edg(vid_t sour, vid_t dest) =0 ;

};

#endif

