
#include <map>
#include <set>
#include <iostream>

#include "types.hpp"
#include "uGraph.hpp"


int
main(int argc, char **argv){

    if( argc != 2 ){
        std::cout << "ProgramName InputGraphFile" << std::endl;
        exit(0);
    }

    uGraph g(argv[1]);
    
    vid_t curr_vertex = 0;
    int degeneracy = 0;
    vid_t degeneracy_vertex = 0;
    ug_t& data = g.get_ugraph_data();

    while(g.vertex_num() != 0){
        usize_t smallest_degree = g.vertex_num();

        /* get the smallest degree and this vertex */
        for(ug_t::iterator it = data.begin(); it != data.end(); ++it)
        {
            if( (it->second).size() < smallest_degree )
            {
                smallest_degree = (it->second).size();
                curr_vertex = it->first;
            }
        }
        if( smallest_degree > degeneracy ){
            degeneracy = smallest_degree;
            degeneracy_vertex = curr_vertex;
        }
        std::cout << curr_vertex << ' ' << smallest_degree << std::endl;

        /* 
         * firstly, remove the @curr_vertex in all its neibors' adjlist
         * secondly, erase @curr_vertex's adjlist from graph data
         */
        const vlist& adjlist = g.adjlist(curr_vertex);
        for( vlist::const_iterator it = adjlist.cbegin();
             it != adjlist.cend(); 
             ++it )
        {
            vlist::iterator curr_vertex_it = data[*it].find(curr_vertex);
            data[*it].erase(curr_vertex_it);
        }
        data.erase(curr_vertex);
    }

    std::cout << "degeneracy: " << degeneracy << std::endl;
    std::cout << "the vertex: " << degeneracy_vertex << std::endl;

    return 0;
}


