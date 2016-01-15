#ifndef __GA__UGRAPH__HPP__
#define __GA__UGRAPH__HPP__

#include<set>
#include<map>
#include<fstream>
#include<string>
#include<utility>
#include<iostream>

#include"types.hpp"

typedef std::map<vid_t, adj_t> ug_t;

// the objects of this class represent a undirected graph
// the class supply some basic operations
// data of a uGraph connot be changed after the building phase
class uGraph{
	public:
		uGraph(){}
		uGraph(char *file){read_graph_data(file);}

		void  read_graph_data(char *file);

		usize_t       adj_size(vid_t sour);
		const adj_t&  get_adj(vid_t sour);
		usize_t       vtx_sum();
		
	private:
		ug_t data;

		void add_edg(vid_t sour, vid_t dest);

};

// init the graph object with a datafile in adjacency list format
void
diGraph::read_graph_data(char *file){
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
		std::string::size_type tab_pos = line.find_first_of('\t', 0);
		vid_t sour = atoi(line.substr(0, tab_pos).c_str());
		vid_t dest = atoi(line.substr(tab_pos, line.size()-tab_pos).c_str());

		add_edg(sour, dest);
		add_edg(dest, sour);
	}
	in_f.close();
}

// add a new edge into the @data, this function is private
void
diGraph::add_edg(vid_t sour, vid_t dest){
	dig_t::iterator iter = data.find(sour);
	if(iter == data.end()){
		
		std::pair<vid_t, adj_t> new_item = std::make_pair(sour, adj_t());
		data.insert(new_item);
	}
	data[sour].insert(dest);
}

// return the adjacency list's size of certain vertex
usize_t 
diGraph::adj_size(vid_t sour){
	return data[sour].size();
}

// return the adjacency list of certain vertex
const adj_t& 
diGraph::get_adj(vid_t sour){
	return data[sour];
}

// return the size of vertices' set
usize_t
diGraph::vtx_sum(){
	return data.size();
}

#endif

