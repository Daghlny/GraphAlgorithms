
#include"uGraph.hpp"

#include<set>
#include<map>
#include<fstream>
#include<utility>
#include<string>
#include<algorithm>
#include<iostream>

// init the graph object with a datafile in adjacency list format
void
uGraph::read_graph_data(const char *file){
    
	std::ifstream in_f;
	in_f.open(file);

	char buff[100];

	while(!in_f.eof()){
		in_f.getline(buff, 100);
		if(buff[0] == '#')
			continue;
		if(!isdigit(buff[0]))
			break;
		std::string line(buff);
		std::string::size_type tab_pos = line.find_first_of(' ', 0);
		vid_t sour = atoi(line.substr(0, tab_pos).c_str());
		vid_t dest = atoi(line.substr(tab_pos, line.size()-tab_pos).c_str());

		add_edge(sour, dest);
		add_edge(dest, sour);
	}
	in_f.close();
}

// add a new edge into the @data, this function is private
void
uGraph::add_edge(vid_t sour, vid_t dest){

	ug_t::iterator sour_it = data.find(sour);
    ug_t::iterator dest_it = data.find(dest);

	if(sour_it == data.end()){
		
		std::pair<vid_t, vlist> new_item = std::make_pair(sour, vlist());
		data.insert(new_item);
	}

    if( dest_it == data.end() ) {
        std::pair<vid_t, vlist> new_item = std::make_pair(dest, vlist());
        data.insert(new_item);
    }

    (data[dest]).insert(sour);
	(data[sour]).insert(dest);
}

// return the adjacency list's size of certain vertex
usize_t 
uGraph::adj_size(vid_t sour) const {
	//return (data[sour]).size();
    ug_t::const_iterator it = data.find(sour);
    if( it != data.cend() )
        return it->second.size();
    return 0;
}

// return the adjacency list of certain vertex
const vlist& 
uGraph::get_adj(vid_t sour) const {
	//return data[sour];
    ug_t::const_iterator it = data.find(sour);
    if( it != data.cend() )
        return it->second;
    std::cout << "error in get_adj(vid_t)" << std::endl;
    exit(0);
    return it->second;
}

// return the size of vertices' set
usize_t
uGraph::vertex_num() const{
	return data.size();
}

// return the number of graph's edges
usize_t
uGraph::edge_num() const {
    
    usize_t res = 0;
    for( ug_t::const_iterator it = data.cbegin();
         it != data.cend();
         ++it) {

        res += it->second.size();
    }

    return res;
}

// return whole adjcency list with pointer
vlist*
uGraph::adjlist_ptr( vid_t v ){
    if( data.find(v) != data.end() )
        return &data[v];
    else
        return NULL;
}

// this function doesn't have existence check
const vlist&
uGraph::adjlist( vid_t v ) const{
    /*
    if( data.find(v) != data.end() )
        return data[v];
    */

    ug_t::const_iterator it = data.find(v);
    if( it != data.cend() )
        return it->second;
    std::cout << "error in adjlist(vid_t)" << std::endl;
    exit(0);
    return it->second;
}

// return the vertices' set
void
uGraph::vertex_set(std::set<vid_t>&  vs) const{
	for(typename ug_t::const_iterator iter = data.cbegin();
		iter != data.cend();
		++iter){
		vs.insert(iter->first);
	}	
}

// check whether two vertices connectivity
bool
uGraph::if_connect(vid_t v, vid_t u) const{
    
    if( adj_size(v) > adj_size(u) ){
        return ( adjlist(u).find(v) != adjlist(u).end() );
    } else {
        return ( adjlist(v).find(u) != adjlist(v).end() );
    }

    return false;
}

// release the memory of graph adjcency lists
void
uGraph::clear_data() {
    data.clear();
}

