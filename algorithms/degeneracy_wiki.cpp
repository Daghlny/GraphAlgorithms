
#include <iostream>
#include <set>
#include <map>

#include "Graph.hpp"
#include "uGraph.hpp"
#include "types.hpp"

typedef std::map<deg_t, vlist> deg_table_t;

void
dt_insert(deg_table_t& dt, vid_t v, usize_t adjlen){

    deg_table_t::iterator dtable_it = dt.find(adjlen);
    if( dtable_it == dt.end() ){
        std::pair<deg_t, vlist> new_item = std::make_pair(adjlen, vlist());
        dt.insert(new_item);
    }
    (dt[adjlen]).insert(v);
}

/* update the degree table with @v == removed vertex
 * all @v's neighbors is moved to the lowwer degree array(current-1)
 */
int
update_deg_table(deg_table_t &dt, uGraph &g, const vid_t &v){
    
    const vlist& adjlist = g.adjlist(v);
    for(deg_table_t::iterator it = dt.begin();
            it != dt.end(); ++it ) {
        if( !(it->second).empty() ){
            for(vlist::iterator adjit = it->second.begin();
                    adjit != it->second.end(); ++adjit) {
                if( adjlist.find(*adjit) != adjlist.end() ){
                    dt[(it->first)-1].insert(*adjit);
                    it->second.erase(adjit);
                }
            }
        }
    }

    return 0;
}

/* remove one of the vertices with the smallest degree
 * return -1 if there are no more vertices to handle
 * return the smallest degree in other cases
 * the removed vertex is @v
 */
int
remove_degsmallest_vertex(deg_table_t& dt, vid_t &v){

    deg_table_t::iterator smallest_dt_iter;
    for( smallest_dt_iter = dt.begin(); smallest_dt_iter != dt.end();
            smallest_dt_iter++ ) {
        if((smallest_dt_iter->second).empty())
            continue;
        else break;
    }

    /* when the iterator points to the dt.end(), 
     * it means all vertices have been removed
     */
    if( smallest_dt_iter == dt.end() ){
        return -1;        
    }

    deg_t smallest_deg = smallest_dt_iter->first;
    vlist &smallest_vertices = smallest_dt_iter->second;

    vid_t chosen_vertex = *(smallest_vertices.begin());
    smallest_vertices.erase(smallest_vertices.begin());

    v = chosen_vertex;

    return (int)smallest_deg;
}

int
main(int argc, char **argv){

    if( argc != 2 ){
        std::cout << "ProgramName InputGraphFile" << std::endl;
        exit(0);
    }

    uGraph g(argv[1]);
    deg_table_t dt;
    std::set<vid_t> vertices;
    g.vertex_set(vertices);

    /* add every vertex to its degree array */
    for( std::set<vid_t>::iterator it = vertices.begin();
         it != vertices.end();
         ++it) {
        
        dt_insert(dt, *it, g.adj_size(*it));
    }

    vid_t rm_vertex = 0;
    int smallest_deg = 0;
    int degeneracy   = 0;
    vid_t degeneracy_vertex = -1;
    while( (smallest_deg = remove_degsmallest_vertex(dt, rm_vertex)) != -1){
        if( smallest_deg > degeneracy ){
            degeneracy = smallest_deg;
            degeneracy_vertex = rm_vertex;
        }
        std::cout << rm_vertex << ' ' << smallest_deg << std::endl;
        update_deg_table(dt, g, rm_vertex);
    }
    std::cout << "degeneracy: "<< degeneracy << std::endl;
    std::cout << "the vertex: " << degeneracy_vertex << std::endl;

    return 1;
}


