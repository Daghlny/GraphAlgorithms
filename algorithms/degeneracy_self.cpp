
#include <map>
#include <set>
#include <iostream>
#include <stdlib.h>

#include "types.hpp"
#include "uGraph.hpp"


int
main(int argc, char **argv){

    if( argc != 3 ){
        std::cout << "ProgramName InputGraphFile OutputToggle" << std::endl;
        exit(0);
    }

    std::cout << "Begin constructing graph..." << std::endl;
    uGraph g(argv[1]);
    std::cout << "finish reading data..." << std::endl;
    
    vid_t curr_vertex = 0;
    int degeneracy = 0;
    vid_t degeneracy_vertex = 0;
    ug_t& data = g.get_ugraph_data();

    const int toggle = atoi(argv[2]);
    vid_t total_vertex_num = g.vertex_num();
    vid_t flag = total_vertex_num / 10 * 9;
    vid_t decrement = total_vertex_num / 10;
    int   percentage = 10;

    while(g.vertex_num() != 0){

        if( g.vertex_num() == flag ){
            std::cout << "have finished " << percentage << "% vertices" << std::endl;
            percentage += 10;
            flag -= decrement;
        }
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
        if( toggle )
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


